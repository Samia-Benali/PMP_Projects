#include <gtest/gtest.h>

#include "Serial.h"

#include "config.h"


std::string filepath = std::string(TEST_DATA_DIRECTORY);

TEST(TestSerial, IBinaryFile_ConstructorKO){
    EXPECT_THROW({serial::IBinaryFile file("/non_existent");},
    std::runtime_error);
}

TEST(TestSerial, IBinaryFile_ConstructorOK){
  EXPECT_NO_THROW({serial::IBinaryFile file(filepath + "/test.bin");});
}

TEST(TestSerial, IBinaryFile_ConstructorOK2){
  EXPECT_NO_THROW({serial::IBinaryFile file(filepath + "/existent.bin");});
}


TEST(TestSerial, OBinaryFileConstructorNoError) {
  EXPECT_NO_THROW({serial::OBinaryFile file(filepath + "/non_existent");});
}


TEST(TestSerial, ReadAndWriteUint8) {
  int toInsert = 3;
  {
    serial::OBinaryFile file(filepath + "/test.bin");
    file << toInsert;

  }

  int hasBeenRead;
  {

    serial::IBinaryFile file(filepath + "/test.bin");
    file >> hasBeenRead;

  }

  EXPECT_EQ(toInsert,hasBeenRead);
}

TEST(TestSerial, ReadOnANonExistentAndWriteUint8) {
  int toInsert = 3;
  {
    serial::OBinaryFile file(filepath + "/test.bin");
    file << toInsert;

  }

  int hasBeenRead = INT8_MAX;
  {

    EXPECT_THROW(serial::IBinaryFile file(filepath + "/test2.bin");,std::runtime_error);

  }

  EXPECT_GT(hasBeenRead,toInsert);
}


TEST(TestSerial, ReadAndWriteUint16) {
  int toInsert = 256;
  {
    serial::OBinaryFile file(filepath + "/test.bin");
    file << toInsert;

  }

  int hasBeenRead;
  {

    serial::IBinaryFile file(filepath + "/test.bin");
    file >> hasBeenRead;

  }

  EXPECT_EQ(toInsert,hasBeenRead);
}


TEST(TestSerial, ReadAndWriteChar) {
  int toInsert = 'c';
  {
    serial::OBinaryFile file(filepath + "/test.bin");
    file << toInsert;

  }

  int hasBeenRead;
  {

    serial::IBinaryFile file(filepath + "/test.bin");
    file >> hasBeenRead;

  }

  EXPECT_EQ(toInsert,hasBeenRead);
}

TEST(TestSerial, ReadAndWriteUint32) {
  int toInsert = 65536;
  {
    serial::OBinaryFile file(filepath + "/test.bin");
    file << toInsert;

  }

  int hasBeenRead;
  {

    serial::IBinaryFile file(filepath + "/test.bin");
    file >> hasBeenRead;

  }

  EXPECT_EQ(toInsert,hasBeenRead);
}


TEST(TestSerial, ReadAndWriteUint64) {
  int toInsert = 4294967295;
  {
    serial::OBinaryFile file(filepath + "/test.bin");
    file << toInsert;

  }

  int hasBeenRead;
  {

    serial::IBinaryFile file(filepath + "/test.bin");
    file >> hasBeenRead;

  }

  EXPECT_EQ(toInsert,hasBeenRead);
}




int main(int argc, char* argv[]) {
::testing::InitGoogleTest(&argc, argv);
return RUN_ALL_TESTS();
}
