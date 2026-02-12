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
  uint8_t toInsert = 3;
  {
    serial::OBinaryFile file(filepath + "/test.bin");
    file << toInsert;

  }

  uint8_t hasBeenRead;
  {

    serial::IBinaryFile file(filepath + "/test.bin");
    file >> hasBeenRead;

  }

  EXPECT_EQ(toInsert,hasBeenRead);
}


TEST(TestSerial, ReadAndWriteInt8) {
  int8_t toInsert = -3;
  {
    serial::OBinaryFile file(filepath + "/test.bin");
    file << toInsert;

  }

  int8_t hasBeenRead;
  {

    serial::IBinaryFile file(filepath + "/test.bin");
    file >> hasBeenRead;

  }

  EXPECT_EQ(toInsert,hasBeenRead);
}

TEST(TestSerial, ReadOnANonExistentAndWriteUint8) {
  uint8_t toInsert = 3;
  {
    serial::OBinaryFile file(filepath + "/test.bin");
    file << toInsert;

  }

  uint8_t hasBeenRead = INT8_MAX;
  {

    EXPECT_THROW(serial::IBinaryFile file(filepath + "/test2.bin");,std::runtime_error);

  }

  EXPECT_GT(hasBeenRead,toInsert);
}


TEST(TestSerial, ReadAndWriteUint16) {
  uint16_t toInsert = 256;
  {
    serial::OBinaryFile file(filepath + "/test.bin");
    file << toInsert;

  }

  uint16_t hasBeenRead;
  {

    serial::IBinaryFile file(filepath + "/test.bin");
    file >> hasBeenRead;

  }

  EXPECT_EQ(toInsert,hasBeenRead);
}


TEST(TestSerial, ReadAndWriteInt16) {
  int16_t toInsert = -256;
  {
    serial::OBinaryFile file(filepath + "/test.bin");
    file << toInsert;

  }

  int16_t hasBeenRead;
  {

    serial::IBinaryFile file(filepath + "/test.bin");
    file >> hasBeenRead;

  }

  EXPECT_EQ(toInsert,hasBeenRead);
}


TEST(TestSerial, ReadAndWriteChar) {
  char toInsert = 'c';
  {
    serial::OBinaryFile file(filepath + "/test.bin");
    file << toInsert;

  }

  char hasBeenRead;
  {

    serial::IBinaryFile file(filepath + "/test.bin");
    file >> hasBeenRead;

  }

  EXPECT_EQ(toInsert,hasBeenRead);
}

TEST(TestSerial, ReadAndWriteUint32) {
  uint32_t toInsert = 65536;
  {
    serial::OBinaryFile file(filepath + "/test.bin");
    file << toInsert;

  }

  uint32_t hasBeenRead;
  {

    serial::IBinaryFile file(filepath + "/test.bin");
    file >> hasBeenRead;

  }

  EXPECT_EQ(toInsert,hasBeenRead);
}


TEST(TestSerial, ReadAndWriteInt32) {
  int32_t toInsert = -65536;
  {
    serial::OBinaryFile file(filepath + "/test.bin");
    file << toInsert;

  }

  int32_t hasBeenRead;
  {

    serial::IBinaryFile file(filepath + "/test.bin");
    file >> hasBeenRead;

  }

  EXPECT_EQ(toInsert,hasBeenRead);
}


TEST(TestSerial, ReadAndWriteUint64) {
  uint64_t toInsert = 4294967295;
  {
    serial::OBinaryFile file(filepath + "/test.bin");
    file << toInsert;

  }

  uint64_t hasBeenRead;
  {

    serial::IBinaryFile file(filepath + "/test.bin");
    file >> hasBeenRead;

  }

  EXPECT_EQ(toInsert,hasBeenRead);
}


TEST(TestSerial, ReadAndWriteInt64) {
  int64_t toInsert = -429496795;
  {
    serial::OBinaryFile file(filepath + "/test.bin");
    file << toInsert;

  }

  int64_t hasBeenRead;
  {

    serial::IBinaryFile file(filepath + "/test.bin");
    file >> hasBeenRead;

  }

  EXPECT_EQ(toInsert,hasBeenRead);
}


TEST(TestSerial, ReadAndWriteString) {
  std::string toInsert = "yo";
  {
    serial::OBinaryFile file(filepath + "/test.bin");
    file << toInsert;

  }

  std::string hasBeenRead;
  {

    serial::IBinaryFile file(filepath + "/test.bin");
    file >> hasBeenRead;

  }

  EXPECT_EQ(toInsert,hasBeenRead);
}



