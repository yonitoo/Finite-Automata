#ifndef NFA_H
#define NFA_H

class DFA;

#include "Alphabet.h"
#include <map>
#include <utility>
#include <set>
#include <string>

//Недетерминираният автомат е наредена петорка (Σ, Q, 𝛿, Qstart, F)
class NFA {

    private: 
        //Σ
        Alphabet alphabet;
        //Q 
        std::set<std::string> states; 
        //𝛿
        std::map<std::pair<std::string, char>, std::set<std::string>> delta;
        //Initial state
        std::set<std::string> qs;
        //F
        std::set<std::string> finalStates;

        void copy(const NFA&);
        void erase();

    public:
        //Default constructor
        NFA();
        //Constructor with arguments
        NFA(const Alphabet&, const std::set<std::string>&, 
            const std::map<std::pair<std::string, char>, std::set<std::string>>&, 
            const std::set<std::string>&, const std::set<std::string>&);
        //Copy constructor
        NFA(const NFA&);
        //Operator=
        NFA& operator= (const NFA&);
        //Destructor
        ~NFA();

        //Add functions
        //Add character to the alphabet
        Alphabet& addLetter(const char&);
        //Add state to the set of states
        void addState(const std::string&);
        //Add transition to the delta function
        void addTransition(const std::pair<std::string, char>&, const std::string&);
        //Add initial state to the set of initial states
        void addInitialState(const std::string&);
        //Add final state to the set of final states
        void addFinalState(const std::string&);

        //Remove functions
        //Remove letter from the alphabet       
        Alphabet& removeLetter(const char&);
        //Remove state from the set of states
        void removeState(const std::string&);
        //Remove transition from the delta function
        void removeTransition(const std::pair<std::string, char>&, const std::string&);
        //Remove initial state from the set of initial states
        void removeInitialState(const std::string&);
        //Remove final state from the set of final states
        void removeFinalState(const std::string&);

        //Setters
        //Set the letters of the alphabet
        void setAlphabet(const Alphabet&);
        //Set the set of states
        void setStates(const std::set<std::string>&); 
        //Set the delta function
        void setDelta(const std::map<std::pair<std::string, char>, std::set<std::string>>&);
        //Set the set of initial states
        void setInitialStates(const std::set<std::string>&);
        //Set the set of final states
        void setFinalStates(const std::set<std::string>&);

        //Getters
        //Get the letters of the alphabet
        Alphabet getAlphabet() const;
        //Get the set of states
        std::set<std::string> getStates() const; 
        //Get the delta function
        std::map<std::pair<std::string, char>, std::set<std::string>> getDelta() const;
        //Get the initial state
        std::set<std::string> getInitialStates() const;
        //Get the set of final states
        std::set<std::string> getFinalStates() const;

        //Check if a word can be recognized by the language of the NFA
        bool isRecognized(const std::string&);
        bool isRecognizedHelper(const std::string&, const std::string&); 
        //Union of the languages of 2 NFAs
        NFA& uni(NFA&);  
        //Print the NFA
        void print() const;
        //Read words from file and print the result
        void processInput(const std::string&);
};

#endif