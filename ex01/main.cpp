# include "RPN.hpp"

int main(int ac, char **av) {
    if (ac != 2) {
        std::cerr << "Error" << std::endl;
        return -1;
    }
    (void)av;
    RPN rpn;

    try {
        rpn.calculate("3 4 +");
        rpn.calculate("3");
    } catch (const std::runtime_error &e) {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}