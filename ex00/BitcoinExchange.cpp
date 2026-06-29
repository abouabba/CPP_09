# include "BitcoinExchange.hpp"


std::string trim(const std::string& str)
{
    size_t start = str.find_first_not_of(" \t");
    size_t end = str.find_last_not_of(" \t");

    if (start == std::string::npos)
        return "";

    return str.substr(start, end - start + 1);
}

void BitcoinExchange::loadDatabase() {

    std::ifstream file("../data.csv");

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
    
    // for (std::map<std::string, double>::iterator it = database.begin();
    //         it != database.end();
    //          ++it) {
    //     std::cout << it->first
    //               << " " 
    //               << it->second 
    //               << std::endl;
    // }
}

double BitcoinExchange::getRate(const std::string &data) {
    std::map<std::string, double>::iterator it;
    it = database.lower_bound(data);
    std::cout << it->first<< "  =>> "<< it->second << std::endl;
    if (it == database.end()) {
        --it;
        return it->second;
    }
    if (it->first == data)
        return it->second;
    if (it != database.begin())
        --it;
    std::cout << it->first<< "  =>> "<< it->second << std::endl;
    return it->second;
}

void BitcoinExchange::processInput(const std::string& filename) {
    std::ifstream file(filename.c_str());
    
    if (!file.is_open())
        throw std::runtime_error("Error : could't open the file");

    std::string line;
    getline(file, line);

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
    
        double amount = 0;
        ss >> amount;
    
    
        std::cout << data << "  -->  " << value << std::endl;
        std::cout <<"  ------------>  " << amount << std::endl;
    
        if (amount < 0) {
            std::cerr << "Error: not a positive number." << std::endl;
            continue;
        }
    
        if (amount > 1000) {
            std::cerr << "Error: too large a number." << std::endl;
            continue;
        }
    }
}