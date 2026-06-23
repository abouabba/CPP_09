# include <iostream>
# include <fstream>
# include <sstream>
# include "BitcoinExchange.hpp"

int main(int ac, char **av) {
    if (ac != 2)
        return -1;
    std::ifstream file(av[1]);
    if (!file.is_open()) {
        std::cerr << "could't open file" << std::endl;
        return -1;
    }
    std::stringstream buffer;

    buffer << file.rdbuf();
    std::string string;


    string = buffer.str();
    std::cout << string << std::endl;

    file.close();
}
