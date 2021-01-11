#include "DFA.h"
#include <fstream>
#include <iostream>
#include <vector>

void DFA::copy(const DFA& other) {

    this->alphabet = other.alphabet;
    this->states = other.states;
    this->delta = other.delta;
    this->qs = qs;
    this->finalStates = other.finalStates;
}

void DFA::renameStates(DFA& dfa) {

}

void DFA::dfs(PDFA& pdfa, const DFA& dfa, const std::pair<std::string, std::string>& currentState) {

    for(std::set<char>::iterator it = this->alphabet.getLetters().begin(); 
            it != this->alphabet.getLetters().end(); it++) {

        pdfa.addTransition(std::make_pair(currentState, *it), 
        std::make_pair(this->delta[std::make_pair(currentState.first, *it)], dfa.getDelta()[std::make_pair(currentState.second, *it)]));
        pdfa.addState(std::make_pair(this->delta[std::make_pair(currentState.first, *it)], dfa.getDelta()[std::make_pair(currentState.second, *it)]));
        this->dfs(pdfa, dfa, std::make_pair(this->delta[std::make_pair(currentState.first, *it)], dfa.getDelta()[std::make_pair(currentState.second, *it)]));
    }
}

DFA::DFA() : alphabet (Alphabet()), states (std::set<std::string>()), 
            delta (std::map<std::pair<std::string, char>, std::string>()), qs(""), 
            finalStates(std::set<std::string>()) {

}

DFA::DFA(const Alphabet& alphabet, const std::set<std::string>& states, 
        const std::map<std::pair<std::string, char>, std::string>& delta, const std::string& qs, 
        const std::set<std::string>& finalStates) {
    
    this->alphabet = alphabet;
    this->states = states;
    this->delta = delta;
    this->qs = qs;
    this->finalStates = finalStates;

}

DFA::DFA(const DFA& other) {

    copy(other);
}

DFA& DFA::operator= (const DFA& other) {

    if(this != &other) {

        copy(other);
    }

    return *this;
}

DFA::~DFA() {

}

Alphabet& DFA::addLetter(const char& letter) {

    return this->alphabet.addLetter(letter);
}

void DFA::addState(const std::string& state) {

    this->states.insert(state);
}

void DFA::addTransition(const std::pair<std::string, char>& sourceLetter, 
                        const std::string& destination) {

    this->states.insert(sourceLetter.first);
    this->states.insert(destination);
    this->delta[sourceLetter] = destination;
}

void DFA::addFinalState(const std::string& final) {

    this->finalStates.insert(final);
}

Alphabet& DFA::removeLetter(const char& letter) {

    int size = this->alphabet.getLetters().size();
    this->alphabet.removeLetter(letter);
    //Check if the letter was missing in the alphabet
    if(this->alphabet.getLetters().size() == size) {

        return this->alphabet;
    }
    //Iterate over the map and delete the transitions, related to this letter
    for (std::map<std::pair<std::string, char>, std::string>::iterator it = this->delta.begin(); 
            it != this->delta.end(); ) {

        if(it->first.second == letter) {

            this->delta.erase(it++);
        }
        else ++it;
    }

    return this->alphabet;
}

void DFA::removeState(const std::string& state) {

    this->states.erase(state);
    for (std::map<std::pair<std::string, char>, std::string>::iterator it = this->delta.begin(); 
            it != this->delta.end(); ) {

        if(it->first.first == state || it->second == state) {

            this->delta.erase(it++);
        }
        else ++it;
    }
}

void DFA::removeTransition(const std::pair<std::string, char>& sourceLetter, 
                            const std::string& destination) {

    this->delta.erase(sourceLetter);
}

void DFA::removeFinalState(const std::string& final) {

    this->finalStates.erase(final);
}

void DFA::setAlphabet(const Alphabet& alphabet) {

    this->alphabet = alphabet;
}

