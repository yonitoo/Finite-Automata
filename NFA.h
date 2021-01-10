#ifndef NFA_H
#define NFA_H

#include <unordered_set>
#include <map>
#include <utility>
#include <string>
#include "Alphabet.h"
#include "DFA.h"

//Автоматът е наредена петорка (Σ, Q, 𝛿, qstart, F)
//template <typename T>
class NFA {

    private: 
        //Σ
        Alphabet alphabet;
        //std::unordered_set<T> states;
        //Q 
        std::unordered_set<std::string> states; 
        //A TEMPLATE IDEA T = string | pair<string, string>
        //std::map<std::pair<T, char>, T> delta;
        //𝛿
        std::map<std::pair<std::string, char>, std::unordered_set<std::string>> delta;
        //T qs;
        //Initial state
        std::unordered_set<std::string> qs;
        //std::unordered_set<T> finalStates;
        //F
        std::unordered_set<std::string> finalStates;

        void copy(const NFA&);
        void erase();

    public:
        //Default constructor
        NFA();
        //NFA(const Alphabet&, const std::unordered_set<T>&, 
        //    const std::map<std::pair<T, char>, T>&, const T&, 
        //    const std::unordered_set<T>&);
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
        //void addState(const T&);
        //Add state to the set of states
        void addState(const std::string&);
        //void addTransition(const std::pair<T, char>&, const T&);
        //Add transition to the delta function
        void addTransition(const std::pair<std::string, char>&, const std::string&);
        //Add initial state to the set of initial states
        void addInitialState(const std::string&);
        //Add final state to the set of final states
        void addFinalState(const std::string&);

        //Remove functions
        //Remove letter from the alphabet       
        Alphabet& removeLetter(const char&);
        //void removeState(const T&);
        //Remove state from the set of states
        void removeState(const std::string&);
        //void removeTransition(const std::pair<T, char>&, const T&);
        //Remove transition from the delta function
        void removeTransition(const std::pair<std::string, char>&, const std::string&);
        //void removeFinalState(const T&);
        //Remove initial state from the set of initial states
        void removeInitialState(const std::string&);
        //Remove final state from the set of final states
        void removeFinalState(const std::string&);

        //Setters
        //Set the letters of the alphabet
        void setAlphabet(const Alphabet&);
        //void setStates(const std::unordered_set<T>&); 
        //Set the set of states
        void setStates(const std::unordered_set<std::string>&); 
        //void setDelta(const std::map<std::pair<T, char>, T>&);
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
        //Concatenation of the languages of 2 NFAs
        NFA& concatenation(const NFA&);
        //Iteration of the language of NFA       
        NFA& iteration();
        //Addition of the language of NFA       
        NFA& addition();
        //Print the NFA
        void print() const;
        //Transform the NFA into RegEx string  
        DFA& determinize();
};

#endif