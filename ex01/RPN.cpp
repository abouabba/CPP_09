# include "RPN.hpp"

RPN::RPN() {}
RPN::RPN(const RPN &other) : stk(other.stk){}
RPN &RPN::operator=(const RPN &other) {
    if (this != &other)
        this->stk = other.stk;
    return *this;
}
RPN::~RPN() {}

bool isOperator(const std::string& token)
{
    return token == "+" ||
           token == "-" ||
           token == "*" ||
           token == "/";
}

void RPN::calculate(const std::string &expression) {

    std::stringstream ss(expression);
    std::string token;
    while(ss >> token) {
        if (token.length() == 1 && std::isdigit(token[0])) {
            stk.push(token[0] - '0');
        }
        else if (isOperator(token)) {
            if (stk.size() < 2)
                throw std::runtime_error("Error");
            int a = stk.top();
            stk.pop();
            int b = stk.top();
            stk.pop();

        
            int result;
        
            if (token == "+")
                result = b + a;
            else if (token == "-")
                result = b - a;
            else if (token == "*")
                result = b * a;
            else {
                if (a == 0)
                    throw std::runtime_error("Error");
        
                result = b / a;
            }
            if (result > INT_MAX || result < INT_MIN)
                throw std::runtime_error("Error");
            stk.push(result);
        }
        else
            throw std::runtime_error("Error");
    }
    if (stk.size() != 1)
        throw std::runtime_error("Error");

    std::cout << stk.top() << std::endl;
    stk.pop();
}