void DFA::setStates(const std::set<std::string>& states) {

    this->states = states;
}

void DFA::setDelta(const std::map<std::pair<std::string, char>, std::string>& delta) {

    this->delta = delta;
}

void DFA::setQs(const std::string& qs) {

    this->qs = qs;
}

void DFA::setFinalStates(const std::set<std::string>& finalStates) {

    this->finalStates = finalStates;
}

Alphabet DFA::getAlphabet() const {

    return this->alphabet;
}

std::set<std::string> DFA::getStates() const {

    return this->states;
}

std::map<std::pair<std::string, char>, std::string> DFA::getDelta() const {

    return this->delta;
}

std::string DFA::getQs() const {

    return this->qs;
}

std::set<std::string> DFA::getFinalStates() const {

    return this->finalStates;
}

bool DFA::canBeRecognized(const std::string& word) {

    int length = word.size();
    std::string currentState = this->qs;
    for(int i = 0 ; i < length ; i++) {
        
        if(!this->delta.count(std::make_pair(currentState, word[i]))) {

            return false;
        }
        
        currentState = this->delta[std::make_pair(currentState, word[i])];
    }
    
    return this->finalStates.find(currentState) != this->finalStates.end();
}

PDFA& DFA::uni(const DFA& dfa) {

    PDFA pdfa;
    pdfa.setQs(std::make_pair(this->getQs(), dfa.getQs()));
    for (std::set<char>::iterator it = this->alphabet.getLetters().begin(); 
            it != this->alphabet.getLetters().end(); it++) {

        pdfa.addLetter(*it);
    }

    for (std::set<char>::iterator it = dfa.getAlphabet().getLetters().begin(); 
            it != dfa.getAlphabet().getLetters().end(); it++) {

        pdfa.addLetter(*it);
    }

    std::pair<std::string, std::string> initialState = pdfa.getInitialState();
    this->dfs(pdfa, dfa, initialState);

    for (std::set<std::pair<std::string, std::string>>::iterator it = pdfa.getStates().begin(); 
            it != pdfa.getStates().end(); it++) {

        if((this->finalStates.find(it->first) != this->finalStates.end()) &&
           (dfa.getFinalStates().find(it->second) != dfa.getFinalStates().end())) {

            pdfa.addFinalState(*it);
        }
    }
    return pdfa;
}

NFA& DFA::uni_2(DFA& dfa) {

    NFA nfa;
    for (std::set<char>::iterator it = this->alphabet.getLetters().begin(); 
            it != this->alphabet.getLetters().end(); it++) {

        nfa.addLetter(*it);
    }

    for (std::set<char>::iterator it = dfa.getAlphabet().getLetters().begin(); 
            it != dfa.getAlphabet().getLetters().end(); it++) {

        nfa.addLetter(*it);
    }

    for (std::set<std::string>::iterator it = this->states.begin(); 
            it != this->states.end(); it++) {

        nfa.addState(*it);
    }

    for (std::set<std::string>::iterator it = dfa.getStates().begin(); 
            it != dfa.getStates().end(); it++) {

        nfa.addState(*it);
    }

    nfa.addInitialState(this->qs);
    nfa.addInitialState(dfa.getQs());
    
    for (std::map<std::pair<std::string, char>, std::string>::iterator it = this->delta.begin(); 
            it != this->delta.end(); ) {

        nfa.addTransition(it->first, it->second);
    }

    for (std::map<std::pair<std::string, char>, std::string>::iterator it = dfa.getDelta().begin(); 
            it != dfa.getDelta().end(); ) {

        nfa.addTransition(it->first, it->second);
    }

    for (std::set<std::string>::iterator it = this->finalStates.begin(); 
            it != this->finalStates.end(); it++) {

        nfa.addFinalState(*it);
    }

    for (std::set<std::string>::iterator it = dfa.getFinalStates().begin(); 
            it != dfa.getFinalStates().end(); it++) {

        nfa.addFinalState(*it);
    }

    return nfa;
}

