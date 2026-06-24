# include "BitcoinExchange.hpp"

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