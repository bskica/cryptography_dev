#include <iostream>
#include <fstream>
#include <memory>

#include "caesar_cipher.hpp"
#include "string_ops.hpp"

void EncryptCaesar::encrypt(const std::string& input) {
    
    auto ascii_key = std::make_unique<std::vector<int>>(StringOps::StringToAscii(key_));
    int sum = 0;
    for (auto itr = ascii_key->begin(); itr != ascii_key->end(); ++itr) {
        sum += *itr;
    }
    sum %= 128; //ensure no overflow+valid ascii range
    auto ascii_txt = std::make_unique<std::vector<int>>(StringOps::StringToAscii(input));
    for (auto itr = ascii_txt->begin(); itr != ascii_txt->end(); ++itr) {
        *itr = (*itr + sum) % 95 + 32;
    }       


}

void EncryptCaesar::decrypt(const std::string &user_key) {
    
    auto ascii_key = std::make_unique<std::vector<int>>(StringOps::StringToAscii(user_key));
    int sum = 0;
    for (auto itr = ascii_key->begin(); itr != ascii_key->end(); ++itr) {
        sum += *itr;
    }
    sum %= 128; //ensure no overflow+valid ascii range

    auto ascii_txt = std::make_unique<std::vector<int>>(/*ascii ciphertext placeholder*/);
    for (auto itr = ascii_txt->begin(); itr != ascii_txt->end(); ++itr) {
        *itr = (*itr - sum + 95) % 95 + 32; //ensure printable ascii
    }       
}