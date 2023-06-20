#include <iostream>
#include <sstream>

#include "caesar_cipher.hpp"

int main(int argc, char* argv[]) {
    std::string key;

    for (int i = 1; i < argc; i++) {
        if (std::string(argv[i]) == "-k" && i + 1 < argc) {
            key = argv[++i];
        } else {
            std::cerr << "Usage: " << argv[0] << " -k <key>\n";
            return 1;
        }
    }

    try {
        EncryptCaesar cipher(key);
        std::string decrypted_message = cipher.decrypt(key);
        std::cout << "Decrypted message: " << decrypted_message << "\n";
    } catch(const std::runtime_error& e) {
        std::cerr << "An error occurred during decryption: " << e.what() << '\n';
        return 1;
    }

    return 0;
}