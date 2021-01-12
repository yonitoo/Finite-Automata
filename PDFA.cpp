#include "PDFA.h"

void PDFA::copy(const PDFA& other) {

    this->alphabet = other.alphabet;
    this->states = other.states;
    this->delta = other.delta;
    this->qs = qs;
    this->finalStates = other.finalStates;
}

PDFA::PDFA() : alphabet (Alphabet()), states (std::set<std::pair<std::string, std::string>>()), 
            delta (std::map<std::pair<std::pair<std::string, std::string>, char>, 
            std::pair<std::string, std::string>>()), qs(std::make_pair("", "")), 
            finalStates(std::set<std::pair<std::string, std::string>>()) {

}

PDFA::PDFA(const Alphabet& alphabet, const std::set<std::pair<std::string, std::string>>& states, 
        const std::map<std::pair<std::pair<std::string, std::string>, char>, std::pair<std::string, std::string>>& delta, const std::pair<std::string, std::string>& qs, 
        const std::set<std::pair<std::string, std::string>>& finalStates) {
    
    this->alphabet = alphabet;
    this->states = states;
    this->delta = delta;
    this->qs = qs;
    this->finalStates = finalStates;

}

PDFA::PDFA(const PDFA& other) {

    copy(other);
}

PDFA& PDFA::operator= (const PDFA& other) {

    if(this != &other) {

        copy(other);
    }

    return *this;
}

PDFA::~PDFA() {

}

Alphabet& PDFA::addLetter(const char& letter) {

    return this->alphabet.addLetter(letter);
}

void PDFA::addState(const std::pair<std::string, std::string>& state) {

    this->states.insert(state);
}

void PDFA::addTransition(const std::pair<std::pair<std::string, std::string>, char>& sourceLetter, 
                        const std::pair<std::string, std::string>& destination) {

    this->states.insert(sourceLetter.first);
    this->states.insert(destination);
    this->delta[sourceLetter] = destination;
}

void PDFA::addFinalState(const std::pair<std::string, std::string>& final) {

    this->finalStates.insert(final);
}

Alphabet& PDFA::removeLetter(const char& letter) {

    int size = this->alphabet.getLetters().size();
    this->alphabet.removeLetter(letter);
    //Check if the letter was not in the alphabet
    if(this->alphabet.getLetters().size() == size) {

        return this->alphabet;
    }
    //Iterate over the map and delete the transitions, related to this letter
    for (std::map<std::pair<std::pair<std::string, std::string>, char>, std::pair<std::string, std::string>>::iterator it = this->delta.begin(); 
            it != this->delta.end(); ) {

        if(it->first.second == letter) {

            this->delta.erase(it++);
        }
        else ++it;
    }

    return this->alphabet;
}

void PDFA::removeState(const std::pair<std::string, std::string>& state) {

    this->states.erase(state);
}

void PDFA::removeTransition(const std::pair<std::pair<std::string, std::string>, char>& sourceLetter, 
                            const std::pair<std::string, std::string>& destination) {

    //if(this->delta.count(sourceLetter))
    this->delta.erase(sourceLetter);
}

void PDFA::removeFinalState(const std::pair<std::string, std::string>& final) {

    this->finalStates.erase(final);
}

void PDFA::setAlphabet(const Alphabet& alphabet) {

    this->alphabet = alphabet;
}

void PDFA::setStates(const std::set<std::pair<std::string, std::string>>& states) {

    this->states = states;
}

void PDFA::setDelta(const std::map<std::pair<std::pair<std::string, std::string>, char>, std::pair<std::string, std::string>>& delta) {

    this->delta = delta;
}

void PDFA::setQs(const std::pair<std::string, std::string>& qs) {

    this->qs = qs;
}

void PDFA::setFinalStates(const std::set<std::pair<std::string, std::string>>& finalStates) {

    this->finalStates = finalStates;
}

Alphabet PDFA::getAlphabet() const {

    return this->alphabet;
}

std::set<std::pair<std::string, std::string>> PDFA::getStates() const {

    return this->states;
}

std::map<std::pair<std::pair<std::string, std::string>, char>, std::pair<std::string, std::string>> PDFA::getDelta() const {

    return this->delta;
}

std::pair<std::string, std::string> PDFA::getInitialState() const {

    return this->qs;
}

std::set<std::pair<std::string, std::string>> PDFA::getFinalStates() const {

    return this->finalStates;
}

bool PDFA::isRecognized(const std::string& word) {

    int length = word.size();
    std::pair<std::string, std::string> currentState = this->qs;
    for(int i = 0 ; i < length ; i++) {
        
        if(!this->delta.count(std::make_pair(currentState, word[i]))) {

            return false;
        }
        
        currentState = this->delta[std::make_pair(currentState, word[i])];
    }
    
    return this->finalStates.find(currentState) != this->finalStates.end();
}

PDFA& PDFA::addition()  {

    bool found = false;
    std::set<std::pair<std::string, std::string>> newFinals;
    for (auto it : this->states) {
        found = false;
        for(auto itFinal : this->finalStates) {
            if(this->states.find(itFinal) != this->states.end()) {

                found = true;
            }
        }

        if(!found) {

            newFinals.insert(it);
        }
    }
}