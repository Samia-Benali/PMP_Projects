#ifndef SIGNAL_H
#define SIGNAL_H

#include <optional>

namespace sig {

  class DiscardCombiner {
  public:
    using result_type = void;

    template<typename U>
    void combine(U item) {
      
    }

    result_type result() {
    }
  };

  template<typename T>
  class LastCombiner {
  public:
    using result_type = T;

    template<typename U>
    void combine(U item) {
      if(std::is_void_v<U>) last = item;// Gérer le cas pour réussir à mettre item dans last std::move(item);
    }

    result_type result() {
      return last;
    }
  
  private : 
    T last;
  };

  template<typename T>
  class VectorCombiner {
  public:
    using result_type = std::vector<T>;
    

    template<typename U>
    void combine(U item) {
      if(std::is_void_v<U>)vect.insert(item);
    }

    result_type result() {
      return vect;
    }

    private:
      std::vector<T> vect;
  };

  enum class PredicateType {
    Unary,
    Binary,
  };

  template<typename T, PredicateType PType = PredicateType::Binary>
  class PredicateCombiner {
  public:
    using result_type = std::optional</* implementation defined */>;

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
  class Signal {
  public:
    using combiner_type = Combiner;

    using result_type = Combiner::result_type;

    Signal(Combiner combiner = Combiner()) {
      // implementation defined
    }

    template<typename... CombinerArgs>
    Signal(CombinerArgs ... args) {
      // implementation defined
    }

    std::size_t connectSlot(std::function<Signature> callback) {
      // implementation defined
    }

    void disconnectSlot(std::size_t id) {
      // implementation defined
    }

    result_type emitSignal(/* implementation defined */) {
      // implementation defined
    }
  };

}

#endif // SIGNAL_H
