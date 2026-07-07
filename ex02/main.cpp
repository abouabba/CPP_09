# include "PmergeMe.hpp"

int main(int ac, char **av) {
    if (ac < 2) {
        std::cout << "Error" << std::endl;
        return 1;
    }
    PmergeMe pMe;

    try {
        pMe.parse(av);
        std::cout << "For vector " << std::endl;
        pMe.sortVector();
        std::cout << "For Deque " << std::endl;
        pMe.sortDeque();
        
    } catch (const std::runtime_error &e) {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}