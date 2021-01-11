#ifndef NFA_H
#define NFA_H

#include "DFA.h"

//Автоматът е наредена петорка (Σ, Q, 𝛿, qstart, F)
//template <typename T>
class NFA {

    private: 
        //Σ
        Alphabet alphabet;
        //Q 
        std::unordered_set<std::string> states; 
        //𝛿
        std::map<std::pair<std::string, char>, std::unordered_set<std::string>> delta;
        //Initial state
        std::unordered_set<std::string> qs;
        //F
        std::unordered_set<std::string> finalStates;

        void copy(const NFA&);
        void erase();

    public:
        //Default constructor
        NFA();
        //Constructor with arguments
        NFA(const Alphabet&, const std::unordered_set<std::string>&, 
            const std::map<std::pair<std::string, char>, std::unordered_set<std::string>>&, 
            const std::unordered_set<std::string>&, const std::unordered_set<std::string>&);
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
        void setStates(const std::unordered_set<std::string>&); 
        //Set the delta function
        void setDelta(const std::map<std::pair<std::string, char>, std::unordered_set<std::string>>&);
        //Set the set of initial states
        void setInitialStates(const std::unordered_set<std::string>&);
        //Set the set of final states
        void setFinalStates(const std::unordered_set<std::string>&);

        //Getters
        //Get the letters of the alphabet
        Alphabet getAlphabet() const;
        //Get the set of states
        std::unordered_set<std::string> getStates() const; 
        //Get the delta function
        std::map<std::pair<std::string, char>, std::unordered_set<std::string>> getDelta() const;
        //Get the initial state
        std::unordered_set<std::string> getInitialStates() const;
        //Get the set of final states
        std::unordered_set<std::string> getFinalStates() const;

        //Check if a word can be recognized by the language of the NFA
        bool canBeRecognized(const std::string&);
        //Union of the languages of 2 NFAs
        NFA& uni(NFA&);       
        //Print the NFA
        void print() const;
        //Transform the NFA into DFA  
        DFA& determinize();

};

#endif