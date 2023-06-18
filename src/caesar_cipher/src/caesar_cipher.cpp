#include <iostream>
#include <fstream>
#include <memory>
#include <sstream>
#include <iomanip>

#include <openssl/evp.h>

#include "caesar_cipher.hpp"
#include "string_ops.hpp"
#include "generators.hpp"

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

    file_path_ = Generators::UniqueFile(".bin");
    
    writeToFile(*ascii_txt);
}

std::string EncryptCaesar::decrypt(const std::string &user_key) {
    
    auto ascii_key = std::make_unique<std::vector<int>>(StringOps::StringToAscii(user_key));
    int sum = 0;
    for (auto itr = ascii_key->begin(); itr != ascii_key->end(); ++itr) {
        sum += *itr;
    }
    sum %= 128; //ensure no overflow+valid ascii range

    auto ascii_txt = std::make_unique<std::vector<int>>(/*ascii ciphertext placeholder*/);
    for (auto itr = ascii_txt->begin(); itr != ascii_txt->end(); ++itr) {
        *itr = (*itr - sum + 95) % 95 + 32; //ensure printable ascii and prevents negative values
    }       
}


void EncryptCaesar::keyHash() {
    unsigned char digest[EVP_MAX_MD_SIZE]; // create a character array to hold the hash
    unsigned int digest_len;

    EVP_MD_CTX* ctx = EVP_MD_CTX_new(); // create a message digest context

    if(!EVP_DigestInit_ex(ctx, EVP_sha256(), NULL)) { // initialize the context with SHA256
        EVP_MD_CTX_free(ctx); // free the context if initialization failed
        throw std::runtime_error("Failed to initialize SHA256 context.");
    }
    if(!EVP_DigestUpdate(ctx, key_.c_str(), key_.size())) { // hash the key
        EVP_MD_CTX_free(ctx); // free the context if hashing failed
        throw std::runtime_error("Failed to update SHA256 context.");
    }
    if(!EVP_DigestFinal_ex(ctx, digest, &digest_len)) { // finalize the hash and store it in digest
        EVP_MD_CTX_free(ctx); // free the context if finalizing the hash failed
        throw std::runtime_error("Failed to finalize SHA256 context.");
    }

    EVP_MD_CTX_free(ctx); // free the context

    std::stringstream ss; // create a stringstream to convert the hash from bytes to a hex string
    for(unsigned int i = 0; i < digest_len; i++)
        ss << std::hex << std::setw(2) << std::setfill('0') << (int)digest[i]; // convert each byte to a two-digit hex number

    key_hash_ = ss.str(); // set the key hash

}



void EncryptCaesar::writeToFile(const std::vector<int> &ciphertext) {
    std::ofstream ofs(file_path_, std::ios::binary);
    
    if (!ofs) {
        throw std::runtime_error("Failed to open file for writing.");
    }
    
    for (const auto &ch : ciphertext) {
        char char_to_write = static_cast<char>(ch);
        ofs.write(&char_to_write, sizeof(char_to_write));
    }
    
    ofs.close();
}

