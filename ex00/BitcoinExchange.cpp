# include "BitcoinExchange.hpp"


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
    return it->second;
}

bool BitcoinExchange::isValidDate(const std::string& date) {

    if (date.length() != 10)
        return false;
    if (date[4] != '-' || date[7] != '-')
        return false;
    for (size_t i = 0; i < date.size(); i++) {
        if (i == 4 || i == 7)
            continue;
        if (!std::isdigit(date[i]))
            return false;
    }
    int year = std::atoi(date.substr(0, 4).c_str());
    int month = std::atoi(date.substr(5, 7).c_str());
    int day = std::atoi(date.substr(7).c_str());
    std::cout << year << "-" << month << "-" << day << std::endl;
    
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
            throw std::runtime_error("Error: bad input");
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
            std::cerr << "Error: too large a number." << std::endl;
            continue;
        }

        if (!isValidDate(data)) {
            std::cerr << "not a valid data ." << std::endl;
            continue;
        }
        double rate = getRate(data);
        std::cout << data << " => " << amount << " = " << amount * rate << std::endl;
    }
}
