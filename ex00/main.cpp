# include <iostream>
# include "BitcoinExchange.hpp"

int main(int ac, char **av)
{
    (void)av;
    if (ac != 2)
    {
        std::cerr << "Error: could not open file." << std::endl;
        return (1);
    }
    try {

        BitcoinExchange btc;
    
        btc.loadDatabase();
        btc.processInput(av[1]);

    } catch (const std::runtime_error &e) {
        std::cout << e.what() << std::endl;
    }
}