#include "generators.hpp"


#include <chrono>
#include <sstream>

namespace Generators {

    std::string UniqueFile(std::string extension) {
        auto now = std::chrono::system_clock::now();
        auto time_since_epoch = now.time_since_epoch();
        auto unique_time = std::chrono::duration_cast<std::chrono::milliseconds>(time_since_epoch).count();

        std::ostringstream oss;
        oss << "encrypted_" << unique_time << extension;

        return oss.str();
    }
} 


