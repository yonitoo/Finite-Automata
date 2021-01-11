#ifndef DFA_H
#define DFA_H

#include <unordered_set>
#include <map>
#include <utility>
#include <string>
#include "Alphabet.h"
#include "NFA.h"
#include "PDFA.h"

//Автоматът е наредена петорка (Σ, Q, 𝛿, qstart, F)
class DFA {

    private: 
        //Σ
        Alphabet alphabet;
        //Q 
        std::unordered_set<std::string> states; 
        //𝛿
        std::map<std::pair<std::string, char>, std::string> delta;
        //Initial state
        std::string qs;
        //F
        std::unordered_set<std::string> finalStates;


        void copy(const DFA&);
        void renameStates(DFA&);
        void dfs(PDFA&, const DFA&, const std::pair<std::string, std::string>&);

    public:
        //Default constructor
        DFA();
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
        //Add state to the set of states
        void addState(const std::string&);
        //Add transition to the delta function
        void addTransition(const std::pair<std::string, char>&, const std::string&);
        //Add final state to the set of final states
        void addFinalState(const std::string&);

        //Remove functions
        //Remove letter from the alphabet       
        Alphabet& removeLetter(const char&);
        //Remove state from the set of states
        void removeState(const std::string&);
        //Remove transition from the delta function
        void removeTransition(const std::pair<std::string, char>&, const std::string&);
        //Remove final state from the set of final states
        void removeFinalState(const std::string&);

        //Setters
        //Set the letters of the alphabet
        void setAlphabet(const Alphabet&);
        //Set the set of states
        void setStates(const std::unordered_set<std::string>&); 
        //Set the delta function
        void setDelta(const std::map<std::pair<std::string, char>, std::string>&);
        //Set the initial state
        void setQs(const std::string&);
        //Set the set of final states
        void setFinalStates(const std::unordered_set<std::string>&);

        //Getters
        //Get the letters of the alphabet
        Alphabet getAlphabet() const;
        //Get the set of states
        std::unordered_set<std::string> getStates() const; 
        //Get the delta function
        std::map<std::pair<std::string, char>, std::string> getDelta() const;
        //Get the initial state
        std::string getQs() const;
        //Get the set of final states
        std::unordered_set<std::string> getFinalStates() const;

        //Check if a word can be recognized by the language of the DFA
        bool canBeRecognized(const std::string&);
        //Union of the languages of 2 DFAs      
        PDFA& uni(const DFA&);
        //Union_2 of the languages of 2 DFAs      
        NFA& uni_2(DFA&);
        //Intersection of the languages of 2 DFAs
        PDFA& intersection(const DFA&);
        //Concatenation of the languages of 2 DFAs
        NFA& concatenation(DFA&);
        //Iteration of the language of DFA       
        NFA& iteration();
        //Addition of the language of DFA       
        DFA& addition();
        //Print the DFA
        void print() const;
        //Transform the DFA into RegEx string  
        std::string transform();
        //transform the DFA into NFA
        NFA& toNFA();
};

#endif