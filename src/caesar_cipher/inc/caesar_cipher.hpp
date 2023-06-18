#ifndef CAESAR_LIB_HPP
#define CAESAR_LIB_HPP

#include <openssl/sha.h>
#include <string>
#include <vector>


class EncryptCaesar {
    public:
        EncryptCaesar(std::string key, std::string plain_text); // Constructor
        ~EncryptCaesar(); // Destructor

       std::string encrypt(const std::string &plain_text);     
       std::string decrypt(const std::string &user_key);
        

    private:
        std::string key;
        std::string 
    };

#endif