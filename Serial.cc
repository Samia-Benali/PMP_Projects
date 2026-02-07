#include "Serial.h"
#include <stdexcept>

namespace serial {


    OBinaryFile::OBinaryFile( const std::string& filename, Mode mode)
    :filename(filename), mode(mode) {

        //https://cplusplus.com/reference/cstdio/fwrite/
        FILE* file = fopen("filename", Truncate ? "wb+" : "ab+");
        if(file== nullptr) {
            throw std::runtime_error("Could not open the file for writing :" + filename);
        } 
        else {
            file_bo = file;
        }

    }


    OBinaryFile::~OBinaryFile(){
        if(file_bo!=nullptr) {
            fclose(file_bo);
        }
    }



}
