#include "Serial.h"
#include <cstdio>
#include <stdexcept>
#include <utility>

namespace {

  // https://keasigmadelta.com/blog/how-to-convert-endianness-in-c-c-in-4-different-ways/
    uint16_t swap16(uint16_t val) {
        return ((0xFF00 & val ) >> 8) | ((0xFF00 & val ) << 8);
    }

    uint32_t swap32(uint32_t val) {
        return ((0xFF00000000 & val) >> 24) |
         ((0x000000FF & val) << 24) |
         ((0x00FF0000 & val ) >> 8) |
         ((0x00FF0000 & val ) << 8);
    }

    uint64_t swap64(uint64_t val) {
        return ((0xFF00000000000000 & val) >> 56) |
         ((0x00000000000000FF & val) << 56) | 
         ((0x00FF000000000000 & val) >> 40) | 
         ((0x000000000000FF00 & val) >> 40) | 
         ((0x0000FF0000000000 & val) >> 24) | 
         ((0x0000000000FF0000 & val) << 24) | 
          ((0x000000FF00000000 & val) >> 8) | 
          ((0x00000000FF000000 & val) << 8) ;
    }


    template <typename T>
    T swap_endian(T val) {
        if (sizeof(T) == 1){
            return val;
        }
        if(T is uint16_t)
        {
          swap16(val);
        }
        else if(T is uint32_t)
        {
          swap32(val);
        }
        else if (T is u_int64_t)
        {
          swap64(val);
        }
    }

}


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
        uint16_t temp;
        file.read(reinterpret_cast<std::byte*>(&temp), sizeof(temp));
        x = swap_endian(temp);
        return file;
    }

    IBinaryFile& operator>>(IBinaryFile& file, int16_t& x) {
        uint16_t temp;
        file.read(reinterpret_cast<std::byte*>(&temp), sizeof(temp));
        x = static_cast<int16_t>(swap_endian(temp));
        return file;
    }

    IBinaryFile& operator>>(IBinaryFile& file, uint32_t& x) {
        uint32_t temp;
        file.read(reinterpret_cast<std::byte*>(&temp), sizeof(temp));
        x = swap_endian(temp);
        return file;
    }

    IBinaryFile& operator>>(IBinaryFile& file, int32_t& x) {
        uint32_t temp;
        file.read(reinterpret_cast<std::byte*>(&temp), sizeof(temp));
        x = static_cast<int32_t>(swap_endian(temp));
        return file;
    }

    IBinaryFile& operator>>(IBinaryFile& file, uint64_t& x) {
        uint64_t temp;
        file.read(reinterpret_cast<std::byte*>(&temp), sizeof(temp));
        x = swap_endian(temp);

        return file;
    }

    IBinaryFile& operator>>(IBinaryFile& file, int64_t& x) {
        uint64_t temp;
        file.read(reinterpret_cast<std::byte*>(&temp), sizeof(temp));
        x = static_cast<int64_t>(swap_endian(temp));
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
            file.read(reinterpret_cast<std::byte*>(&x[0]), size);
        }
        return file;
    }

    //Read
    std::size_t IBinaryFile::read(std::byte* data, std::size_t size) {
        if (file_bi == nullptr){
            return 0;
        } 
        std::size_t res = std::fread(data, 1, size, file_bi);
        if (res < size){
            perror("fread");
            return res;
        }
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

    //Write
    std::size_t OBinaryFile::write(const std::byte* data, std::size_t size) {
        std::size_t writting = fwrite(data,1,size,file_bo);
        if(writting < size) {
            perror("Write couldn't work");
            return writting;
        }
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
        uint16_t temp = x;
        uint16_t swapped = swap_endian(temp);
        file.write(reinterpret_cast<const std::byte*>(&swapped), sizeof(x));
        return file;
    }

    OBinaryFile& operator<<(OBinaryFile& file, int16_t x) {
        uint16_t temp = static_cast<uint16_t>(x);
        uint16_t swapped = swap_endian(temp);
        file.write(reinterpret_cast<const std::byte*>(&swapped), sizeof(x));
        return file;
    }

    OBinaryFile& operator<<(OBinaryFile& file, uint32_t x) {
        uint16_t temp = x;
        uint16_t swapped = swap_endian(temp);
        file.write(reinterpret_cast<const std::byte*>(&swapped), sizeof(x));
        return file;
    }

    OBinaryFile& operator<<(OBinaryFile& file, int32_t x) {
        uint32_t temp = static_cast<uint32_t>(x);
        uint32_t swapped = swap_endian(temp);
        file.write(reinterpret_cast<const std::byte*>(&swapped), sizeof(x));
        return file;
    }

    OBinaryFile& operator<<(OBinaryFile& file, uint64_t x) {
        uint64_t temp = x;
        uint64_t swapped = swap_endian(temp);
        file.write(reinterpret_cast<const std::byte*>(&swapped), sizeof(x));
        return file;
    }

    OBinaryFile& operator<<(OBinaryFile& file, int64_t x) {
        uint64_t temp = static_cast<uint64_t>(x);
        uint64_t swapped = swap_endian(temp);
        file.write(reinterpret_cast<const std::byte*>(&swapped), sizeof(x));
        return file;
    }

    OBinaryFile& operator<<(OBinaryFile& file, char x) {
        uint8_t temp = x;
        uint8_t swapped = swap_endian(temp);
        file.write(reinterpret_cast<const std::byte*>(&swapped), sizeof(x));
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

    // OBinaryFile& operator<<(OBinaryFile& file, const std::string& x) {
    //     uint64_t temp = x;
    //     uint64_t swapped = swap_endian(temp);
    //     uint64_t size = swapped.size();
    //     file << size;
    //     if (size > 0) {
    //         file.write(reinterpret_cast<const std::byte*>(swapped.data()), size);
    //     }
    //     return file;
    // }


}




