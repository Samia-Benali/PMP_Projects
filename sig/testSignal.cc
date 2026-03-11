#include "Signal.h"

#include <gtest/gtest.h>

TEST(TestSignal, DiscardCombiner){
    Combiner c = new DiscardCombiner();

}

int main(int argc, char* argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
