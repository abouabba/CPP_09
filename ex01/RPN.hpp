# ifndef RPN_HPP
# define RPN_HPP

# include <stack>
# include <iostream>
# include <sstream>
# include <string>
# include <algorithm>
# include <climits>

class RPN {
    private:
        std::stack<int> stk;
    public:
        RPN();
        RPN(const RPN &other);
        RPN &operator=(const RPN &other);
        ~RPN();
        void calculate(const std::string &expression);
};

# endif