#include "Signal.h"

#include <gtest/gtest.h>

void callback(int param) {
  std::printf("Hello %i\n", param);
}

TEST(TestSignal, DiscardCombiner){
  sig::DiscardCombiner combiner;
  combiner.combine(42);
  combiner.result();
}

TEST(TestSignal, LastCombiner){
  sig::LastCombiner<int> combiner;
  combiner.combine(42);
  EXPECT_EQ(combiner.result(), 42);
  combiner.combine(100);
  EXPECT_EQ(combiner.result(), 100);
    

}

TEST(TestSignal, VectorCombiner){
  sig::VectorCombiner<int> combiner;
  combiner.combine(42);
  combiner.combine(100);
  std::vector<int> expected = {42, 100};
  EXPECT_EQ(combiner.result(), expected);

}


TEST(TestSignal, PredicateCombinerBinary){

  sig::Signal<void(int)> sig;
  sig.connectSlot(callback);
  int res = 0;
  sig.connectSlot([&res](int x) { res = x; });
  sig.emitSignal(1);
  EXPECT_EQ(res,1);

  sig::Signal<int(int), sig::PredicateCombiner<int, sig::PredicateType::Binary>> sig2([](int lhs, int rhs) -> bool {
  return lhs < rhs;
  });
  sig2.connectSlot([](int x) { return x;});
  sig2.connectSlot([](int x) { return x * x;});
  std::size_t id = sig2.connectSlot([](int x) { return x * -1;});
  auto result = sig2.emitSignal(8);
  EXPECT_TRUE(result);
  EXPECT_EQ(*result,-8);
  sig2.disconnectSlot(id);
  result = sig2.emitSignal(8);
  EXPECT_TRUE(result);
  EXPECT_EQ(*result,8);
    
}


TEST(TestSignal, PredicateCombinerUnary){
  sig::PredicateCombiner<int, sig::PredicateType::Unary> number([](int x) -> bool {return x % 10 == 0;});
  number.combine(2);
  number.combine(10);
  number.combine(-100);
  EXPECT_EQ(number.result().value(),-100);

}


int main(int argc, char* argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
