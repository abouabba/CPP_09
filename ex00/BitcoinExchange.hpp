# ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP

# include <algorithm>
# include <map>

class BitcoinExchange {
    private:
        std::map<std::string, double> map;
    public:
        BitcoinExchange();
        BitcoinExchange(const BitcoinExchange &other);
        BitcoinExchange &operator=(const BitcoinExchange &other);
        ~BitcoinExchange();

        void validate_input(std::string &input);
        void date_validate(std::string &date);
};

# endif