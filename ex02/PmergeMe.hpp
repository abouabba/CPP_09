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
        /* ---------Vector-------- */
        void parse(char **av);
        void sortVector();
        std::vector<std::pair<int, int> > 
        makePairs(bool &hasStraggler, int &straggler);
        void sortEachPair(std::vector<std::pair<int, int> > &pair);
        void sortPairs(std::vector<std::pair<int, int> > &pairs);
        void merge(std::vector<std::pair<int, int> > &left,
                    std::vector<std::pair<int, int> > &right,
                    std::vector<std::pair<int, int> > &pairs);
        void buildChains(const std::vector<std::pair<int,int> > &pairs,
                                    std::vector<int> &mainChain,
                                    std::vector<int> &pend);
        std::vector<size_t> jacobsthalNumbers(size_t max);
        std::vector<size_t> buildInsertionOrder(size_t pendSize);
        void binaryInsert(std::vector<int> &mainChain, int value);
        /* ---------Deque-------- */
        void sortDeque();
        std::deque<std::pair<int, int> > 
        makePairsforDeque(bool &hasStraggler, int &straggler);
        void sortEachPair(std::deque<std::pair<int, int> > &pair);
        void sortPairs(std::deque<std::pair<int, int> > &pairs);
        void mergeDeque(std::deque<std::pair<int, int> > &left,
                    std::deque<std::pair<int, int> > &right,
                    std::deque<std::pair<int, int> > &pairs);
        void buildChains(const std::deque<std::pair<int,int> > &pairs,
                                    std::deque<int> &mainChain,
                                    std::deque<int> &pend);
        std::deque<size_t> jacobsthalNumbers_forDeque(size_t max);
        std::deque<size_t> buildInsertionOrder_forDeque(size_t pendSize);
        void binaryInsert(std::deque<int> &mainChain, int value);
};

#endif