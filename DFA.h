#ifndef DFA_H
#define DFA_H

#include <unordered_set>
#include <map>
#include <utility>
#include <string>
#include "Alphabet.h"

//Автоматът е наредена петорка (Σ, Q, 𝛿, qstart, F)
//template <typename T>
class DFA {

    private: 
        //Σ
        Alphabet alphabet;
        //std::unordered_set<T> states;
        //Q 
        std::unordered_set<std::string> states; 
        //A TEMPLATE IDEA T = string | pair<string, string>
        //std::map<std::pair<T, char>, T> delta;
        //𝛿
        std::map<std::pair<std::string, char>, std::string> delta;
        //T qs;
        //Initial state
        std::string qs;
        //std::unordered_set<T> finalStates;
        //F
        std::unordered_set<std::string> finalStates;

        void copy(const DFA&);
        void erase();

    public:
        //Default constructor
        DFA();
        //DFA(const Alphabet&, const std::unordered_set<T>&, 
        //    const std::map<std::pair<T, char>, T>&, const T&, 
        //    const std::unordered_set<T>&);
        //Constructor with arguments
        DFA(const Alphabet&, const std::unordered_set<std::string>&, 
            const std::map<std::pair<std::string, char>, std::string>&, const std::string&, 
            const std::unordered_set<std::string>&);
        //Copy constructor
        DFA(const DFA&);
        //Operator=
        DFA& operator= (const DFA&);
        //Destructor
        ~DFA();

        //Add functions
        //Add character to the alphabet
        Alphabet& addLetter(const char&);
        //void addState(const T&);
        //Add state to the set of states
        void addState(const std::string&);
        //void addTransition(const std::pair<T, char>&, const T&);
        //Add transition to the delta function
        void addTransition(const std::pair<std::string, char>&, const std::string&);
        //void addFinalState(const T&);
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
        void setDelta(const std::map<std::pair<std::string, char>, std::string>&);
        //void setQs(const T&);
        //Set the initial state
        void setQs(const std::string&);
        //void setFinalStates(const std::unordered_set<T>&);
        //Set the set of final states
        void setFinalStates(const std::unordered_set<std::string>&);

        //Getters
        //Get the letters of the alphabet
        Alphabet getAlphabet() const;
        //std::unordered_set<T> getStates() const; 
        //Get the set of states
        std::unordered_set<std::string> getStates() const; 
        //std::map<std::pair<T, char>, T> getDelta() const;
        //Get the delta function
        std::map<std::pair<std::string, char>, std::string> getDelta() const;
        //T getQs() const;
        //Get the initial state
        std::string getQs() const;
        //std::unordered_set<T> getFinalStates() const;
        //Get the set of final states
        std::unordered_set<std::string> getFinalStates() const;

        //Check if a word can be recognized by the language of the DFA
        bool canBeRecognized(const std::string&);
        //Prioritize regular expression      
        DFA& uni(const DFA&);
        //Intersection of the languages of 2 DFAs
        DFA& intersection(const DFA&);
        //Concatenation of the languages of 2 DFAs
        DFA& concatenation(const DFA&);
        //Iteration of the language of DFA       
        DFA& iteration();
        //Addition of the language of DFA       
        DFA& addition(const DFA&);
        //Print the DFA
        void print() const;
        //Transform the DFA into RegEx string  
        std::string transform();
};

#endif