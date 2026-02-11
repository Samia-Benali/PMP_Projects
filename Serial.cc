#include "Serial.h"
#include <cstdio>
#include <stdexcept>
#include <utility>

namespace serial {


    //////////////////////////////////////////////////////////////
    //                      IBinaryFile                         //
    //////////////////////////////////////////////////////////////

    //Constructor
    IBinaryFile::IBinaryFile(const std::string& filename) 
    : filename(filename)
    {

        FILE* f = std::fopen(filename.c_str(), "rb");
        if (f == nullptr) {
            throw std::runtime_error("Could not open file for reading: " + filename);
        }
        file_bi = f;
    }

    //Destructor
    IBinaryFile::~IBinaryFile(){
        if (file_bi != nullptr) {
            fclose(file_bi);
        }
    }


    //Copy Constructor
    IBinaryFile::IBinaryFile(const IBinaryFile& other) 
    : IBinaryFile(other.filename) { 
    }

    //Copy Assignment
    IBinaryFile::IBinaryFile(IBinaryFile&& other) noexcept 
    : file_bi(std::exchange(other.file_bi, nullptr)), 
      filename(std::move(other.filename)) {
    }

    //Move Constructor
    IBinaryFile& IBinaryFile::operator=(const IBinaryFile& other) {
        return *this = IBinaryFile(other);
    }

    //Move Assignement
    IBinaryFile& IBinaryFile::operator=(IBinaryFile&& other) noexcept {
        std::swap(file_bi, other.file_bi);
        std::swap(filename, other.filename);
        return *this;
    }

    
    //////////////////////////////////////////////////////////////
    //                      Operator IBinary                    //
    //////////////////////////////////////////////////////////////
    IBinaryFile& operator>>(IBinaryFile& file, uint8_t& x) {
        file.read(reinterpret_cast<std::byte*>(&x), sizeof(x));
        return file;
    }

    IBinaryFile& operator>>(IBinaryFile& file, int8_t& x) {
        file.read(reinterpret_cast<std::byte*>(&x), sizeof(x));
        return file;
    }

    IBinaryFile& operator>>(IBinaryFile& file, uint16_t& x) {
        file.read(reinterpret_cast<std::byte*>(&x), sizeof(x));
        return file;
    }

    IBinaryFile& operator>>(IBinaryFile& file, int16_t& x) {
        file.read(reinterpret_cast<std::byte*>(&x), sizeof(x));
        return file;
    }

    IBinaryFile& operator>>(IBinaryFile& file, uint32_t& x) {
        file.read(reinterpret_cast<std::byte*>(&x), sizeof(x));
        return file;
    }

    IBinaryFile& operator>>(IBinaryFile& file, int32_t& x) {
        file.read(reinterpret_cast<std::byte*>(&x), sizeof(x));
        return file;
    }

    IBinaryFile& operator>>(IBinaryFile& file, uint64_t& x) {
        file.read(reinterpret_cast<std::byte*>(&x), sizeof(x));
        return file;
    }

    IBinaryFile& operator>>(IBinaryFile& file, int64_t& x) {
        file.read(reinterpret_cast<std::byte*>(&x), sizeof(x));
        return file;
    }

    IBinaryFile& operator>>(IBinaryFile& file, char& x) {
        file.read(reinterpret_cast<std::byte*>(&x), sizeof(x));
        return file;
    }

    IBinaryFile& operator>>(IBinaryFile& file, float& x) {
        file.read(reinterpret_cast<std::byte*>(&x), sizeof(x));
        return file;
    }

    IBinaryFile& operator>>(IBinaryFile& file, double& x) {
        file.read(reinterpret_cast<std::byte*>(&x), sizeof(x));
        return file;
    }

    IBinaryFile& operator>>(IBinaryFile& file, bool& x) {
        file.read(reinterpret_cast<std::byte*>(&x), sizeof(x));
        return file;
    }

    IBinaryFile& operator>>(IBinaryFile& file, std::string& x) {
        uint64_t size;
        file >> size;
        x.resize(size);
        if (size > 0) {
            //file.read(reinterpret_cast<std::byte*>(&x[0]), size);
        }
        return file;
    }



