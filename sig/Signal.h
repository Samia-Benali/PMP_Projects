#ifndef SIGNAL_H
#define SIGNAL_H

#include <optional>
#include <vector>
#include <map>
#include <functional>
#include <type_traits>


namespace sig {

  class DiscardCombiner {
  public:
    using result_type = void;

    template<typename U>
    void combine(U item) {
      (void)item;
    }

    result_type result() {
    }
  };

  template<typename T>
  class LastCombiner {
  private : 
    T last;

  public:
    using result_type = T;

    template<typename U>
    void combine(U&& item) {
        last = std::forward<U>(item); 
    }

    result_type result() {
      return last;
    }
  
  };

  template<typename T>
  class VectorCombiner {
  private:
      std::vector<T> vect;

  public:
    using result_type = std::vector<T>;
    

    template<typename U>
    void combine(U&& item) {
        vect.push_back(std::forward<U>(item));
    }

    result_type result() {
      return vect;
    }

  };

  enum class PredicateType {
    Unary,
    Binary,
  };


  template<typename T, PredicateType PType = PredicateType::Unary>
  class PredicateCombiner {};

  template<typename T>
  class PredicateCombiner<T, PredicateType::Unary> {
  public:
      using result_type = std::optional<T>;

      PredicateCombiner(std::function<bool(const T&)> predicate)
          : predicate_val(std::move(predicate)) {}

      template<typename U>
      void combine(U&& item) {
          if (predicate_val(item)) {
              last_val = std::forward<U>(item);
          }
      }
      result_type result() {
          return last_val;
      }

  private:
      std::function<bool(const T&)> predicate_val;
      std::optional<T> last_val;
  };

  template<typename T>
  class PredicateCombiner<T, PredicateType::Binary> {
  public:
      using result_type = std::optional<T>;

      PredicateCombiner(std::function<bool(const T&, const T&)> predicate)
          : predicate_val(std::move(predicate)) {}

      template<typename U>
      void combine(U&& item) {
          if (!last_val.has_value() || predicate_val(*last_val, item)) {
              last_val = std::forward<U>(item);
          }
      }

      result_type result() {
          return last_val;
      }

  private:
      std::function<bool(const T&, const T&)> predicate_val;
      std::optional<T> last_val;
  };



  template<typename Signature, typename Combiner = DiscardCombiner>
  class Signal;

  template<typename R, typename... Args, typename Combiner>
  class Signal<R(Args...), Combiner> {

   private : 
    std::size_t next_id = 0;
    Combiner combiner_val;
    std::map<std::size_t, std::function<R(Args...)>> slots;
  
  public:
    using combiner_type = Combiner;

    using result_type = typename Combiner::result_type;

    Signal(Combiner combiner = Combiner()) 
      : combiner_val(std::move(combiner)){}

    
    template<typename... CombinerArgs>
    Signal(CombinerArgs&& ... args) 
      : combiner_val(std::forward<CombinerArgs>(args)...) {}


    std::size_t connectSlot(std::function<R(Args...)> callback) {
      std::size_t id = next_id++;
      slots[id] = std::move(callback);
      return id;
    }//INT MAX soucis dans les test avec INT MAX 

    void disconnectSlot(std::size_t id) {
      slots.erase(id);
    }

    result_type emitSignal(Args... args) {
      for (auto& [id, callback] : slots) {
        if constexpr (std::is_void_v<R>) {
            callback(args...);
        } else {
            combiner_val.combine(callback(args...));
        }
      }
      if constexpr (!std::is_void_v<R>) {
        return combiner_val.result();
      }
    }

  };

}
#endif //SIGNAL_H