PDFA& DFA::intersection(const DFA& dfa) {

    PDFA pdfa;
    pdfa.setQs(std::make_pair(this->getQs(), dfa.getQs()));
    for (std::set<char>::iterator it = this->alphabet.getLetters().begin(); 
            it != this->alphabet.getLetters().end(); it++) {

        pdfa.addLetter(*it);
    }

    for (std::set<char>::iterator it = dfa.getAlphabet().getLetters().begin(); 
            it != dfa.getAlphabet().getLetters().end(); it++) {

        pdfa.addLetter(*it);
    }

    std::pair<std::string, std::string> initialState = pdfa.getInitialState();
    this->dfs(pdfa, dfa, initialState);

    for (std::set<std::pair<std::string, std::string>>::iterator it = pdfa.getStates().begin(); 
            it != pdfa.getStates().end(); it++) {

        if((this->finalStates.find(it->first) != this->finalStates.end()) &&
           (dfa.getFinalStates().find(it->second) != dfa.getFinalStates().end())) {

            pdfa.addFinalState(*it);
        }
    }
    return pdfa;
}        

DFA& DFA::concatenation(const DFA& dfa) {

    for (std::set<char>::iterator it = dfa.getAlphabet().getLetters().begin(); 
            it != dfa.getAlphabet().getLetters().end(); it++) {

        this->addLetter(*it);
    }

    for (std::set<std::string>::iterator it = dfa.getStates().begin(); 
            it != dfa.getStates().end(); it++) {

        this->addState(*it);
    }

    for (std::map<std::pair<std::string, char>, std::string>::iterator it = dfa.getDelta().begin(); 
            it != dfa.getDelta().end(); ) {

        this->addTransition(it->first, it->second);
    }
    std::set<std::string> temp = this->finalStates;
    this->finalStates.clear();

    for (std::set<std::string>::iterator it = this->finalStates.begin(); 
            it != this->finalStates.end(); it++) {
        
        this->addTransition(std::make_pair(*it, '@'), dfa.getQs());
    }

    if(dfa.getFinalStates().find(dfa.getQs()) != dfa.getFinalStates().end()) {
        
        for (std::set<std::string>::iterator it = this->finalStates.begin(); 
            it != this->finalStates.end(); it++) {
        
            this->setFinalStates(temp);
        }
    }

    for (std::set<std::string>::iterator it = dfa.getFinalStates().begin(); 
            it != dfa.getFinalStates().end(); it++) {

        this->addFinalState(*it);
    }

    return *this;
}

/*NFA& DFA::concatenation(const DFA& dfa) {

    NFA nfa;
    for (std::set<char>::iterator it = this->alphabet.getLetters().begin(); 
            it != this->alphabet.getLetters().end(); it++) {

        nfa.addLetter(*it);
    }

    for (std::set<char>::iterator it = dfa.getAlphabet().getLetters().begin(); 
            it != dfa.getAlphabet().getLetters().end(); it++) {

        nfa.addLetter(*it);
    }

    for (std::set<std::string>::iterator it = this->states.begin(); 
            it != this->states.end(); it++) {

        nfa.addState(*it);
    }

    for (std::set<std::string>::iterator it = dfa.getStates().begin(); 
            it != dfa.getStates().end(); it++) {

        nfa.addState(*it);
    }

    nfa.addInitialState(this->qs);
    
    for (std::map<std::pair<std::string, char>, std::string>::iterator it = this->delta.begin(); 
            it != this->delta.end(); ) {
        
        if(dfa.getFinalStates().find(it->first.first) != dfa.getFinalStates().end()) {

            nfa.addTransition(std::make_pair(it->first.first, '@'), dfa.getQs());
        }
        nfa.addTransition(it->first, it->second);
    }

    for (std::map<std::pair<std::string, char>, std::string>::iterator it = dfa.getDelta().begin(); 
            it != dfa.getDelta().end(); ) {

        nfa.addTransition(it->first, it->second);
    }

    if(dfa.getFinalStates().find(dfa.getQs()) != dfa.getFinalStates().end()) {
        
        for (std::set<std::string>::iterator it = this->finalStates.begin(); 
            it != this->finalStates.end(); it++) {
        
            nfa.addFinalState(*it);
        }
    }

    for (std::set<std::string>::iterator it = dfa.getFinalStates().begin(); 
            it != dfa.getFinalStates().end(); it++) {

        nfa.addFinalState(*it);
    }

    return nfa;
}*/

