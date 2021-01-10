#ifndef PDFA_H
#define PDFA_H

#include <unordered_set>
#include <map>
#include <utility>
#include <string>
#include "Alphabet.h"

//Автоматът е наредена петорка (Σ, Q, 𝛿, qstart, F)
//template <typename T>
class PDFA {

    private: 
        //Σ
        Alphabet alphabet;
        //std::unordered_set<T> states;
        //Q 
        std::unordered_set<std::pair<std::string, std::string>> states; 
        //A TEMPLATE IDEA T = string | pair<string, string>
        //std::map<std::pair<T, char>, T> delta;
        //𝛿
        std::map<std::pair<std::pair<std::string, std::string>, char>, std::pair<std::string, std::string>> delta;
        //T qs;
        //Initial state
        std::pair<std::string, std::string> qs;
        //std::unordered_set<T> finalStates;
        //F
        std::unordered_set<std::pair<std::string, std::string>> finalStates;

        void copy(const PDFA&);
        void erase();

    public:
        //Default constructor
        PDFA();
        //PDFA(const Alphabet&, const std::unordered_set<T>&, 
        //    const std::map<std::pair<T, char>, T>&, const T&, 
        //    const std::unordered_set<T>&);
        //Constructor with arguments
        PDFA(const Alphabet&, const std::unordered_set<std::pair<std::string, std::string>>&, 
            const std::map<std::pair<std::pair<std::string, std::string>, char>, 
            std::pair<std::string, std::string>>&, const std::pair<std::string, std::string>&, 
            const std::unordered_set<std::pair<std::string, std::string>>&);
        //Copy constructor
        PDFA(const PDFA&);
        //Operator=
        PDFA& operator= (const PDFA&);
        //Destructor
        ~PDFA();

        //Add functions
        //Add character to the alphabet
        Alphabet& addLetter(const char&);
        //void addState(const T&);
        //Add state to the set of states
        void addState(const std::pair<std::string, std::string>&);
        //void addTransition(const std::pair<T, char>&, const T&);
        //Add transition to the delta function
        void addTransition(const std::pair<std::pair<std::string, std::string>, char>&, 
                           const std::pair<std::string, std::string>&);
        //void addFinalState(const T&);
        //Add final state to the set of final states
        void addFinalState(const std::pair<std::string, std::string>&);

        //Remove functions
        //Remove letter from the alphabet       
        Alphabet& removeLetter(const char&);
        //void removeState(const T&);
        //Remove state from the set of states
        void removeState(const std::pair<std::string, std::string>&);
        //void removeTransition(const std::pair<T, char>&, const T&);
        //Remove transition from the delta function
        void removeTransition(const std::pair<std::pair<std::string, std::string>, char>&, 
                              const std::pair<std::string, std::string>&);
        //void removeFinalState(const T&);
        //Remove final state from the set of final states
        void removeFinalState(const std::pair<std::string, std::string>&);

        //Setters
        //Set the letters of the alphabet
        void setAlphabet(const Alphabet&);
        //void setStates(const std::unordered_set<T>&); 
        //Set the set of states
        void setStates(const std::unordered_set<std::pair<std::string, std::string>>&); 
        //void setDelta(const std::map<std::pair<T, char>, T>&);
        //Set the delta function
        void setDelta(const std::map<std::pair<std::pair<std::string, std::string>, char>, 
                            std::pair<std::string, std::string>>&);
        //void setQs(const T&);
        //Set the initial state
        void setQs(const std::pair<std::string, std::string>&);
        //void setFinalStates(const std::unordered_set<T>&);
        //Set the set of final states
        void setFinalStates(const std::unordered_set<std::pair<std::string, std::string>>&);

        //Getters
        //Get the letters of the alphabet
        Alphabet getAlphabet() const;
        //std::unordered_set<T> getStates() const; 
        //Get the set of states
        std::unordered_set<std::pair<std::string, std::string>> getStates() const; 
        //std::map<std::pair<T, char>, T> getDelta() const;
        //Get the delta function
        std::map<std::pair<std::pair<std::string, std::string>, char>, std::pair<std::string, std::string>> getDelta() const;
        //T getQs() const;
        //Get the initial state
        std::pair<std::string, std::string> getInitialState() const;
        //std::unordered_set<T> getFinalStates() const;
        //Get the set of final states
        std::unordered_set<std::pair<std::string, std::string>> getFinalStates() const;

        //Check if a word can be recognized by the language of the PDFA
        bool canBeRecognized(const std::string&);
        //Addition of the language of PDFA       
        PDFA& addition();
        //Print the PDFA
        void print() const;
};

#endif