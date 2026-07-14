# include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange() {}
BitcoinExchange::BitcoinExchange(const BitcoinExchange &other) : database(other.database) {}
BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &other) {
    if (this != &other) {
        database = other.database;
    }
    return *this;
}
BitcoinExchange::~BitcoinExchange() {}

std::string trim(const std::string& str) {
    size_t start = str.find_first_not_of(" \t");
    size_t end = str.find_last_not_of(" \t");

    if (start == std::string::npos)
        return "";

    return str.substr(start, end - start + 1);
}

void BitcoinExchange::loadDatabase() {

    std::ifstream file("data.csv");

    if (!file.is_open())
        throw std::runtime_error("Error : could't open the csv file");

    std::string line;
    getline(file, line);
    while(getline(file, line)) {
        size_t pos = line.find(",");
        if (pos == std::string::npos)
            continue;
        std::string data = line.substr(0, pos);
        std::string rateStr = line.substr(pos + 1);
        
        std::stringstream ss(rateStr);
        double rate;
        ss >> rate;
        database[data] = rate;
    }
}

double BitcoinExchange::getRate(const std::string &data) {
    std::map<std::string, double>::iterator it;
    it = database.lower_bound(data);
    if (it == database.end()) {
        --it;
        return it->second;
    }
    if (it->first == data)
        return it->second;
    if (it != database.begin())
        --it;
    if (it == database.begin())
        throw std::runtime_error("Error : bad Input");
    return it->second;
}

bool BitcoinExchange::isValidDate(const std::string& date) {

    if (date.length() != 10)
        return false;
    if (date[4] != '-' || date[7] != '-')
        return false;
    for (size_t i = 0; i < date.length(); i++) {
        if (i == 4 || i == 7)
            continue;
        if (!std::isdigit(date[i]))
            return false;
    }
    int year = std::atoi(date.substr(0, 4).c_str());
    int month = std::atoi(date.substr(5, 2).c_str());
    int day = std::atoi(date.substr(8, 2).c_str());
    
    if (month < 1 || month > 12)
        return false;
    int daysInMonth[12] = {
        31, 28, 31, 30,
        31, 30, 31, 31,
        30, 31, 30, 31
    };
    bool leap = (year % 400 == 0) || (year % 4 == 0 && year % 100 != 0);
    if (leap)
        daysInMonth[1] = 29;
    if (day < 1 || day > daysInMonth[month - 1])
        return false;
    return true;
}

void BitcoinExchange::processInput(const std::string& filename) {
    std::ifstream file(filename.c_str());
    
    if (!file.is_open())
        throw std::runtime_error("Error : could't open the file");

    std::string line;
    getline(file, line);

    if (line != "date | value")
        throw std::runtime_error("Error: invalid header");
    while(getline(file, line)) {

        size_t pos = line.find('|');
        if (pos == std::string::npos) {
            std::cerr << "Error: bad input => " << line << std::endl;
            continue;
        }
        std::string data = line.substr(0, pos);
        std::string value = line.substr(pos + 1);
        
        data = trim(data);
        value = trim(value);
    
        std::stringstream ss(value);
    
        double amount;
        char extra;

        if (!(ss >> amount) || (ss >> extra))
        {
            std::cerr << "Error: bad input => " << line << std::endl;
            continue;
        }
    
        if (amount < 0) {
            std::cerr << "Error: not a positive number." << std::endl;
            continue;
        }
    
        if (amount > 1000) {
            std::cerr << "Error: too large number." << std::endl;
            continue;
        }

        if (!isValidDate(data)) {
            std::cerr << "not a valid data ." << std::endl;
            continue;
        }
        try {
            double rate = getRate(data);
            std::cout << data << " => " << amount << " = " << amount * rate << std::endl;
        }
        catch(const std::runtime_error &e)
        {
            std::cerr << e.what() << std::endl;
        }
    }
}
