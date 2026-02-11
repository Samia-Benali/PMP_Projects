#include <gtest/gtest.h>

#include "Serial.h"

#include "config.h"


std::string filepath = std::string(TEST_DATA_DIRECTORY);

TEST(TestSerial, IBinaryFile_ConstructorKO){
    EXPECT_THROW({serial::IBinaryFile file("non_existent_file.bin");},
    std::runtime_error);
}

TEST(TestSerial, IBinaryFile_ConstructorOK){
  EXPECT_NO_THROW({serial::IBinaryFile file(filepath + "/test.bin");});
}


TEST(TestSerial, OBinaryFileConstructorNoError) {
  EXPECT_NO_THROW({serial::OBinaryFile file("non_existent_file.bin");});
}

int main(int argc, char* argv[]) {
::testing::InitGoogleTest(&argc, argv);
return RUN_ALL_TESTS();
}
