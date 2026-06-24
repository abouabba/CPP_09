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

    BitcoinExchange btc;

    btc.loadDatabase();
    std::cout << btc.getRate("2011-01-03") << std::endl;
    std::cout << btc.getRate("2011-01-07") << std::endl;
    std::cout << btc.getRate("2012-01-11") << std::endl;
    btc.processInput(av[1]);
}