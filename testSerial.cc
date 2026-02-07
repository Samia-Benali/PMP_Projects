#include <gtest/gtest.h>

#include "Serial.h"

#include "config.h"

TEST(TestSerial, OBinaryFileConstructorNoError) {
  EXPECT_NO_THROW({serial::OBinaryFile file("non_existent_file.bin");});
}

int main(int argc, char* argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
