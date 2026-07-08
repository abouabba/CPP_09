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
        /*algorithm fo vector*/
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

void PmergeMe::sortPairs(std::vector<std::pair<int, int> > &pairs) {
    if (pairs.size() <= 1)
        return ;
    size_t mid = pairs.size() / 2;
    std::vector<std::pair<int, int> > left(pairs.begin(), pairs.begin() + mid);
    std::vector<std::pair<int, int> > right(pairs.begin() + mid, pairs.end());

    sortPairs(left);
    sortPairs(right);
    merge(left, right, pairs);
}

void PmergeMe::merge(std::vector<std::pair<int, int> > &left,
std::vector<std::pair<int, int> > &right,
std::vector<std::pair<int, int> > &pairs) {
    size_t i = 0;
    size_t j = 0;
    size_t k = 0;
    while(i < left.size() && j < right.size()) {
        if (left[i].second <= right[j].second)
            pairs[k++] = left[i++];
        else
            pairs[k++] = right[j++];
    }
    while(i < left.size()) {
        pairs[k++] = left[i++];
    }
    while(j < right.size())
        pairs[k++] = right[j++];
}

void PmergeMe::buildChains(const std::vector<std::pair<int,int> > &pairs,
std::vector<int> &mainChain,
std::vector<std::pair<int, int> > &pend) {
    if (pairs.empty())
        return ;
    mainChain.push_back(pairs[0].first);
    mainChain.push_back(pairs[0].second);
    for(size_t i = 1; i < pairs.size(); i++) {
        mainChain.push_back(pairs[i].second);
        pend.push_back(pairs[i]);
    }
}

std::vector<size_t> PmergeMe::jacobsthalNumbers(size_t max) {
    std::vector<size_t> jacob;
    jacob.push_back(0);
    jacob.push_back(1);
    while (jacob.back() < max) {
        size_t n = jacob[jacob.size() - 1] + 2 * jacob[jacob.size() - 2];
        jacob.push_back(n);
    }
    return jacob;
}

std::vector<size_t> PmergeMe::buildInsertionOrder(size_t pendSize) {
    std::vector<size_t> order;
    if (pendSize == 0)
        return order;
    std::vector<size_t> jacob = jacobsthalNumbers(pendSize);

    order.push_back(0);
    size_t previous = 1;
    for (size_t i = 1; i < jacob.size(); i++) {
        size_t current = jacob[i];
        if (current > pendSize)
            current = pendSize;
        if (current == previous)
            continue;
        for (size_t j = current; j > previous; --j) {
            order.push_back(j - 1);
        }
        previous = current;
    }
    return order;
}

void PmergeMe::binaryInsert(std::vector<int> &mainChain, int value) {
    std::vector<int>::iterator it;
    it = std::lower_bound(mainChain.begin(), mainChain.end(), value);
    mainChain.insert(it, value);
}

void PmergeMe::binaryInsert(std::vector<int> &mainChain, int value, int limit) {
    
    std::vector<int>::iterator limitIt = std::find(mainChain.begin(), mainChain.end(), limit);
    std::vector<int>::iterator it;
    it = std::lower_bound(mainChain.begin(), limitIt + 1, value);
    mainChain.insert(it, value);
}

std::vector<int> PmergeMe::sortVector() {
    bool hasStraggler = false;
    int straggler = 0;
    std::vector<std::pair<int, int> > pairs;
    pairs = makePairs(hasStraggler, straggler);
    sortEachPair(pairs);
    sortPairs(pairs);
    std::vector<int> mainChain;
    std::vector<std::pair<int, int> > pend;
    buildChains(pairs, mainChain, pend);
    size_t max = pend.size();
    std::vector<size_t> order = buildInsertionOrder(max);
    for (size_t i = 0; i < order.size(); i++) {
        binaryInsert(mainChain, pend[order[i]].first, pend[order[i]].second);
    }
    if (hasStraggler)
        binaryInsert(mainChain, straggler);
    return mainChain;
}

