#ifndef SYMM_ABS_HPP
#define SYMM_ABS_HPP

#include <string>
#include <vector>


class EncryptSymmetric {
    public:
        EncryptSymmetric(std::string key, std::string plain_text = ""); // Constructor

        void encrypt(); // rolled all encryption ops into this     
        std::string decrypt(const std::string &user_key); // handles all decryption, returns decrypted file contents
        
        std::string keyHash(const std::string &key);  // hashes key for storage

        void writeToFile(const std::vector<int> &ciphertext);
        std::vector<int> readFromFile();

    private:
        std::string key_;
        std::string key_hash_;
        std::string key_hash_check_;
        std::string plain_text_;
        std::string file_path_ = "tmp.bin";
       
    };

#endif