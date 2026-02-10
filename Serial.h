#ifndef SERIAL_H
#define SERIAL_H

#include <cstddef>
#include <cstdint>

#include <array>
#include <map>
#include <set>
#include <string>
#include <vector>

namespace serial {

  /**
   * @brief A file to be written
   */
  class OBinaryFile {
  public:
    /**
     * @brief The mode for opening the file
     */
    enum Mode {
      Truncate,
      Append,
    };

    /**
     * @brief Constructor
     *
     * Opens the file for writing or throws a `std::runtime_error` in case of
     * error.
     */
    OBinaryFile(const std::string& filename, Mode mode = Truncate);

    ~OBinaryFile();
    OBinaryFile(const OBinaryFile& other);
    OBinaryFile& operator=(const OBinaryFile& other);
    OBinaryFile(OBinaryFile&& other) noexcept;
    OBinaryFile& operator=(OBinaryFile&& other) noexcept;




    /**
     * @brief Write `size` bytes pointed by `data` in the file
     *
     * Returns the number of bytes actually written
     */
    std::size_t write(const std::byte* data, std::size_t size);


    private:

      FILE* file_bo;
      std::string filename;
      Mode mode;
  };



  /**
   * @brief A file to be read
   */
  class IBinaryFile {
  public:
    /**
     * @brief Constructor
     *
     * Opens the file for reading or throws a `std::runtime_error` in case of
     * error.
     */
    IBinaryFile(const std::string& filename);

    ~IBinaryFile();
    IBinaryFile(const IBinaryFile& other);
    IBinaryFile& operator=(const IBinaryFile& other);
    IBinaryFile(IBinaryFile&& other) noexcept;
    IBinaryFile& operator=(IBinaryFile&& other) noexcept;


    /**
     * @brief Read `size` bytes from the file and store them in the buffer
     * pointed by `data`.
     *
     * Returns the number of bytes actually read.
     */
    std::size_t read(std::byte* data, std::size_t size);

  private:
    FILE* file_bi;
    std::string filename;
  };


  OBinaryFile& operator<<(OBinaryFile& file, uint8_t x);
  OBinaryFile& operator<<(OBinaryFile& file, int8_t x);
  OBinaryFile& operator<<(OBinaryFile& file, uint16_t x);
  OBinaryFile& operator<<(OBinaryFile& file, int16_t x);
  OBinaryFile& operator<<(OBinaryFile& file, uint32_t x);
  OBinaryFile& operator<<(OBinaryFile& file, int32_t x);
  OBinaryFile& operator<<(OBinaryFile& file, uint64_t x);
  OBinaryFile& operator<<(OBinaryFile& file, int64_t x);
  OBinaryFile& operator<<(OBinaryFile& file, char x);
  OBinaryFile& operator<<(OBinaryFile& file, float x);
  OBinaryFile& operator<<(OBinaryFile& file, double x);
  OBinaryFile& operator<<(OBinaryFile& file, bool x);
  OBinaryFile& operator<<(OBinaryFile& file, const std::string& x);

  template<typename T>
  OBinaryFile& operator<<(OBinaryFile& file, const std::vector<T>& x) {
    uint64_t size = x.size();
    file << size;
    for(const auto& val : x){
      file << val;
    }
    return file;
  }

  template<typename T, std::size_t N>
  OBinaryFile& operator<<(OBinaryFile& file, const std::array<T,N>& x) {
    for(const auto& val : x) {
        file << val;
    }
    return file;
  }

  template<typename K, typename V>
  OBinaryFile& operator<<(OBinaryFile& file, const std::map<K,V>& x) {
    uint64_t size = x.size();
    file << size;
    for(const auto& pair : x) {
        file << pair.first << pair.second;
    }
    return file;
  }

  template<typename T>
  OBinaryFile& operator<<(OBinaryFile& file, const std::set<T>& x) {
    uint64_t size = x.size();
    file << size;
    for(const auto& val : x) {
        file << val;
    }
    return file;
  }

  IBinaryFile& operator>>(IBinaryFile& file, int8_t& x);
  IBinaryFile& operator>>(IBinaryFile& file, uint8_t& x);
  IBinaryFile& operator>>(IBinaryFile& file, int16_t& x);
  IBinaryFile& operator>>(IBinaryFile& file, uint16_t& x);
  IBinaryFile& operator>>(IBinaryFile& file, int32_t& x);
  IBinaryFile& operator>>(IBinaryFile& file, uint32_t& x);
  IBinaryFile& operator>>(IBinaryFile& file, int64_t& x);
  IBinaryFile& operator>>(IBinaryFile& file, uint64_t& x);
  IBinaryFile& operator>>(IBinaryFile& file, char& x);
  IBinaryFile& operator>>(IBinaryFile& file, float& x);
  IBinaryFile& operator>>(IBinaryFile& file, double& x);
  IBinaryFile& operator>>(IBinaryFile& file, bool& x);
  IBinaryFile& operator>>(IBinaryFile& file, std::string& x);

  template<typename T>
  IBinaryFile& operator>>(IBinaryFile& file, std::vector<T>& x) {
    uint64_t size;
    file >> size;
    x.resize(size);
    for(std::size_t i = 0; i < size; ++i) {
        file >> x[i];
    }
    return file;
  }

  template<typename T, std::size_t N>
  IBinaryFile& operator>>(IBinaryFile& file, std::array<T, N>& x) {
    for(std::size_t i = 0; i < N; ++i) {
        file >> x[i];
    }
    return file;
  }

  template<typename K, typename V>
  IBinaryFile& operator>>(IBinaryFile& file, std::map<K, V>& x) {
    x.clear();
    uint64_t size;
    file >> size;
    for(std::size_t i = 0; i < size; ++i) {
        K key;
        V value;
        file >> key >> value;
        x.insert({key, value});
    }
    return file;
  }

  template<typename T>
  IBinaryFile& operator>>(IBinaryFile& file, std::set<T>& x) {
    x.clear();
    uint64_t size;
    file >> size;
    for(std::size_t i = 0; i < size; ++i) {
        T val;
        file >> val;
        x.insert(val);
    }
    return file;
  }

} // namespace serial

#endif // SERIAL_H