void PmergeMe::printOriginal() {
    for (size_t i = 0; i < vec.size(); i++)
        std::cout << vec[i] << " ";
    std::cout << std::endl;
}

        /*algorithm for deque*/

std::deque<std::pair<int, int> >
PmergeMe::makePairsforDeque(bool &hasStraggler, int &straggler) {
    std::deque<std::pair<int, int> > pairs;

    hasStraggler = false;

    for (size_t i = 0; i + 1 < deq.size(); i += 2)
        pairs.push_back(std::make_pair(deq[i], deq[i + 1]));

    if (deq.size() % 2)
    {
        hasStraggler = true;
        straggler = deq.back();
    }

    return pairs;
}

void PmergeMe::sortEachPair(std::deque<std::pair<int, int> > &pair) {

    for (size_t i = 0; i < pair.size(); i++) {
        if (pair[i].first > pair[i].second)
            std::swap(pair[i].first, pair[i].second);
    }
}

void PmergeMe::sortPairs(std::deque<std::pair<int, int> > &pairs) {
    if (pairs.size() <= 1)
        return ;
    size_t mid = pairs.size() / 2;
    std::deque<std::pair<int, int> > left(pairs.begin(), pairs.begin() + mid);
    std::deque<std::pair<int, int> > right(pairs.begin() + mid, pairs.end());

    sortPairs(left);
    sortPairs(right);
    mergeDeque(left, right, pairs);
}

void PmergeMe::mergeDeque(std::deque<std::pair<int, int> > &left,
std::deque<std::pair<int, int> > &right,
std::deque<std::pair<int, int> > &pairs) {
    size_t i = 0;
    size_t j = 0;
    size_t k = 0;
    while(i < left.size() && j < right.size()) {
        if (left[i].second <= right[j].second)
            pairs[k++] = left[i++];
        else
            pairs[k++] = right[j++];
    }
    while(i < left.size()) {
        pairs[k++] = left[i++];
    }
    while(j < right.size())
        pairs[k++] = right[j++];
}

void PmergeMe::buildChains(const std::deque<std::pair<int,int> > &pairs,
std::deque<int> &mainChain,
std::deque<std::pair<int, int> > &pend) {
    if (pairs.empty())
        return ;
    mainChain.push_back(pairs[0].first);
    mainChain.push_back(pairs[0].second);
    for(size_t i = 1; i < pairs.size(); i++) {
        mainChain.push_back(pairs[i].second);
        pend.push_back(pairs[i]);
    }
}


void PmergeMe::binaryInsert(std::deque<int> &mainChain, int value) {
    std::deque<int>::iterator it;
    it = std::lower_bound(mainChain.begin(), mainChain.end(), value);
    mainChain.insert(it, value);
}

void PmergeMe::binaryInsert(std::deque<int> &mainChain, int value, int limit) {
    
    std::deque<int>::iterator limitIt = std::find(mainChain.begin(), mainChain.end(), limit);
    std::deque<int>::iterator it;
    it = std::lower_bound(mainChain.begin(), limitIt + 1, value);
    mainChain.insert(it, value);
}

void PmergeMe::sortDeque() {
    bool hasStraggler = false;
    int straggler = 0;
    std::deque<std::pair<int, int> > pairs;
    pairs = makePairsforDeque(hasStraggler, straggler);
    sortEachPair(pairs);
    sortPairs(pairs);
    std::deque<int> mainChain;
    std::deque<std::pair<int, int> > pend;
    buildChains(pairs, mainChain, pend);
    size_t max = pend.size();
    std::vector<size_t> order = buildInsertionOrder(max);
    for (size_t i = 0; i < order.size(); i++) {
        binaryInsert(mainChain, pend[order[i]].first, pend[order[i]].second);
    }
    if (hasStraggler)
        binaryInsert(mainChain, straggler);
}