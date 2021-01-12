#ifndef PDFA_H
#define PDFA_H

class DFA;

#include <set>
#include <map>
#include <utility>
#include <string>
#include "Alphabet.h"

//Автоматът е наредена петорка (Σ, Q, 𝛿, qstart, F)
class PDFA {

    private: 
        //Σ
        Alphabet alphabet;
        //Q 
        std::set<std::pair<std::string, std::string>> states; 
        //𝛿
        std::map<std::pair<std::pair<std::string, std::string>, char>, std::pair<std::string, std::string>> delta;
        //Initial state
        std::pair<std::string, std::string> qs;
        //F
        std::set<std::pair<std::string, std::string>> finalStates;

        void copy(const PDFA&);
        void erase();

    public:
        //Default constructor
        PDFA();
        //Constructor with arguments
        PDFA(const Alphabet&, const std::set<std::pair<std::string, std::string>>&, 
            const std::map<std::pair<std::pair<std::string, std::string>, char>, 
            std::pair<std::string, std::string>>&, const std::pair<std::string, std::string>&, 
            const std::set<std::pair<std::string, std::string>>&);
        //Copy constructor
        PDFA(const PDFA&);
        //Operator=
        PDFA& operator= (const PDFA&);
        //Destructor
        ~PDFA();

        //Add functions
        //Add character to the alphabet
        Alphabet& addLetter(const char&);
        //Add state to the set of states
        void addState(const std::pair<std::string, std::string>&);
        //Add transition to the delta function
        void addTransition(const std::pair<std::pair<std::string, std::string>, char>&, 
                           const std::pair<std::string, std::string>&);
        //Add final state to the set of final states
        void addFinalState(const std::pair<std::string, std::string>&);

        //Remove functions
        //Remove letter from the alphabet       
        Alphabet& removeLetter(const char&);
        //Remove state from the set of states
        void removeState(const std::pair<std::string, std::string>&);
        //Remove transition from the delta function
        void removeTransition(const std::pair<std::pair<std::string, std::string>, char>&, 
                              const std::pair<std::string, std::string>&);
        //Remove final state from the set of final states
        void removeFinalState(const std::pair<std::string, std::string>&);

        //Setters
        //Set the letters of the alphabet
        void setAlphabet(const Alphabet&);
        //Set the set of states
        void setStates(const std::set<std::pair<std::string, std::string>>&); 
        //Set the delta function
        void setDelta(const std::map<std::pair<std::pair<std::string, std::string>, char>, 
                            std::pair<std::string, std::string>>&);
        //Set the initial state
        void setQs(const std::pair<std::string, std::string>&);
        //Set the set of final states
        void setFinalStates(const std::set<std::pair<std::string, std::string>>&);

        //Getters
        //Get the letters of the alphabet
        Alphabet getAlphabet() const;
        //Get the set of states
        std::set<std::pair<std::string, std::string>> getStates() const; 
        //Get the delta function
        std::map<std::pair<std::pair<std::string, std::string>, char>, std::pair<std::string, std::string>> getDelta() const;
        //Get the initial state
        std::pair<std::string, std::string> getInitialState() const;
        //Get the set of final states
        std::set<std::pair<std::string, std::string>> getFinalStates() const;

        //Check if a word can be recognized by the language of the PDFA
        bool isRecognized(const std::string&);
        //Addition of the language of PDFA       
        PDFA& addition();
        //Print the PDFA
        void print() const;
};

#endif