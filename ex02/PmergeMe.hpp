#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <vector>
#include <deque>
#include <string>
#include <sstream>
#include <stdexcept>
#include <limits>
#include <algorithm>
#include <iostream>

class PmergeMe
{
    private:
        std::vector<int> vec;
        std::deque<int>  deq;
    
        bool isDuplicate(int value) const;
        int  stringToInt(const std::string &str) const;
    
    public:
        void parse(char **av);
        std::vector<std::pair<int, int> > 
        makePairs(bool &hasStraggler, int &straggler);
        void sortEachPair(std::vector<std::pair<int, int> > &pair);
        void sortPairs(std::vector<std::pair<int, int> > &pairs);
        // void sortVector();
        // void sortDeque();
};

#endif