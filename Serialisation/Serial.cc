#include "Serial.h"
#include <cstdio>
#include <utility>
#include <cstdint>
#include <cstring> 
#include <cstddef> 
#include <stdexcept>
#include <string>
#include <vector>
#include <map>
#include <set>

namespace {


    template <typename T>
    void to_bytes(T val, std::byte* buf) {
        // https://en.cppreference.com/w/cpp/types/make_unsigned.html
        using U = std::make_unsigned_t<T>;
        U uval = static_cast<U>(val);

        if constexpr (sizeof(T) == 2) {
            buf[0] = static_cast<std::byte>((uval >> 8) & 0xFF);
            buf[1] = static_cast<std::byte>(uval & 0xFF);
        }
        else if constexpr (sizeof(T) == 4) {
            buf[0] = static_cast<std::byte>((uval >> 24) & 0xFF);
            buf[1] = static_cast<std::byte>((uval >> 16) & 0xFF);
            buf[2] = static_cast<std::byte>((uval >> 8) & 0xFF);
            buf[3] = static_cast<std::byte>(uval & 0xFF);
        }
        else if constexpr (sizeof(T) == 8) {
            buf[0] = static_cast<std::byte>((uval >> 56) & 0xFF);
            buf[1] = static_cast<std::byte>((uval >> 48) & 0xFF);
            buf[2] = static_cast<std::byte>((uval >> 40) & 0xFF);
            buf[3] = static_cast<std::byte>((uval >> 32) & 0xFF);
            buf[4] = static_cast<std::byte>((uval >> 24) & 0xFF);
            buf[5] = static_cast<std::byte>((uval >> 16) & 0xFF);
            buf[6] = static_cast<std::byte>((uval >> 8) & 0xFF);
            buf[7] = static_cast<std::byte>(uval & 0xFF);
        }
    }

