#include <gtest/gtest.h>

#include "Serial.h"

#include "config.h"
#include <cmath>
#include <limits>

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

TEST(TestSerial, IBinaryFile_NotCopyable) {
    EXPECT_FALSE(std::is_copy_constructible<serial::IBinaryFile>::value);
    EXPECT_FALSE(std::is_copy_assignable<serial::IBinaryFile>::value);
}

TEST(TestSerial, OBinaryFile_NotCopyable) {
    EXPECT_FALSE(std::is_copy_constructible<serial::OBinaryFile>::value);
    EXPECT_FALSE(std::is_copy_assignable<serial::OBinaryFile>::value);
}

TEST(TestSerial, OBinaryFile_MoveConstructor) {
  {
    serial::OBinaryFile file1(filepath + "/test_move.bin");
    serial::OBinaryFile file2 = std::move(file1);
    file2 << (int32_t)42;
  } 

  int32_t readVal;
  {
    serial::IBinaryFile file(filepath + "/test_move.bin");
    file >> readVal;
  }
  EXPECT_EQ(42, readVal);
}

TEST(TestSerial, IBinaryFile_MoveAssignment) {
  {
    serial::OBinaryFile file(filepath + "/test_move_assign.bin");
    file << (int32_t)100 << (int32_t)200;
  }

  int32_t val1, val2;
  {
    serial::IBinaryFile file1(filepath + "/test_move_assign.bin");
    file1 >> val1; 
    
    serial::IBinaryFile file2(filepath + "/test.bin"); 
    
    file2 = std::move(file1); 
    
    file2 >> val2; 
  }

  EXPECT_EQ(100, val1);
  EXPECT_EQ(200, val2);
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

TEST(TestSerial, ReadAndWriteFloat) {
  float toInsert = 3.14159f;
  {
    serial::OBinaryFile file(filepath + "/test.bin");
    file << toInsert;
  }

  float hasBeenRead;
  {
    serial::IBinaryFile file(filepath + "/test.bin");
    file >> hasBeenRead;
  }

  EXPECT_EQ(toInsert, hasBeenRead);
}

TEST(TestSerial, ReadAndWriteDouble) {
  double toInsert = 12345.6789012345;
  {
    serial::OBinaryFile file(filepath + "/test.bin");
    file << toInsert;
  }

  double hasBeenRead;
  {
    serial::IBinaryFile file(filepath + "/test.bin");
    file >> hasBeenRead;
  }

  EXPECT_EQ(toInsert, hasBeenRead);
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


TEST(TestSerial, OBinaryFile_AppendMode) {
    {
        serial::OBinaryFile file(filepath + "/test_append.bin", serial::OBinaryFile::Truncate);
        file << (int32_t)1;
    }
    {
        serial::OBinaryFile file(filepath + "/test_append.bin", serial::OBinaryFile::Append);
        file << (int32_t)2;
    }
    {
        serial::IBinaryFile file(filepath + "/test_append.bin");
        int32_t v1, v2;
        file >> v1 >> v2;
        EXPECT_EQ(1, v1);
        EXPECT_EQ(2, v2);
    }
}



TEST(TestSerial, ReadAndWriteFloatSpecial) {
    std::vector<double> specials = {
        std::numeric_limits<double>::infinity(),
        -std::numeric_limits<double>::infinity(),
        std::numeric_limits<double>::quiet_NaN(),
        0.0,
        -0.0
    };

    {
        serial::OBinaryFile file(filepath + "/floats.bin");
        file << specials;
    }

    std::vector<double> read;
    {
        serial::IBinaryFile file(filepath + "/floats.bin");
        file >> read;
    }

    EXPECT_EQ(read.size(), specials.size());
    EXPECT_TRUE(std::isinf(read[0]));
    EXPECT_TRUE(std::isinf(read[1]));
    EXPECT_TRUE(std::isnan(read[2]));
    EXPECT_EQ(read[3], 0.0);
    EXPECT_EQ(read[4], -0.0);
}


TEST(TestSerial, ReadTruncatedFile_ThrowsError) {
    {
        serial::OBinaryFile file(filepath + "/truncated.bin");
        file << (uint8_t)42;
    }
    {
        serial::IBinaryFile file(filepath + "/truncated.bin");
        uint32_t val;
        EXPECT_THROW(file >> val, std::runtime_error);
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

TEST(TestSerial, ReadAndWriteVectorBool) {
  std::vector<bool> insert = {true, false, true, true, false, false, true};
  {
    serial::OBinaryFile file(filepath + "/test.bin");
    file << insert;
  }

  std::vector<bool> read;
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

TEST(TestSerial, ReadAndWriteArrayBool) {
  std::array<bool, 5> insert = {true, false, false, true, true};
  {
    serial::OBinaryFile file(filepath + "/test.bin");
    file << insert;
  }

  std::array<bool, 5> read;
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

TEST(TestSerial, ReadAndWriteMapBoolValues) {
  std::map<std::string, bool> insert = {
      {"oki", true},
      {"nope", false},
      {"YEPPPP", true}
  };
  {
    serial::OBinaryFile file(filepath + "/test.bin");
    file << insert;
  }

  std::map<std::string, bool> read;
  {
    serial::IBinaryFile file(filepath + "/test.bin");
    file >> read;
  }

  EXPECT_EQ(insert, read);
}

TEST(TestSerial, ReadAndWriteMapBoolKeys) {
  std::map<bool, std::string> insert = {
      {true, "Vrai"},
      {false, "Faux"}
  };
  {
    serial::OBinaryFile file(filepath + "/test.bin");
    file << insert;
  }

  std::map<bool, std::string> read;
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
}// TEST CROISES



TEST(TestSerial, ReadAndWriteUint32Crossed) {
  uint32_t toInsert = 0x43563232;
  {
    serial::OBinaryFile file(filepath + "/test.bin",serial::OBinaryFile::Truncate);
    file << toInsert;

  }

  std::byte hasBeenRead[4];
  {

    serial::IBinaryFile file(filepath + "/test.bin");
    file.read(hasBeenRead,4);

  }
  EXPECT_EQ(static_cast<std::byte>(0x43),hasBeenRead[0]);
  EXPECT_EQ(static_cast<std::byte>(0x56),hasBeenRead[1]);
  EXPECT_EQ(static_cast<std::byte>(0x32),hasBeenRead[2]);
  EXPECT_EQ(static_cast<std::byte>(0x32),hasBeenRead[3]);
}

TEST(TestSerial, ReadAndWriteInt32Crossed) {
  int32_t toInsert = 0xF3563232;
  {
    serial::OBinaryFile file(filepath + "/test.bin",serial::OBinaryFile::Truncate);
    file << toInsert;

  }

  std::byte hasBeenRead[4];
  {

    serial::IBinaryFile file(filepath + "/test.bin");
    file.read(hasBeenRead,4);

  }
  EXPECT_EQ(static_cast<std::byte>(0xF3),hasBeenRead[0]);
  EXPECT_EQ(static_cast<std::byte>(0x56),hasBeenRead[1]);
  EXPECT_EQ(static_cast<std::byte>(0x32),hasBeenRead[2]);
  EXPECT_EQ(static_cast<std::byte>(0x32),hasBeenRead[3]);
}


int main(int argc, char* argv[]) {
::testing::InitGoogleTest(&argc, argv);
return RUN_ALL_TESTS();
}
