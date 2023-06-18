#ifndef STRING_OPS_HPP
#define STRING_OPS_HPP

#include <string>
#include <vector>


namespace StringOps {

    bool ValidAscii(const std::string& input); 
    std::vector<int> StringToAscii(const std::string &input);

} 


#endif