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

/*bool RegEx::isValid() {

}
      
std::string& RegEx::regExPrioritization() {

    return ('(' + this->expression + ')');
}
   
std::string& RegEx::regExConcatenation(const std::string& expression) {
    
    if(this->isValid()) {

        return this->expression + std::to_string('.') + expression;
    }
}
         
std::string& RegEx::regExUnion(const std::string& expression) {
    //TODO да видя какво става, ако имат общи части
    if(this->isValid()) {

        return this->expression + std::to_string('+') + expression;
    }
}
               
std::string& RegEx::regExIntersection(const std::string& expression) {

    //TODO може би някакъв цикъл по 2та израза
}
           
std::string& RegEx::regExKleeneStar() {

    if(this->isValid()) {
        
        if(this->expression[this->expression.length() - 1] == '*') {

            return (this->regExPrioritization() + '*');
        }
        else {

            return (this->expression + '*');
        }
    }
}*/

DFA RegEx::transformHelper(std::map<int, int>& match, int start, int end, int i) {

    int balance = 0;
    int bestPosition = -1;
    int bestPriority = -1;
    char bestOperator;
    for(int i = start ; i <= end ; i++) {

        if(this->expression[i] == '(') {

            balance++;
        }
        else if(this->expression[i] == ')') {

            balance--;
        }
        else if(balance == 0) {

            if(this->expression[i] == '*' && bestPriority < 2) {

                bestPriority = 2;
                bestOperator = '*';
                bestPosition = i;
            }
            else if(this->expression[i] == '.' && bestPriority < 1) {

                bestPriority = 1;
                bestOperator = '.';
                bestPosition = i;
            }
            else if(this->expression[i] == '+' && bestPriority < 0) {
               
                bestPriority = 0;
                bestOperator = '+';
                bestPosition = i;
            }
            else if(this->expression[i] == '&' && bestPriority < 0) {

                bestPriority = 0;
                bestOperator = '&';
                bestPosition = i;
            }
        }
    }

    if(bestPosition == -1) {

        if(this->expression[start] == '(') {

            return transformHelper(match, start + 1, end - 1, i + 10);
        }
        else {

            DFA current;
            current.addState("q" + std::to_string(i));
            current.addState("q1" + std::to_string(i + 1));
            current.addTransition(std::make_pair("q" + std::to_string(i), 
                                    this->expression[start]), "q" + std::to_string(i + 1));
            current.addLetter(this->expression[start]);
            current.setQs("q" + std::to_string(i));
            current.addFinalState("q" + std::to_string(i + 1));
            return current;
        }
    }
    else if(bestOperator == '*'){

        DFA current = transformHelper(match, start, bestPosition - 1, i + 10);
        return current.iteration();
    }
    else {

        DFA left = transformHelper(match, start, bestPosition - 1, i + 10);
        DFA right = transformHelper(match, bestPosition + 1, end, i + 10);
        if(bestOperator == '.') {

            return left.concatenation(right);
        }
        else if(bestOperator == '&') {

            return left.intersection(right).toDFA(); 
        }
        else {

            return left.uni(right).toDFA();
        }
    }
}


DFA RegEx::transform() {

    int length = this->expression.size();
    std::stack<int> brackets;
    std::map<int, int> match;
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

    return transformHelper(match, 0, length - 1, 0);
}