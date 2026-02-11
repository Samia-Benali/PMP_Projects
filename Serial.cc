#include "Serial.h"
#include <cstdio>
#include <stdexcept>
#include <utility>

namespace serial {

    IBinaryFile::IBinaryFile(const std::string& filename) 
    : filename(filename)
    {

        FILE* f = std::fopen(filename.c_str(), "rb");
        if (f == nullptr) {
            throw std::runtime_error("Could not open file for reading: " + filename);
        }
        file_bi = f;
    }

    IBinaryFile::~IBinaryFile(){
        if (file_bi != nullptr) {
            fclose(file_bi);
        }
    }

    IBinaryFile::IBinaryFile(const IBinaryFile& other) 
    : IBinaryFile(other.filename) { 
    }

    IBinaryFile::IBinaryFile(IBinaryFile&& other) noexcept 
    : file_bi(std::exchange(other.file_bi, nullptr)), 
      filename(std::move(other.filename)) {
    }

    IBinaryFile& IBinaryFile::operator=(const IBinaryFile& other) {
        return *this = IBinaryFile(other);
    }

    IBinaryFile& IBinaryFile::operator=(IBinaryFile&& other) noexcept {
        std::swap(file_bi, other.file_bi);
        std::swap(filename, other.filename);
        return *this;
    }



    OBinaryFile::OBinaryFile( const std::string& filename, Mode mode)
    :filename(filename), mode(mode) {

        //https://cplusplus.com/reference/cstdio/fwrite/
        FILE* file = fopen(filename.c_str(), (mode == Truncate) ? "wb+" : "ab+");
        if(file== nullptr) {
            throw std::runtime_error("Could not open the file for writing :" + filename);
        } 
        else {
            file_bo = file;
        }

    }

    OBinaryFile::~OBinaryFile(){
        if(file_bo != nullptr) {
            std::fclose(file_bo);
        }
    }

    OBinaryFile::OBinaryFile(const OBinaryFile& other)
    : OBinaryFile(other.filename, Append) {
    }

    OBinaryFile::OBinaryFile(OBinaryFile&& other) noexcept
    : file_bo(std::exchange(other.file_bo, nullptr)), 
      filename(std::move(other.filename)), 
      mode(other.mode) {
    }

    OBinaryFile& OBinaryFile::operator=(const OBinaryFile& other) {
        return *this = OBinaryFile(other);
    }

    OBinaryFile& OBinaryFile::operator=(OBinaryFile&& other) noexcept {
        std::swap(file_bo, other.file_bo);
        std::swap(filename, other.filename);
        std::swap(mode, other.mode);
        return *this;
    }



}