/*NFA& DFA::iteration() {

    NFA nfa;
    nfa.setAlphabet(this->alphabet);
    nfa.addInitialState(this->qs);
    for (std::set<std::string>::iterator it = this->states.begin(); 
            it != this->states.end(); it++) {
        
        nfa.addState(*it);
        if(this->finalStates.find(*it) != this->finalStates.end()) {
            //epsilon transition to the initial state
            nfa.addTransition(std::make_pair(*it, '@'), this->qs);
            nfa.addFinalState(*it);
        }
    }

    nfa.addInitialState(this->qs + "_2");
    nfa.addFinalState(this->qs + "_2");
    return nfa;
}*/

DFA& DFA::iteration() {

    this->addState("newQs");
    this->addTransition(std::make_pair("newQs", '@'), this->qs);
    this->setQs("newQs");
    this->addFinalState("newQs");
    for (std::set<std::string>::iterator it = this->finalStates.begin(); 
            it != this->finalStates.end(); it++) {
        //epsilon transition to the old initial state
        this->addTransition(std::make_pair(*it, '@'), this->qs);
    }
    return *this;
}

DFA& DFA::addition()  {

    bool found = false;
    std::set<std::string> newFinals;
    for (std::set<std::string>::iterator it = this->states.begin(); 
            it != this->states.end(); it++) {
        found = false;
        for(std::set<std::string>::iterator itFinal = this->finalStates.begin(); 
            itFinal != this->finalStates.end(); itFinal++) {
            if(this->states.find(*itFinal) != this->states.end()) {

                found = true;
            }
        }

        if(!found) {

            newFinals.insert(*it);
        }
    }
}   

void DFA::print() const {
    //TODO table output maybe
    //Alphabet: ...; States: ...; Initial state: ...; Final states: ...; Transitions: st1 + char -> st2
}

std::string DFA::transform() {
    
}

NFA& DFA::toNFA() {

    NFA nfa;
    nfa.setAlphabet(this->alphabet);
    for(std::set<std::string>::iterator it = this->states.begin();
        it != this->states.end(); it++) {
        
        if(*it == this->qs) {

            nfa.addInitialState(*it);
        }
        if(this->finalStates.find(*it) != this->finalStates.end()) {

            nfa.addFinalState(*it);
        }
        nfa.addState(*it);
    }

    for(std::map<std::pair<std::string, char>, std::string>::iterator it = 
                this->delta.begin(); it != this->delta.end(); it++) {
                
        nfa.addTransition(it->first, it->second);
    }

    return nfa;
}

void DFA::processInput(const std::string& input) {
     
    std::ifstream file;
    file.open(input, std::ios::in);
    if (!file.is_open())
    {
        std::cout << "Couldn't open the file or not a valid path!" << std::endl;
        return;
    }
    std::cout << "File opened successfully" << std::endl;
    std::multiset<std::string> words;
    std::string line;
    while(std::getline(file, line)) {

        words.insert(line);
    }
    
    file.close();
    int i = 1;
    for(std::multiset<std::string>::iterator it = words.begin() ; it != words.end() ; it++) {

        if(this->canBeRecognized(*it)) {

            std::cout << "The word " << *it << " on line " << i << " can be recognized!" << std::endl; 
        }
        i++;
    }
}