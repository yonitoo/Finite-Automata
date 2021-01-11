#include "RegEx.h"
#include <stack>
#include <queue>

void RegEx::copy(const RegEx& other) {

    this->expression = other.expression;
}

RegEx::RegEx() : expression("") {

}

RegEx::RegEx(const std::string& expression) {

    this->expression = expression;
}

RegEx::RegEx(const RegEx& other) {

    copy(other);
}

RegEx& RegEx::operator=(const RegEx& other) {

    if(this != &other) {

        copy(other);
    }

    return *this;
}

RegEx::~RegEx() {

}

void RegEx::setRegEx(const std::string& expression) {

    this->expression = expression;
}

std::string RegEx::getRegEx() const {

    return this->expression;
}

bool RegEx::isValid() {

}
      
std::string& RegEx::regExPrioritization() {

    if(this->isValid()) {

        return '(' + this->expression + ')';
    }
    //TODO decide what to return in the other scenario
}
   
std::string& RegEx::regExConcatenation(const std::string& expression) {
    
    if(this->isValid()) {

        return this->expression + '.' + expression;
    }
}
         
std::string& RegEx::regExUnion(const std::string& expression) {
    //TODO да видя какво става, ако имат общи части
    if(this->isValid()) {

        return this->expression + '+' + expression;
    }
}
               
std::string& RegEx::regExIntersection(const std::string& expression) {

    //TODO може би някакъв цикъл по 2та израза
}
           
std::string& RegEx::regExKleeneStar() {

    if(this->isValid()) {
        
        if(this->expression[this->expression.length() - 1] == '*') {

            return this->regExPrioritization() + '*';
        }
        else {

            return this->expression + '*';
        }
    }
}

NFA RegEx::transformHelper(std::unordered_map<int, int>& match, int start, int end) {

    int balance = 0;
    std::priority_queue<std::pair<char, std::pair<int, int>>> operations;
    for(int i = start ; i <= end ; i++) {

        if(this->expression[i] == '(') {

            balance++;
        }
        else if(this->expression[i] == ')') {

            balance--;
        }
        else if(balance == 0) {

            if(this->expression[i] == '*') {

                operations.push(std::make_pair('*', std::make_pair(i, 2)));
            }
            else if(this->expression[i] == '.') {

                operations.push(std::make_pair('.', std::make_pair(i, 1)));
            }
            else if(this->expression[i] == '+' || this->expression[i] == '&') {

                operations.push(std::make_pair(this->expression[i], std::make_pair(i, 0)));
            }
        }
    }
    NFA left, right, current;
    while(!operations.empty()) {

        if(operations.top().first == '*') {

        }
        else {

            if(this->expression[operations.top().second.first - 1] == ')') {

                left = this->transformHelper(match, match[operations.top().second.first - 1] + 1, 
                                        operations.top().second.first - 2);
            }
            else {

                left = this->transformHelper(match, operations.top().second.first - 1, 
                                        operations.top().second.first - 1);
            }

            if(this->expression[operations.top().second.first + 1] == '(') {

                right = this->transformHelper(match, operations.top().second.first + 2, 
                                               match[operations.top().second.first + 1] - 1);
            }
            else {

                right = this->transformHelper(match, operations.top().second.first + 1, 
                                        operations.top().second.first + 1);
            }
            
            if(operations.top().first == '+') {

                current = left.uni(right);
            }
            else if(operations.top().first == '&') {

                //PDFA current2 =  
            }
        }
    }
}


NFA RegEx::transform() {

    int length = this->expression.size();
    std::stack<int> brackets;
    std::unordered_map<int, int> match;
    for(int i = 0 ; i < length ; i++) {

        if(this->expression[i] == '(') {

            brackets.push(i);
        }
        else if(this->expression[i] == ')') {

            match[brackets.top()] = i;
            match[i] = brackets.top();
            brackets.pop();
        }
    }

    return transformHelper(match, 0, length - 1);
}