TEST(TestSerial, ReadAndWriteMethodsWithBytes) {
  std::byte toInsert[5];
  toInsert[0] = static_cast<std::byte>(0xFE);
  toInsert[1] = static_cast<std::byte>(0x00);
  toInsert[2] = static_cast<std::byte>(0x23);
  toInsert[3] = static_cast<std::byte>(0x88);
  toInsert[4] = static_cast<std::byte>(0x48);
  {
    serial::OBinaryFile file(filepath + "/test.bin");
    file.write(toInsert,5);

  }

  std::byte hasBeenRead[5];
  {

    serial::IBinaryFile file(filepath + "/test.bin");
    file.read(hasBeenRead,5);

  }

  for(int i=0;i<5;i++){
    EXPECT_EQ(toInsert[i],hasBeenRead[i]);
  }
}



TEST(TestSerial, ReadAndWriteMethodsWithBytes) {
  std::byte toInsert[5];
  toInsert[0] = static_cast<std::byte>(0xFE);
  toInsert[1] = static_cast<std::byte>(0x00);
  toInsert[2] = static_cast<std::byte>(0x23);
  toInsert[3] = static_cast<std::byte>(0x88);
  toInsert[4] = static_cast<std::byte>(0x48);
  {
    serial::OBinaryFile file(filepath + "/test.bin");
    file.write(toInsert,5);

  }

  std::byte hasBeenRead[5];
  {

    serial::IBinaryFile file(filepath + "/test.bin");
    file.read(hasBeenRead,5);

  }

  for(int i=0;i<5;i++){
    EXPECT_EQ(toInsert[i],hasBeenRead[i]);
  }
}


TEST(TestSerial, ReadAndWriteVectorInt32) {
  std::vector<int32_t> insert = {1, 2, 3, 4, 5, -100, 42};
  {
    serial::OBinaryFile file(filepath + "/test.bin");
    file << insert;
  }

  std::vector<int32_t> read;
  {
    serial::IBinaryFile file(filepath + "/test.bin");
    file >> read;
  }

  EXPECT_EQ(insert, read);
}

TEST(TestSerial, ReadAndWriteVectorString) {
  std::vector<std::string> insert = {"Hello", "World", "C++", "Bytes", "Controversional"};
  {
    serial::OBinaryFile file(filepath + "/test.bin");
    file << insert;
  }

  std::vector<std::string> read;
  {
    serial::IBinaryFile file(filepath + "/test.bin");
    file >> read;
  }

  EXPECT_EQ(insert, read);
}

TEST(TestSerial, ReadAndWriteEmptyVector) {
  std::vector<int32_t> insert = {};
  {
    serial::OBinaryFile file(filepath + "/test.bin");
    file << insert;
  }

  std::vector<int32_t> read;
  {
    serial::IBinaryFile file(filepath + "/test.bin");
    file >> read;
  }

  EXPECT_EQ(insert, read);
  EXPECT_TRUE(read.empty());
}


TEST(TestSerial, ReadAndWriteArrayDouble) {
  std::array<double, 4> insert = {3.14, 2.71, -0.01, 123.456};
  {
    serial::OBinaryFile file(filepath + "/test.bin");
    file << insert;
  }

  std::array<double, 4> read;
  {
    serial::IBinaryFile file(filepath + "/test.bin");
    file >> read;
  }

  EXPECT_EQ(insert, read);
}


TEST(TestSerial, ReadAndWriteSetInt) {
  std::set<int32_t> insert = {5, 1, 4, 2, 3}; 
  {
    serial::OBinaryFile file(filepath + "/test.bin");
    file << insert;
  }

  std::set<int32_t> read;
  {
    serial::IBinaryFile file(filepath + "/test.bin");
    file >> read;
  }

  EXPECT_EQ(insert, read);
}


TEST(TestSerial, ReadAndWriteMapIntString) {
  std::map<int32_t, std::string> insert = {
      {1, "one"},
      {2, "two"},
      {10, "ten"},
      {-5, "minus five"}
  };
  {
    serial::OBinaryFile file(filepath + "/test.bin");
    file << insert;
  }

  std::map<int32_t, std::string> read;
  {
    serial::IBinaryFile file(filepath + "/test.bin");
    file >> read;
  }

  EXPECT_EQ(insert, read);
}


TEST(TestSerial, ReadAndWriteVectorsInVector) {
  std::vector<std::vector<int16_t>> insert = {
      {1, 2},
      {3, 4, 5},
      {}, 
      {6}
  };
  {
    serial::OBinaryFile file(filepath + "/test.bin");
    file << insert;
  }

  std::vector<std::vector<int16_t>> read;
  {
    serial::IBinaryFile file(filepath + "/test.bin");
    file >> read;
  }

  EXPECT_EQ(insert, read);
}

int main(int argc, char* argv[]) {
::testing::InitGoogleTest(&argc, argv);
return RUN_ALL_TESTS();
}
