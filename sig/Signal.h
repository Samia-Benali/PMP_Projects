#ifndef SIGNAL_H
#define SIGNAL_H

#include <optional>
#include <vector>

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
    void combine(U item) {
      last =  std::move(item);
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
    void combine(U item) {
      if(std::is_same_v<U,T>)vect.insert(item);
    }

    result_type result() {
      return vect;
    }

  };

  enum class PredicateType {
    Unary,
    Binary,
  };

  template<typename T, PredicateType PType = PredicateType::Binary>
  class PredicateCombiner {
  public:
    using result_type = std::optional<T>;

    PredicateCombiner(/* implementation defined */ predicate) {
      // implementation defined
    }

    template<typename U>
    void combine(/* implementation defined */ item) {
      // implementation defined
    }

    result_type result() {
      // implementation defined
    }
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
    Signal(CombinerArgs ... args) 
      : combiner_val(std::move<CombinerArgs>(args)...) {}


    std::size_t connectSlot(std::function<R(Args...)> callback) {
      std::size_t id = next_id++;
      slots[id] = std::move(callback);
      return id;
    }

    void disconnectSlot(std::size_t id) {
      slots.erase(id);
    }

    result_type emitSignal(CombinerArgs... args) {
      for (auto& [id, callback] : slots) {
        if constexpr (std::is_void_v<R>) {
            callback(args...);
        } else {
            combiner_val.combine(callback(args...));
        }
      }
      return combiner_val.result();
    }

  };

}

#endif // SIGNAL_H