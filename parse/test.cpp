#include "../includes/Utils.hpp"
#include "parsing.hpp"
// std::string get_value(const std::string& str, const std::string& key)
// {
//     std::string result;
//     if (str.find(key) == 0) // Check if key is at the beginning of str
//     {
//         std::string::size_type pos = str.find_first_not_of(" \t", key.length()); // Find the position of the first non-whitespace character after the key
//         if (pos != std::string::npos)
//         {
//             std::string::size_type end_pos = str.find_first_of("\r\n", pos); // Find the position of the end of the line
//             result = str.substr(pos, end_pos - pos); // Extract the rest of the line
//         }
//     }
//     return result;
// }

// #include <iostream>

int main(int ac , char **av) {
(void)ac;
    std::ifstream infile(av[1]);

    if (!infile) {
        std::cerr << "Failed to open file: " << av[1] << std::endl;
        return 1;
    }

    Config conf;
	conf.check_config(av[1]);
	std::cout << conf.getListen() << std::endl;
	std::cout << conf.getServerName() << std::endl;
	std::cout << conf.getRoot() << std::endl;
	std::cout << conf.getClientMaxBodySize() << std::endl;
	std::cout << conf.getClientBodyTempPath() << std::endl;

    return 0;
}