#include "RegEx.h"

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

        return this->expression + expression;
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

DFA RegEx::transform() {
    //TODO * = цикъл
}