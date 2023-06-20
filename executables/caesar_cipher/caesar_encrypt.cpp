#include <iostream>
#include <stdexcept>

#include "caesar_cipher.hpp"

int main(int argc, char* argv[]) {
    std::string key;
    std::string message;

    // Ugly but lets the user input spaces in the message
    for (int i = 1; i < argc; i++) {
        std::string current_arg = argv[i];

        if (current_arg == "-k" && i + 1 < argc) {
            key = argv[++i];
        } else if (current_arg == "-m" && i + 1 < argc) {
            i++;
            while (i < argc && std::string(argv[i]) != "-k") {
                if (!message.empty()) {
                    message += " ";
                }
                message += argv[i++];
            }
            i--;  // Move back the index to correctly process next argument
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