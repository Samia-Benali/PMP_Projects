#include "Serial.h"
#include <cstdio>
#include <stdexcept>

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
    IBinaryFile::IBinaryFile(const IBinaryFile& other): IBinaryFile(other.filename) { 
    }

    IBinaryFile& IBinaryFile::operator=(const IBinaryFile& other) {
        if (this != &other) {
            *this = IBinaryFile(other);
        }
        return *this;
    }

    // IBinaryFile::IBinaryFile(IBinaryFile&& other) noexcept : 
    // file_bi(std::__exchange(other.file_bi, nullptr)), filename(std::move(other.filename)) {
    // }

    // IBinaryFile& IBinaryFile::operator=(IBinaryFile&& other) noexcept {
    //     if (this != &other) {
    //         std::swap(file_bi, other.file_bi);
    //         std::swap(filename, other.filename);
    //     }
    //     return *this;
    // }




}