    template <typename T>
    T from_bytes(const std::byte* buf) {
        using U = std::make_unsigned_t<T>;
        U uval = 0;

        if constexpr (sizeof(T) == 2) {
            uval = (static_cast<U>(buf[0]) << 8) |
                   (static_cast<U>(buf[1]));
        }
        else if constexpr (sizeof(T) == 4) {
            uval = (static_cast<U>(buf[0]) << 24) |
                   (static_cast<U>(buf[1]) << 16) |
                   (static_cast<U>(buf[2]) << 8)  |
                   (static_cast<U>(buf[3]));
        }
        else if constexpr (sizeof(T) == 8) {
            uval = (static_cast<U>(buf[0]) << 56) |
                   (static_cast<U>(buf[1]) << 48) |
                   (static_cast<U>(buf[2]) << 40) |
                   (static_cast<U>(buf[3]) << 32) |
                   (static_cast<U>(buf[4]) << 24) |
                   (static_cast<U>(buf[5]) << 16) |
                   (static_cast<U>(buf[6]) << 8)  |
                   (static_cast<U>(buf[7]));
        }
        
        return static_cast<T>(uval);
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

    IBinaryFile::IBinaryFile(IBinaryFile&& other) noexcept  
    : file_bi(std::exchange(other.file_bi, nullptr)),  
      filename(std::move(other.filename)) {
    } 

    IBinaryFile& IBinaryFile::operator=(IBinaryFile&& other) noexcept {
        if (this != &other) { 
            if (file_bi) fclose(file_bi); 
            file_bi = std::exchange(other.file_bi, nullptr);
            filename = std::move(other.filename);
        }
        return *this;
    }

    std::size_t IBinaryFile::read(std::byte* data, std::size_t size) {
        std::size_t reading = std::fread(data, 1, size, file_bi);
        if (reading < size) {
             perror("Read couldn't work");
             throw std::runtime_error("Read error");
             return reading;
        }
        return reading;
    }

    
    //////////////////////////////////////////////////////////////
    //                      Operator IBinary                    //
    //////////////////////////////////////////////////////////////

    template<typename T>
    void read_type(IBinaryFile& file, T& x) {
        std::byte buffer[sizeof(T)];
        file.read(buffer, sizeof(T));
        x = from_bytes<T>(buffer);
    }

    IBinaryFile& operator>>(IBinaryFile& file, uint8_t& x) {
        file.read(reinterpret_cast<std::byte*>(&x), 1);
        return file;
    }

    IBinaryFile& operator>>(IBinaryFile& file, int8_t& x) {
        file.read(reinterpret_cast<std::byte*>(&x), 1);
        return file;
    }

    IBinaryFile& operator>>(IBinaryFile& file, uint16_t& x) { 
        read_type(file, x); return file; 
    }
    IBinaryFile& operator>>(IBinaryFile& file, int16_t& x)  { 
        read_type(file, x); return file; 
    }
    IBinaryFile& operator>>(IBinaryFile& file, uint32_t& x) { 
        read_type(file, x); return file; 
    }
    IBinaryFile& operator>>(IBinaryFile& file, int32_t& x)  { 
        read_type(file, x); return file; 
    }
    IBinaryFile& operator>>(IBinaryFile& file, uint64_t& x) { 
        read_type(file, x); return file; 
    }
    IBinaryFile& operator>>(IBinaryFile& file, int64_t& x)  { 
        read_type(file, x); return file; 
    }

    IBinaryFile& operator>>(IBinaryFile& file, char& x) {
        file.read(reinterpret_cast<std::byte*>(&x), 1);
        return file;
    }

    IBinaryFile& operator>>(IBinaryFile& file, float& x) {
        uint32_t temp;
        read_type(file, temp);
        std::memcpy(&x, &temp, sizeof(float));
        return file;
    }

    IBinaryFile& operator>>(IBinaryFile& file, double& x) {
        uint64_t temp;
        read_type(file, temp);
        std::memcpy(&x, &temp, sizeof(double));
        return file;
    }

    IBinaryFile& operator>>(IBinaryFile& file, bool& x) {
        uint8_t temp;
        file >> temp;
        x = (temp != 0);
        return file;
    }

    IBinaryFile& operator>>(IBinaryFile& file, std::string& x) {
        uint64_t size;
        file >> size; 
        x.resize(size);
        if (size > 0) {
            file.read(reinterpret_cast<std::byte*>(x.data()), size);
        }
        return file;
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

    OBinaryFile::OBinaryFile(OBinaryFile&& other) noexcept
    : file_bo(std::exchange(other.file_bo, nullptr)),  
      filename(std::move(other.filename)),  
      mode(other.mode) {
    } 

    OBinaryFile& OBinaryFile::operator=(OBinaryFile&& other) noexcept {
        if (this != &other) {
            if (file_bo) fclose(file_bo);
            file_bo = std::exchange(other.file_bo, nullptr);
            filename = std::move(other.filename);
            mode = other.mode;
        }
        return *this;
    }

    //https://www.developpez.net/forums/d1113169/c-cpp/cpp/conversion-little-endian-big-endian-inversement/

    std::size_t OBinaryFile::write(const std::byte* data, std::size_t size) {
        std::size_t writting = fwrite(data,1,size,file_bo);
        if(writting < size) {
            perror("Write couldn't work");
            throw std::runtime_error("Write error");
            return writting;
        }
        return writting;
    }



    //////////////////////////////////////////////////////////////
    //                      Operator OBinary                    //
    /////////////////////////////////////////////////////////////
    
    template<typename T>
    void write_type(OBinaryFile& file, T x) {
        std::byte buffer[sizeof(T)];
        to_bytes(x, buffer); 
        file.write(buffer, sizeof(T));  
    }

    OBinaryFile& operator<<(OBinaryFile& file, uint8_t x) {
        file.write(reinterpret_cast<const std::byte*>(&x), 1);
        return file;
    }
    
    OBinaryFile& operator<<(OBinaryFile& file, int8_t x) {
        file.write(reinterpret_cast<const std::byte*>(&x), 1);
        return file;
    }

    OBinaryFile& operator<<(OBinaryFile& file, uint16_t x) { 
        write_type(file, x); return file; 
    }

    OBinaryFile& operator<<(OBinaryFile& file, int16_t x)  { 
        write_type(file, x); return file; 
    }

    OBinaryFile& operator<<(OBinaryFile& file, uint32_t x) { 
        write_type(file, x); return file; 
    }

    OBinaryFile& operator<<(OBinaryFile& file, int32_t x)  { 
        write_type(file, x); return file; 
    }
    OBinaryFile& operator<<(OBinaryFile& file, uint64_t x) { 
        write_type(file, x); return file; 
    }

    OBinaryFile& operator<<(OBinaryFile& file, int64_t x)  { 
        write_type(file, x); return file; 
    }

    OBinaryFile& operator<<(OBinaryFile& file, char x) {
        file.write(reinterpret_cast<const std::byte*>(&x), 1);
        return file;
    }

    OBinaryFile& operator<<(OBinaryFile& file, float x) {
        uint32_t temp;
        std::memcpy(&temp, &x, sizeof(float));
        write_type(file, temp);
        return file;
    }

    OBinaryFile& operator<<(OBinaryFile& file, double x) {
        uint64_t temp;
        std::memcpy(&temp, &x, sizeof(double));
        write_type(file, temp);
        return file;
    }

    OBinaryFile& operator<<(OBinaryFile& file, bool x) {
        uint8_t temp = x ? 1 : 0;
        file << temp;
        return file;
    }

    OBinaryFile& operator<<(OBinaryFile& file, const std::string& x) {
        uint64_t size = x.size();
        file << size;
        if (size > 0) {
            file.write(reinterpret_cast<const std::byte*>(x.data()), size);
        }
        return file;
    }
}