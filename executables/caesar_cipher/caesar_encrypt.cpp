#include <iostream>
#include <stdexcept>

#include "caesar_cipher.hpp"

int main(int argc, char* argv[]) {
    std::string key;
    std::string message;

    for (int i = 1; i < argc; i++) {
        if (std::string(argv[i]) == "-k" && i + 1 < argc) {
            key = argv[++i];
        } else if (std::string(argv[i]) == "-m" && i + 1 < argc) {
            message = argv[++i];
        } else {
            std::cerr << "Usage: " << argv[0] << " -k <key> -m <message>\n";
            return 1;
        }
    }

    try {
        EncryptCaesar cipher(key, message);
        cipher.encrypt();
    } catch(const std::runtime_error& e) {
        std::cerr << "An error occurred during encryption: " << e.what() << '\n';
        return 1;
    }

    return 0;
}