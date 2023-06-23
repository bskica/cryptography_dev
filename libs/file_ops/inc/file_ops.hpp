#ifndef GENERATORS_HPP
#define GENERATORS_HPP

#include <string>
#include <vector>
#include <optional>

constexpr size_t SHA256_HASH_LENGTH = 64;

/**
 * @brief Namespace containing utilities for file I/O
 *  
 * This namespace contains an assortment of helper functions for file operations  
 *  
 */

namespace FileOps{

    /**
    * @brief Generates a unique filename for temporary files
    *
    * @param[in] param1 File location path  [Default = current dir]
    * @param[in] param2 File extension type [Default = text file]
    * @return std::string containing a unique filename
    * 
    */
    std::string UniqueFile(std::string path = "./", std::string extension = ".bin");


    /**
    * @brief Writes the given data to a file
    *
    * Writes the given data and an optional hash value to a file with the given filename. The file is
    * overwritten if it already exists. Can handle either strings or vectors of 
    * 8-bit text formats (ASCII & UTF-8)
    *
    * @tparam T The type of data being written to the file. This can be either a 
    *           std::string or a std::vector<uint8_t>
    *         
    * @param[in] filename  The name of the file to write to
    * @param[in] inputtext The data to write to the file
    * @param[in] hash      Optional input for writing a SHA256 value to the file alongside data
    * 
    * @throws std::runtime_error if an I/O error occurs.
    */
    template <typename T>
    void writeToFile(const std::string &filename, const T &inputtext, const std::optional<std::string> &hash);


    /**
    * @brief Reads file contents into a specified container
    *
    * Reads the contents of the specified file into a string or 8-bit vector to simplify 
    * swapping between text representations. If the file contains a hash, it will be stored in
    * the optional hash parameter
    *         
    * @param[in] filename  The name of the file to write to
    * @param[in] inputtext The data to write to the file
    * @param[out] hash     Optional parameter for storing a SHA256 hashfrom the file 
    * @return This can be either a std::string or a std::vector<uint8_t>
    * 
    * @throws std::runtime_error if an I/O error occurs.
    */
    template <typename T>
    T readFromFile(const std::string &filename, std::optional<std::string> &hash);

}


#endif  