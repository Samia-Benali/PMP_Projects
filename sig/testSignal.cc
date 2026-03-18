#include "Signal.h"

#include <gtest/gtest.h>

void callback(int param) {
  std::printf("Hello %i\n", param);
}

TEST(TestSignal, DiscardCombiner){
    
  sig::Signal<void(int)> sig;
  sig.connectSlot(callback);
  int res = 0;
  sig.connectSlot([&res](int x) { res = x; });
  sig.emitSignal(1);
  EXPECT_EQ(res,1);

  sig::Signal<int(int), sig::PredicateCombiner<int>> sig2([](int lhs, int rhs) -> bool {
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

// TEST(TestSignal, LastCombiner){
    

// }

// TEST(TestSignal, VectorCombiner){
    

// }

// TEST(TestSignal, PredicateCombinerUnary){
    

// }

// TEST(TestSignal, PredicateCombinerBinary){
    

// }

int main(int argc, char* argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
