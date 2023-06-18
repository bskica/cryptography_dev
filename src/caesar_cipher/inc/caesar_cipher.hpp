#ifndef CAESAR_LIB_HPP
#define CAESAR_LIB_HPP

#include <openssl/sha.h>
#include <string>
#include <vector>


class EncryptCaesar {
    public:
        EncryptCaesar(std::string key, std::string plain_text); // Constructor
        ~EncryptCaesar(); // Destructor

        void encrypt(const std::string &plain_text);     
        std::string decrypt(const std::string &user_key);
        
        void keyHash();

        void writeToFile(const std::vector<int> &ciphertext);
        void readFromFile();

    private:
        std::string key_;
        std::string key_hash_;
        std::string plain_text_;
        std::string file_path_;
       
    };

#endif