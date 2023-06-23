#include <chrono>
#include <sstream>
#include <fstream>
#include <iostream>

#include "file_ops.hpp"

namespace FileOps {

    std::string UniqueFile(std::string path, std::string extension) {
        if (!path.empty() && path.back() != '/') {
            path += '/';
        }
        if (!extension.empty() && extension.front() != '.') {
            extension = "." + extension;
        }

        auto now = std::chrono::system_clock::now();
        auto time_since_epoch = now.time_since_epoch();
        auto unique_time = std::chrono::duration_cast<std::chrono::milliseconds>(time_since_epoch).count();

        std::ostringstream oss;
        oss << path << "gen_file_" << unique_time << extension;

        return oss.str();
    }


    template <>
    void writeToFile<std::string>(const std::string &filename, const std::string &input_text, const std::optional<std::string> &hash) {
        std::ofstream ofs(filename, std::ios::binary);

        if (!ofs) {
            throw std::runtime_error("Failed to open file for writing");
        }
        if (hash) {
            ofs.write(hash.value().c_str(), hash.value().size());
        }

        ofs.write(input_text.c_str(), input_text.size());
        ofs.close();
    }


    template <>
    void writeToFile<std::vector<uint8_t>>(const std::string &filename, const std::vector<uint8_t> &input_text, 
                                           const std::optional<std::string> &hash) {
        std::ofstream ofs(filename, std::ios::binary);

        if (!ofs) {
            throw std::runtime_error("Failed to open file for writing");
        }
        if (hash) {
            ofs.write(hash.value().c_str(), hash.value().size());
        }

        for (const auto &ch : input_text) {
            char char_to_write = static_cast<char>(ch);
            ofs.write(&char_to_write, sizeof(char_to_write));
        }

        ofs.close();
    }


    template <>
    std::string readFromFile(const std::string &filename, std::optional<std::string> &hash) {
        std::ifstream ifs(filename, std::ios::binary);
    
        if (!ifs) {
            throw std::runtime_error("Failed to open file for reading.");
        }

        if (hash) {
            if (!hash.has_value()) {
                std::vector<char> hash_chars(SHA256_HASH_LENGTH);
                ifs.read(hash_chars.data(), SHA256_HASH_LENGTH);
                hash = std::string(hash_chars.begin(), hash_chars.end()); //overwrites key_hash_
            } 
        }
         
        std::vector<char> buffer(std::istreambuf_iterator<char>(ifs), {});
        std::string filedata(buffer.begin(), buffer.end());
        ifs.close();

        return filedata;
    } 


    template <>
    std::vector<uint8_t> readFromFile(const std::string &filename, std::optional<std::string> &hash) {
        std::ifstream ifs(filename, std::ios::binary);

        if (!ifs) {
            throw std::runtime_error("Failed to open file for reading");
        }
        
        if (hash) {
            std::vector<char> hash_chars(SHA256_HASH_LENGTH);
            ifs.read(hash_chars.data(), SHA256_HASH_LENGTH);
            hash = std::string(hash_chars.begin(), hash_chars.end()); //overwrites key_hash_
        }
         
        std::vector<uint8_t> buffer(std::istreambuf_iterator<char>{ifs}, {});
        ifs.close();

        return buffer;    
    }






}
