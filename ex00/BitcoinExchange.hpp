# ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP

# include <fstream>
# include <algorithm>
# include <iostream>
# include <sstream>
# include <stdexcept>
# include <map>

class BitcoinExchange {
    private:
        std::map<std::string, double> database;
    public:
        // BitcoinExchange();
        // BitcoinExchange(const BitcoinExchange &other);
        // BitcoinExchange &operator=(const BitcoinExchange &other);
        // ~BitcoinExchange();

        void loadDatabase();
        // void processInput(const std::string& filename);

        // bool isValidDate(const std::string& date);
        // bool isValidValue(const std::string& value);

        double getRate(const std::string& date);

};

# endif