# include "PmergeMe.hpp"

int main(int ac, char **av) {
    if (ac < 2) {
        std::cout << "Error" << std::endl;
        return 1;
    }
    PmergeMe pMe;

    try {
        PmergeMe pMe;

        pMe.parse(av);

        std::cout << "Before: ";
        pMe.printOriginal();

        clock_t start = clock();
        std::vector<int> sortedVec = pMe.sortVector();
        clock_t end = clock();

        double vecTime =
            static_cast<double>(end - start) * 1000000.0 / CLOCKS_PER_SEC;

        clock_t start2 = clock();
        pMe.sortDeque();
        clock_t end2 = clock();

        double deqTime =
            static_cast<double>(end2 - start2) * 1000000.0 / CLOCKS_PER_SEC;

        std::cout << "After: ";
        for (size_t i = 0; i < sortedVec.size(); i++)
            std::cout << sortedVec[i] << " ";
        std::cout << std::endl;

        std::cout << std::fixed << std::setprecision(5);

        std::cout << "Time to process a range of "
                  << sortedVec.size()
                  << " elements with std::vector : "
                  << vecTime << " us\n";

        std::cout << "Time to process a range of "
                  << sortedVec.size()
                  << " elements with std::deque : "
                  << deqTime << " us\n";
    } catch (const std::runtime_error &e) {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}