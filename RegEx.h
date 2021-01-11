#ifndef REGEX_H
#define REGEX_H

#include "DFA.h"
#include "NFA.h"

//Клас за азбуката на автомат
class RegEx {

    private:
        std::string expression;

        void copy(const RegEx&);
        DFA transformHelper(std::map<int, int>&, int, int, int);

    public:
        //Default constructor
        RegEx();
        //Constructor with argument
        RegEx(const std::string&);
        //Copy constructor
        RegEx(const RegEx&);
        //Operator=
        RegEx& operator=(const RegEx&);
        //Destructor
        ~RegEx();

        //Setter
        void setRegEx(const std::string&);
        //Getter
        std::string getRegEx() const;

        //Check if the string is a valid expression
        bool isValid();
        //Prioritize regular expression      
        std::string& regExPrioritization();
        //Concatenation of 2 regular expressions
        std::string& regExConcatenation(const std::string&);
        //Union of 2 regular expressions       
        std::string& regExUnion(const std::string&);
        //Intersection of 2 regular expressions       
        std::string& regExIntersection(const std::string&);
        //Kleene star of regular expressions       
        std::string& regExKleeneStar();

        //Transform the RegEx into DFA
        DFA transform();
};

#endif