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

TEST(TestSerial, OBinaryFile_MoveConstructorAssignment) {
      serial::OBinaryFile writer1(filepath + "/test.bin");
      
      // Move Constructor
      serial::OBinaryFile writer2 = std::move(writer1); 
      writer2 << (int)42;

      // Move Assignment
      serial::OBinaryFile writer3(filepath + "/test2.bin");
      writer3 = std::move(writer2);
      writer3 << (int)7;
  
      int empty = 0;
      EXPECT_EQ(writer1.write((std::byte*)&empty, 1), 0);
}

TEST(TestSerial, OBinaryFile_MoveConstructorAssignmentVerif) {
  
    serial::IBinaryFile reader(filepath + "/test.bin");
    int val;
    reader >> val;
    EXPECT_EQ(val, 7); 
}

TEST(TestSerial, IBinaryFile_CopySemantics) {
      serial::OBinaryFile out(filepath + "/test.bin");
      out << (int)100 << (int)200;
     }

TEST(TestSerial, IBinaryFile_CopySemanticsVerif) {


    serial::IBinaryFile reader1(filepath + "/test.bin");
    int v1;
    reader1 >> v1;
    EXPECT_EQ(v1, 100);

    // Copie : reader2 doit ouvrir son propre handle indépendant
    serial::IBinaryFile reader2 = reader1; 
    
    // reader1 continue sa lecture
    int v2;
    reader1 >> v2;
    EXPECT_EQ(v2, 200);

    // reader2 recommence-t-il au début ou continue-t-il ?
    // Selon ton implémentation (Copy ctor appelle fopen), 
    // reader2 est un NOUVEAU handle au début du fichier.
    int v3;
    reader2 >> v3;
    EXPECT_EQ(v3, 100); // Doit relire le début
}


int main(int argc, char* argv[]) {
::testing::InitGoogleTest(&argc, argv);
return RUN_ALL_TESTS();
}
