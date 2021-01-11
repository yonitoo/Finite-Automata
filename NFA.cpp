#include "NFA.h"

void NFA::copy(const NFA& other) {

    this->alphabet = other.alphabet;
    this->states = other.states;
    this->delta = other.delta;
    this->qs = qs;
    this->finalStates = other.finalStates;
}

NFA::NFA() : alphabet (Alphabet()), states (std::unordered_set<std::string>()), 
            delta (std::map<std::pair<std::string, char>, std::unordered_set<std::string>>()), 
            qs(std::unordered_set<std::string>()), finalStates(std::unordered_set<std::string>()) {

}

NFA::NFA(const Alphabet& alphabet, const std::unordered_set<std::string>& states, 
        const std::map<std::pair<std::string, char>, std::unordered_set<std::string>>& delta, 
        const std::unordered_set<std::string>& qs, const std::unordered_set<std::string>& finalStates) {
    
    this->alphabet = alphabet;
    this->states = states;
    this->delta = delta;
    this->qs = qs;
    this->finalStates = finalStates;

}

NFA::NFA(const NFA& other) {

    copy(other);
}

NFA& NFA::operator= (const NFA& other) {

    if(this != &other) {

        copy(other);
    }

    return *this;
}

NFA::~NFA() {

}

Alphabet& NFA::addLetter(const char& letter) {

    return this->alphabet.addLetter(letter);
}

void NFA::addState(const std::string& state) {

    this->states.insert(state);
}

void NFA::addTransition(const std::pair<std::string, char>& sourceLetter, 
                        const std::string& destination) {

    this->states.insert(sourceLetter.first);
    this->states.insert(destination);
    this->delta[sourceLetter].insert(destination);
}

void NFA::addFinalState(const std::string& final) {

    this->finalStates.insert(final);
}

Alphabet& NFA::removeLetter(const char& letter) {

    int size = this->alphabet.getLetters().size();
    this->alphabet.removeLetter(letter);
    //Check if the letter was not in the alphabet
    if(this->alphabet.getLetters().size() == size) {

        return this->alphabet;
    }
    //Iterate over the map and delete the transitions, related to this letter
    for (std::map<std::pair<std::string, char>, std::unordered_set<std::string>>::iterator it = this->delta.begin(); 
            it != this->delta.end(); ) {

        if(it->first.second == letter) {

            this->delta.erase(it++);
        }
        else ++it;
    }

    return this->alphabet;
}

void NFA::removeState(const std::string& state) {

    this->states.erase(state);
}

void NFA::removeTransition(const std::pair<std::string, char>& sourceLetter, 
                            const std::string& destination) {

    //if(this->delta.count(sourceLetter))
    this->delta.erase(sourceLetter);
}

void NFA::removeInitialState(const std::string& initial) {

    if(this->qs.size() == 1) {

        //print error that there would be 0 initial states
    }

    for (std::map<std::pair<std::string, char>, std::unordered_set<std::string>>::iterator it = this->delta.begin(); 
            it != this->delta.end(); ) {

        if(it->first.first == initial) {

            it->second.clear();
            this->delta.erase(it++);
        }
        else ++it;
    }
}

void NFA::removeFinalState(const std::string& final) {

    this->finalStates.erase(final);
}

void NFA::setAlphabet(const Alphabet& alphabet) {

    this->alphabet = alphabet;
}

void NFA::setStates(const std::unordered_set<std::string>& states) {

    this->states = states;
}

void NFA::setDelta(const std::map<std::pair<std::string, char>, std::unordered_set<std::string>>& delta) {

    this->delta = delta;
}

void NFA::setInitialStates(const std::unordered_set<std::string>& qs) {

    this->qs = qs;
}

void NFA::setFinalStates(const std::unordered_set<std::string>& finalStates) {

    this->finalStates = finalStates;
}

//
Alphabet NFA::getAlphabet() const {

    return this->alphabet;
}

//
std::unordered_set<std::string> NFA::getStates() const {

    return this->states;
}

std::map<std::pair<std::string, char>, std::unordered_set<std::string>> NFA::getDelta() const {

    return this->delta;
}

std::unordered_set<std::string> NFA::getInitialStates() const {

    return this->qs;
}

std::unordered_set<std::string> NFA::getFinalStates() const {

    return this->finalStates;
}

bool NFA::canBeRecognized(const std::string& word) {

    /*int length = word.size();
    std::string currentState;
    //TODO for each Qs fix
    for(auto it : this->qs) {
        currentState = it;
        for(int i = 0 ; i < length ; i++) {
        
            if(!this->delta.count(std::make_pair(currentState, word[i]))) {

                return false;
            }
            //currentState така става set
            //dfs moje bi
            currentState = this->delta[std::make_pair(currentState, word[i])];
        }
    
        if(this->finalStates.find(currentState) != this->finalStates.end()) {

            return true;
        }
    }*/
    return false;
}  

NFA& NFA::uni(NFA& nfa) {

    NFA result;
    for (std::unordered_set<char>::iterator it = this->alphabet.getLetters().begin(); 
            it != this->alphabet.getLetters().end(); it++) {

        result.addLetter(*it);
    }

    for (std::unordered_set<char>::iterator it = nfa.getAlphabet().getLetters().begin(); 
            it != nfa.getAlphabet().getLetters().end(); it++) {

        result.addLetter(*it);
    }

    for (std::unordered_set<std::string>::iterator it = this->states.begin(); 
            it != this->states.end(); it++) {

        result.addState(*it);
    }

    for (std::unordered_set<std::string>::iterator it = nfa.getStates().begin(); 
            it != nfa.getStates().end(); it++) {

        result.addState(*it);
    }

    result.setInitialStates(this->qs);
    for (std::unordered_set<std::string>::iterator it = nfa.getInitialStates().begin(); 
            it != nfa.getInitialStates().end(); it++) {

        result.addInitialState(*it);
    }
    
    for (std::map<std::pair<std::string, char>, std::unordered_set<std::string>>::iterator it = this->delta.begin(); 
            it != this->delta.end(); ) {
        for (std::unordered_set<std::string>::iterator it2 = it->second.begin(); 
            it2 != it->second.end(); it++) {

            result.addTransition(it->first, *it2);
        }
    }

    for (std::map<std::pair<std::string, char>, std::unordered_set<std::string>>::iterator it = nfa.getDelta().begin(); 
            it != nfa.getDelta().end(); ) {
        for (std::unordered_set<std::string>::iterator it2 = it->second.begin(); 
            it2 != it->second.end(); it++) {

            result.addTransition(it->first, *it2);
        }
    }

    for (std::unordered_set<std::string>::iterator it = this->finalStates.begin(); 
            it != this->finalStates.end(); it++) {

        nfa.addFinalState(*it);
    }

    for (std::unordered_set<std::string>::iterator it = nfa.getFinalStates().begin(); 
            it != nfa.getFinalStates().end(); it++) {

        nfa.addFinalState(*it);
    }

    return nfa;
}

DFA& NFA::determinize() {

}