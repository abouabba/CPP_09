# include "PmergeMe.hpp"

int main(int ac, char **av) {
    if (ac < 2) {
        std::cout << "Error" << std::endl;
        return 1;
    }
    PmergeMe pMe;
    bool hasStraggler = false;
    int straggler = 0;
    std::vector<std::pair<int, int> > pairs;

    try {
        pMe.parse(av);
        pairs = pMe.makePairs(hasStraggler, straggler);
        pMe.sortEachPair(pairs);
        for (size_t i = 0; i < pairs.size(); i++) {
            std::cout << pairs[i].first << "-" << pairs[i].second << std::endl;
        }
        std::cout << "hasStraggler : " << hasStraggler << std::endl;
        std::cout << "straggler : " << straggler << std::endl;
        pMe.sortPairs(pairs);
        

    } catch (const std::runtime_error &e) {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}