    //Read

    std::size_t read(std::byte* data, std::size_t size) {

    }


    //////////////////////////////////////////////////////////////
    //                      OBinaryFile                         //
    /////////////////////////////////////////////////////////////


    //Constructor
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

    //Destructor
    OBinaryFile::~OBinaryFile(){
        if(file_bo != nullptr) {
            std::fclose(file_bo);
        }
    }

    //Move Constructor
    OBinaryFile::OBinaryFile(const OBinaryFile& other)
    : OBinaryFile(other.filename, Append) {
    }

    //Copy Assignment
    OBinaryFile::OBinaryFile(OBinaryFile&& other) noexcept
    : file_bo(std::exchange(other.file_bo, nullptr)), 
      filename(std::move(other.filename)), 
      mode(other.mode) {
    }

    //Move Constructor
    OBinaryFile& OBinaryFile::operator=(const OBinaryFile& other) {
        return *this = OBinaryFile(other);
    }

    //Move Assignment
    OBinaryFile& OBinaryFile::operator=(OBinaryFile&& other) noexcept {
        std::swap(file_bo, other.file_bo);
        std::swap(filename, other.filename);
        std::swap(mode, other.mode);
        return *this;
    }

    //https://www.developpez.net/forums/d1113169/c-cpp/cpp/conversion-little-endian-big-endian-inversement/

    std::size_t OBinaryFile::write(const std::byte* data, std::size_t size) {
        


    }



    //////////////////////////////////////////////////////////////
    //                      Operator OBinary                    //
    /////////////////////////////////////////////////////////////
    OBinaryFile& operator<<(OBinaryFile& file, uint8_t x) {
        file.write(reinterpret_cast<const std::byte*>(&x), sizeof(x));
        return file;
    }

    OBinaryFile& operator<<(OBinaryFile& file, int8_t x) {
        file.write(reinterpret_cast<const std::byte*>(&x), sizeof(x));
        return file;
    }

    OBinaryFile& operator<<(OBinaryFile& file, uint16_t x) {
        file.write(reinterpret_cast<const std::byte*>(&x), sizeof(x));
        return file;
    }

    OBinaryFile& operator<<(OBinaryFile& file, int16_t x) {
        file.write(reinterpret_cast<const std::byte*>(&x), sizeof(x));
        return file;
    }

    OBinaryFile& operator<<(OBinaryFile& file, uint32_t x) {
        file.write(reinterpret_cast<const std::byte*>(&x), sizeof(x));
        return file;
    }

    OBinaryFile& operator<<(OBinaryFile& file, int32_t x) {
        file.write(reinterpret_cast<const std::byte*>(&x), sizeof(x));
        return file;
    }

    OBinaryFile& operator<<(OBinaryFile& file, uint64_t x) {
        file.write(reinterpret_cast<const std::byte*>(&x), sizeof(x));
        return file;
    }

    OBinaryFile& operator<<(OBinaryFile& file, int64_t x) {
        file.write(reinterpret_cast<const std::byte*>(&x), sizeof(x));
        return file;
    }

    OBinaryFile& operator<<(OBinaryFile& file, char x) {
        file.write(reinterpret_cast<const std::byte*>(&x), sizeof(x));
        return file;
    }

    OBinaryFile& operator<<(OBinaryFile& file, float x) {
        file.write(reinterpret_cast<const std::byte*>(&x), sizeof(x));
        return file;
    }

    OBinaryFile& operator<<(OBinaryFile& file, double x) {
        file.write(reinterpret_cast<const std::byte*>(&x), sizeof(x));
        return file;
    }

    OBinaryFile& operator<<(OBinaryFile& file, bool x) {
        file.write(reinterpret_cast<const std::byte*>(&x), sizeof(x));
        return file;
    }

    OBinaryFile& operator<<(OBinaryFile& file, const std::string& x) {
        uint64_t size = x.size();
        file << size;
        if (size > 0) {
            // file.write(reinterpret_cast<const std::byte*>(x.data()), size);
        }
        return file;
    }


}
