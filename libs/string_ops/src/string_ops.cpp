#include "string_ops.hpp"


namespace StringOps {

    bool ValidAscii(const std::string& input) {
        for (char c : input) {
            if (c < 32 || c > 126) {
                return false;
            }
        }
        return true;
    }

    std::vector<int> StringToAscii(const std::string &input) {
        std::vector<int> ascii_conv;
        auto itr = input.begin();

        auto ascii_converter = [&](auto &&self, auto &&itr) -> void {
            if (itr != input.end()) {
                ascii_conv.push_back(static_cast<int>(*itr));
                self(self, ++itr);
            }
        };

        ascii_converter(ascii_converter, itr);
        
        return ascii_conv;
    }

    
}

