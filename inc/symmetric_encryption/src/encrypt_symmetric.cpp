#include <iostream>
#include <fstream>
#include <memory>
#include <sstream>
#include <iomanip>
#include <cstdio>

#include <openssl/evp.h>

#include "caesar_cipher.hpp"
#include "string_ops.hpp"
#include "generators.hpp"


EncryptCaesar::EncryptCaesar(std::string key, std::string plain_text) 
    : key_(std::move(key)), plain_text_(std::move(plain_text)) {
}

void EncryptCaesar::encrypt() {

    auto ascii_key = std::make_unique<std::vector<int>>(StringOps::StringToAscii(key_));
    int sum = 0;
    for (auto itr = ascii_key->begin(); itr != ascii_key->end(); ++itr) {
        sum += *itr;
    }
    sum %= 128; //ensure no overflow+valid ascii range
    auto ascii_txt = std::make_unique<std::vector<int>>(StringOps::StringToAscii(plain_text_));
    for (auto itr = ascii_txt->begin(); itr != ascii_txt->end(); ++itr) {
        *itr = ((*itr + sum - 32) % 95) + 32; //ensures the values are printable
    }       

    key_hash_ = keyHash(key_); //hashes key, stores in key_hash_
    
    //write everything to file
    //std::string tmp = Generators::UniqueFile(".bin"); design error,tbd fix
    //file_path_ = "tmp.bin";
    writeToFile(*ascii_txt); 


    //wipe private variables just to make sure
    key_.clear();
    key_hash_.clear();
    plain_text_.clear();

}

std::string EncryptCaesar::decrypt(const std::string &user_key) {

    auto ascii_key = std::make_unique<std::vector<int>>(StringOps::StringToAscii(user_key));
    int sum = 0;
    for (auto itr = ascii_key->begin(); itr != ascii_key->end(); ++itr) {
        sum += *itr;
    }
    sum %= 128; //ensure no overflow+valid ascii range

    auto ascii_txt = std::make_unique<std::vector<int>>(readFromFile());
    for (auto itr = ascii_txt->begin(); itr != ascii_txt->end(); ++itr) {
        *itr = ((*itr - sum - 32 + 95) % 95) + 32; //ensure printable ascii and prevents negative values
    }       

    if (std::remove(file_path_.c_str()) != 0) {
        throw std::runtime_error("Failed to delete the file.");
    }

    key_hash_check_ = keyHash(user_key);


    if (key_hash_check_ != key_hash_) {
        throw std::runtime_error("Incorrect key. Please try again");
    } else {
        std::string result;
        for (const auto &ch : *ascii_txt) {
            result += static_cast<char>(ch);
        }
        return result;
    }

}


std::string EncryptCaesar::keyHash(const std::string &key) {
    unsigned char digest[EVP_MAX_MD_SIZE]; // create a character array to hold the hash
    unsigned int digest_len;

    EVP_MD_CTX* ctx = EVP_MD_CTX_new(); // create a message digest context

    if(!EVP_DigestInit_ex(ctx, EVP_sha256(), NULL)) { // initialize the context with SHA256
        EVP_MD_CTX_free(ctx); // free the context if initialization failed
        throw std::runtime_error("Failed to initialize SHA256 context.");
    }
    if(!EVP_DigestUpdate(ctx, key.c_str(), key.size())) { // hash the key
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

    return ss.str();

}



void EncryptCaesar::writeToFile(const std::vector<int> &ciphertext) {
    std::ofstream ofs(file_path_, std::ios::binary);
    
    if (!ofs) {
        throw std::runtime_error("Failed to open file for writing.");
    }

    ofs.write(key_hash_.c_str(), key_hash_.size());

    for (const auto &ch : ciphertext) {
        char char_to_write = static_cast<char>(ch);
        ofs.write(&char_to_write, sizeof(char_to_write));
    }
    
    ofs.close();
}

std::vector<int> EncryptCaesar::readFromFile() {
    
    std::ifstream ifs(file_path_, std::ios::binary);

    if (!ifs) {
        throw std::runtime_error("Failed to open file for reading.");
    }

    std::vector<char> hash_chars(64);
    ifs.read(hash_chars.data(), 64);
    key_hash_ = std::string(hash_chars.begin(), hash_chars.end()); //overwrites key_hash_

    std::vector<int> cipher_text;
    char ch;
    while (ifs.read(&ch, sizeof(ch))) {
        cipher_text.push_back(static_cast<int>(ch));
    }
    
    ifs.close();

    return cipher_text;

}