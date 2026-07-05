# include "PmergeMe.hpp"

int PmergeMe::stringToInt(const std::string &str) const {
    std::stringstream ss(str);
    long value;
    char c;

    if (!(ss >> value) || (ss >> c))
        throw std::runtime_error("Error");

    if (value < 0 || value > std::numeric_limits<int>::max())
        throw std::runtime_error("Error");

    return static_cast<int>(value);
}

bool PmergeMe::isDuplicate(int value) const {
    return std::find(vec.begin(), vec.end(), value) != vec.end();
}

void PmergeMe::parse(char **av) {
    for (int i = 1; av[i]; i++) {
        int value = stringToInt(av[i]);

        if (isDuplicate(value))
            throw std::runtime_error("Error");

        vec.push_back(value);
        deq.push_back(value);
    }
}

std::vector<std::pair<int, int> >
PmergeMe::makePairs(bool &hasStraggler, int &straggler) {
    std::vector<std::pair<int, int> > pairs;

    hasStraggler = false;

    for (size_t i = 0; i + 1 < vec.size(); i += 2)
        pairs.push_back(std::make_pair(vec[i], vec[i + 1]));

    if (vec.size() % 2)
    {
        hasStraggler = true;
        straggler = vec.back();
    }

    return pairs;
}

void PmergeMe::sortEachPair(std::vector<std::pair<int, int> > &pair) {

    for (size_t i = 0; i < pair.size(); i++) {
        if (pair[i].first > pair[i].second)
            std::swap(pair[i].first, pair[i].second);
    }
}