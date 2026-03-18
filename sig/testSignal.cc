#include "Signal.h"

#include <gtest/gtest.h>
#include <climits>
#include <limits>

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

TEST(TestSignal, LastCombiner_String){
  sig::LastCombiner<std::string> combiner;
  combiner.combine(std::string("hello"));
  EXPECT_EQ(combiner.result(), "hello");
  combiner.combine(std::string("world"));
  EXPECT_EQ(combiner.result(), "world");
}

TEST(TestSignal, Signal_LastCombiner){
  sig::Signal<int(int), sig::LastCombiner<int>> sig;
  sig.connectSlot([](int x) { return x; });
  sig.connectSlot([](int x) { return x * 2; });
  auto result = sig.emitSignal(5);
  EXPECT_EQ(result, 10);
}


TEST(TestSignal, VectorCombiner){
  sig::VectorCombiner<int> combiner;
  combiner.combine(42);
  combiner.combine(100);
  std::vector<int> expected = {42, 100};
  EXPECT_EQ(combiner.result(), expected);

}

TEST(TestSignal, Signal_VectorCombiner){
  sig::Signal<int(int), sig::VectorCombiner<int>> sig;
  sig.connectSlot([](int x) { return x; });
  sig.connectSlot([](int x) { return x * x; });
  sig.connectSlot([](int x) { return x * -1; });
  auto result = sig.emitSignal(3);
  std::vector<int> expected = {3, 9, -3};
  EXPECT_EQ(result, expected);
}

TEST(TestSignal, Signal_VectorCombiner_TwoEmits){
  sig::Signal<int(int), sig::VectorCombiner<int>> sig;
  sig.connectSlot([](int x) { return x; });
  sig.connectSlot([](int x) { return x * 2; });

  auto r1 = sig.emitSignal(4);
  EXPECT_EQ(r1, (std::vector<int>{4, 8}));

  auto r2 = sig.emitSignal(10);
  EXPECT_EQ(r2, (std::vector<int>{10, 20}));
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

TEST(TestSignal, Signal_PredicateCombinerBinary_Max){
  sig::Signal<int(int), sig::PredicateCombiner<int, sig::PredicateType::Binary>> sig(
      [](int lhs, int rhs) -> bool { return lhs > rhs; });
  sig.connectSlot([](int x) { return x; });
  sig.connectSlot([](int x) { return x * x; });
  sig.connectSlot([](int x) { return x * -1; });
  auto result = sig.emitSignal(3);
  EXPECT_TRUE(result.has_value());
  EXPECT_EQ(*result, 9);
}


TEST(TestSignal, PredicateCombinerUnary){
  sig::PredicateCombiner<int, sig::PredicateType::Unary> number([](int x) -> bool {return x % 10 == 0;});
  number.combine(2);
  number.combine(10);
  number.combine(-100);
  EXPECT_EQ(number.result().value(),-100);

}

TEST(TestSignal, PredicateCombinerUnary_NoMatch){
  sig::PredicateCombiner<int, sig::PredicateType::Unary> combiner(
      [](int x) -> bool { return x > 1000; });
  combiner.combine(1);
  combiner.combine(2);
  EXPECT_FALSE(combiner.result().has_value());
}

TEST(TestSignal, Signal_PredicateCombinerUnary){
  sig::Signal<int(int), sig::PredicateCombiner<int, sig::PredicateType::Unary>> sig(
      [](int x) -> bool { return x % 2 == 0; }); 
  sig.connectSlot([](int x) { return x; });
  sig.connectSlot([](int x) { return x + 1; });
  sig.connectSlot([](int x) { return x * 2; });

  auto result = sig.emitSignal(4);
  EXPECT_TRUE(result.has_value());
  EXPECT_EQ(*result, 8); 
}


TEST(TestSignal, DisconnectNonExistentId){
  sig::Signal<void(int)> sig;
  sig.connectSlot([](int x) { (void)x; });
  EXPECT_NO_FATAL_FAILURE(sig.disconnectSlot(999));
}

TEST(TestSignal, DisconnectAllSlots){
  sig::Signal<void(int)> sig;
  std::size_t id = sig.connectSlot([](int x) { (void)x; });
  sig.disconnectSlot(id);
  EXPECT_NO_FATAL_FAILURE(sig.emitSignal(42));
}

TEST(TestSignal, UniqueIds){
  sig::Signal<int(int), sig::VectorCombiner<int>> sig;
  std::size_t id0 = sig.connectSlot([](int x) { return x; });
  std::size_t id1 = sig.connectSlot([](int x) { return x * 2; });
  EXPECT_NE(id0, id1);
  sig.disconnectSlot(id0);
  std::size_t id2 = sig.connectSlot([](int x) { return x * 3; });
  EXPECT_NE(id1, id2); 
  auto result = sig.emitSignal(2);
  EXPECT_EQ(result, (std::vector<int>{4, 6}));
}


TEST(TestSignal, Signal_ManyConnectDisconnect){
  sig::Signal<int(int), sig::VectorCombiner<int>> sig;

  for (int i = 0; i < 10000; ++i) {
    std::size_t id = sig.connectSlot([](int x) { return x; });
    sig.disconnectSlot(id);
  }
  sig.connectSlot([](int x) { return x * 42; });
  auto result = sig.emitSignal(1);
  EXPECT_EQ(result, (std::vector<int>{42}));
}

TEST(TestSignal, DisconnectSizeMaxId){
  sig::Signal<void(int)> sig;
  sig.connectSlot(callback);
  EXPECT_NO_FATAL_FAILURE(
      sig.disconnectSlot(std::numeric_limits<std::size_t>::max()));
  EXPECT_NO_FATAL_FAILURE(sig.emitSignal(0));
}


int main(int argc, char* argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}