#include "DFA.h"

void DFA::copy(const DFA& other) {

    this->alphabet = other.alphabet;
    this->states = other.states;
    this->delta = other.delta;
    this->qs = qs;
    this->finalStates = other.finalStates;
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

void DFA::addLetter(const char& letter) {

    this->alphabet.addLetter(letter);
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

void DFA::removeLetter(const char& letter) {

    this->alphabet.removeLetter(letter);
}

void DFA::removeState(const std::string& state) {

    this->states.erase(state);
}

void DFA::removeTransition(const std::pair<std::string, char>& sourceLetter, 
                            const std::string& destination) {

    //if(this->delta.count(sourceLetter))
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