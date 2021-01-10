#include "DFA.h"

void DFA::copy(const DFA& other) {

    this->alphabet = other.alphabet;
    this->states = other.states;
    this->delta = other.delta;
    this->qs = qs;
    this->finalStates = other.finalStates;
}

DFA& DFA::renameStates(DFA& dfa) {

}

PDFA& DFA::dfs(PDFA&, const DFA&, const DFA&) {

}

DFA::DFA() : alphabet (Alphabet()), states (std::unordered_set<std::string>()), 
            delta (std::map<std::pair<std::string, char>, std::string>()), qs(""), 
            finalStates(std::unordered_set<std::string>()) {

}

DFA::DFA(const Alphabet& alphabet, const std::unordered_set<std::string>& states, 
        const std::map<std::pair<std::string, char>, std::string>& delta, const std::string& qs, 
        const std::unordered_set<std::string>& finalStates) {
    
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
}

void DFA::removeTransition(const std::pair<std::string, char>& sourceLetter, 
                            const std::string& destination) {

    //MAYBE TODO use bool return type
    this->delta.erase(sourceLetter);
}

void DFA::removeFinalState(const std::string& final) {

    this->finalStates.erase(final);
}

void DFA::setAlphabet(const Alphabet& alphabet) {

    this->alphabet = alphabet;
}

void DFA::setStates(const std::unordered_set<std::string>& states) {

    this->states = states;
}

void DFA::setDelta(const std::map<std::pair<std::string, char>, std::string>& delta) {

    this->delta = delta;
}

void DFA::setQs(const std::string& qs) {

    this->qs = qs;
}

void DFA::setFinalStates(const std::unordered_set<std::string>& finalStates) {

    this->finalStates = finalStates;
}

Alphabet DFA::getAlphabet() const {

    return this->alphabet;
}

std::unordered_set<std::string> DFA::getStates() const {

    return this->states;
}

std::map<std::pair<std::string, char>, std::string> DFA::getDelta() const {

    return this->delta;
}

std::string DFA::getQs() const {

    return this->qs;
}

std::unordered_set<std::string> DFA::getFinalStates() const {

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
    for (std::unordered_set<char>::iterator it = this->alphabet.getLetters().begin(); 
            it != this->alphabet.getLetters().end(); it++) {

        pdfa.addLetter(*it);
    }

    for (std::unordered_set<char>::iterator it = dfa.getAlphabet().getLetters().begin(); 
            it != dfa.getAlphabet().getLetters().end(); it++) {

        pdfa.addLetter(*it);
    }
    //състояния
    std::pair<std::string, std::string> currentState = pdfa.getInitialState();
    //TODO dfs to find the transitions and the states
    pdfa = dfs(pdfa, *this, dfa);


    //преходи
    for (std::unordered_set<std::pair<std::string, std::string>>::iterator it = pdfa.getStates().begin(); 
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
    for (std::unordered_set<char>::iterator it = this->alphabet.getLetters().begin(); 
            it != this->alphabet.getLetters().end(); it++) {

        nfa.addLetter(*it);
    }

    for (std::unordered_set<char>::iterator it = dfa.getAlphabet().getLetters().begin(); 
            it != dfa.getAlphabet().getLetters().end(); it++) {

        nfa.addLetter(*it);
    }

    for (std::unordered_set<std::string>::iterator it = this->states.begin(); 
            it != this->states.end(); it++) {

        nfa.addState(*it);
    }
    //TODO renameStates function
    dfa = this->renameStates(dfa);

    for (std::unordered_set<std::string>::iterator it = dfa.getStates().begin(); 
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

    for (std::unordered_set<std::string>::iterator it = this->finalStates.begin(); 
            it != this->finalStates.end(); it++) {

        nfa.addFinalState(*it);
    }

    for (std::unordered_set<std::string>::iterator it = dfa.getFinalStates().begin(); 
            it != dfa.getFinalStates().end(); it++) {

        nfa.addFinalState(*it);
    }

    return nfa;
}

PDFA& DFA::intersection(const DFA& dfa) {

    PDFA pdfa;
    pdfa.setQs(std::make_pair(this->getQs(), dfa.getQs()));
    for (std::unordered_set<char>::iterator it = this->alphabet.getLetters().begin(); 
            it != this->alphabet.getLetters().end(); it++) {

        pdfa.addLetter(*it);
    }

    for (std::unordered_set<char>::iterator it = dfa.getAlphabet().getLetters().begin(); 
            it != dfa.getAlphabet().getLetters().end(); it++) {

        pdfa.addLetter(*it);
    }

    std::pair<std::string, std::string> currentState = pdfa.getInitialState();
    //TODO dfs to find the transitions and the states
    pdfa = dfs(pdfa, *this, dfa);

    for (std::unordered_set<std::pair<std::string, std::string>>::iterator it = pdfa.getStates().begin(); 
            it != pdfa.getStates().end(); it++) {

        if((this->finalStates.find(it->first) != this->finalStates.end()) &&
           (dfa.getFinalStates().find(it->second) != dfa.getFinalStates().end())) {

            pdfa.addFinalState(*it);
        }
    }
    return pdfa;
}        

NFA& DFA::concatenation(DFA& dfa) {

    NFA nfa;
    for (std::unordered_set<char>::iterator it = this->alphabet.getLetters().begin(); 
            it != this->alphabet.getLetters().end(); it++) {

        nfa.addLetter(*it);
    }

    for (std::unordered_set<char>::iterator it = dfa.getAlphabet().getLetters().begin(); 
            it != dfa.getAlphabet().getLetters().end(); it++) {

        nfa.addLetter(*it);
    }

    for (std::unordered_set<std::string>::iterator it = this->states.begin(); 
            it != this->states.end(); it++) {

        nfa.addState(*it);
    }
    //TODO renameStates function
    dfa = this->renameStates(dfa);

    for (std::unordered_set<std::string>::iterator it = dfa.getStates().begin(); 
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
        
        for (std::unordered_set<std::string>::iterator it = this->finalStates.begin(); 
            it != this->finalStates.end(); it++) {
        
            nfa.addFinalState(*it);
        }
    }

    for (std::unordered_set<std::string>::iterator it = dfa.getFinalStates().begin(); 
            it != dfa.getFinalStates().end(); it++) {

        nfa.addFinalState(*it);
    }

    return nfa;
}   

NFA& DFA::iteration() {

    NFA nfa;
    nfa.setAlphabet(this->alphabet);
    nfa.addInitialState(this->qs);
    for (std::unordered_set<std::string>::iterator it = this->states.begin(); 
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
}

DFA& DFA::addition()  {

    bool found = false;
    std::unordered_set<std::string> newFinals;
    for (std::unordered_set<std::string>::iterator it = this->states.begin(); 
            it != this->states.end(); it++) {
        found = false;
        for(std::unordered_set<std::string>::iterator itFinal = this->finalStates.begin(); 
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