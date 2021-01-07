#include "DFA.h"

//template <typename T>
void DFA::copy(const DFA& other) {

    this->alphabet = other.alphabet;
    this->states = other.states;
    this->delta = other.delta;
    this->qs = qs;
    this->finalStates = other.finalStates;
}

//template <typename T>
DFA::DFA() : alphabet (Alphabet()), states (std::unordered_set<std::string>()), 
            delta (std::map<std::pair<std::string, char>, std::string>()), qs(""), 
            finalStates(std::unordered_set<std::string>()) {

}

//template <typename T>
DFA::DFA(const Alphabet& alphabet, const std::unordered_set<std::string>& states, 
        const std::map<std::pair<std::string, char>, std::string>& delta, const std::string& qs, 
        const std::unordered_set<std::string>& finalStates) {
    
    this->alphabet = alphabet;
    this->states = states;
    this->delta = delta;
    this->qs = qs;
    this->finalStates = finalStates;

}

//template <typename T>
DFA::DFA(const DFA& other) {

    copy(other);
}

//template <typename T>
DFA& DFA::operator= (const DFA& other) {

    if(this != &other) {

        copy(other);
    }

    return *this;
}

//template <typename T>
DFA::~DFA() {

}

//template <typename T>
Alphabet& DFA::addLetter(const char& letter) {

    return this->alphabet.addLetter(letter);
}

//template <typename T>
void DFA::addState(const std::string& state) {

    this->states.insert(state);
}

//template <typename T>
void DFA::addTransition(const std::pair<std::string, char>& sourceLetter, 
                        const std::string& destination) {

    this->states.insert(sourceLetter.first);
    this->states.insert(destination);
    this->delta[sourceLetter] = destination;
}

//template <typename T>
void DFA::addFinalState(const std::string& final) {

    this->finalStates.insert(final);
}

//template <typename T>
Alphabet& DFA::removeLetter(const char& letter) {

    int size = this->alphabet.getLetters().size();
    this->alphabet.removeLetter(letter);
    //Check if the letter was not in the alphabet
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

//template <typename T>
void DFA::removeState(const std::string& state) {

    this->states.erase(state);
}

//template <typename T>
void DFA::removeTransition(const std::pair<std::string, char>& sourceLetter, 
                            const std::string& destination) {

    //if(this->delta.count(sourceLetter))
    this->delta.erase(sourceLetter);
}

//template <typename T>
void DFA::removeFinalState(const std::string& final) {

    this->finalStates.erase(final);
}

//template <typename T>
void DFA::setAlphabet(const Alphabet& alphabet) {

    this->alphabet = alphabet;
}

//template <typename T>
void DFA::setStates(const std::unordered_set<std::string>& states) {

    this->states = states;
}

//template <typename T>
void DFA::setDelta(const std::map<std::pair<std::string, char>, std::string>& delta) {

    this->delta = delta;
}

//template <typename T>
void DFA::setQs(const std::string& qs) {

    this->qs = qs;
}

//template <typename T>
void DFA::setFinalStates(const std::unordered_set<std::string>& finalStates) {

    this->finalStates = finalStates;
}

//template <typename T>
Alphabet DFA::getAlphabet() const {

    return this->alphabet;
}

//template <typename T>
std::unordered_set<std::string> DFA::getStates() const {

    return this->states;
}

//template <typename T>
std::map<std::pair<std::string, char>, std::string> DFA::getDelta() const {

    return this->delta;
}

//template <typename T>
std::string DFA::getQs() const {

    return this->qs;
}

//template <typename T>
std::unordered_set<std::string> DFA::getFinalStates() const {

    return this->finalStates;
}

//template <typename T>
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

//DFA<std::pair<std::string, std::string>& DFA<std::string>::uni(DFA<std::string>& dfa)
/*DFA& DFA::uni(const DFA& dfa) {

    //<std::pair<std::string, std::string>>
    DFA result;
    result.setQs(std::make_pair(this->getQs(), dfa.getQs()));
    for (std::unordered_set<char>::iterator it = this->alphabet.getLetters().begin(); 
            it != this->alphabet.getLetters().end(); it++) {

        result.addLetter(*it);
    }

    for (std::unordered_set<char>::iterator it = dfa.getAlphabet().getLetters().begin(); 
            it != dfa.getAlphabet().getLetters().end(); it++) {

        result.addLetter(*it);
    }
    //състояния
    //преходи
    for (std::unordered_set<std::pair<std::string, std::string>>::iterator it = result.getStates().begin(); 
            it != result.getStates().end(); it++) {

        if((this->finalStates.find(it->first) != this->finalStates.end()) ||
           (dfa.getFinalStates().find(it->second) != dfa.getFinalStates().end())) {

            result.addFinalState(*it);
        }
    }
    return result;
}

//template <typename T>
DFA& DFA::intersection(const DFA&) {

    //<std::pair<std::string, std::string>>
    DFA result;
    result.setQs(std::make_pair(this->getQs(), dfa.getQs()));
    for (std::unordered_set<char>::iterator it = this->alphabet.getLetters().begin(); 
            it != this->alphabet.getLetters().end(); it++) {

        result.addLetter(*it);
    }

    for (std::unordered_set<char>::iterator it = dfa.getAlphabet().getLetters().begin(); 
            it != dfa.getAlphabet().getLetters().end(); it++) {

        result.addLetter(*it);
    }
    //състояния
    //преходи
    for (std::unordered_set<std::pair<std::string, std::string>>::iterator it = result.getStates().begin(); 
            it != result.getStates().end(); it++) {

        if((this->finalStates.find(it->first) != this->finalStates.end()) &&
           (dfa.getFinalStates().find(it->second) != dfa.getFinalStates().end())) {

            result.addFinalState(*it);
        }
    }
    return result;
}        */

//template <typename T>
DFA& DFA::concatenation(const DFA&) {

    
}   

//template <typename T>
DFA& DFA::iteration() {

}

//template <typename T>
DFA& DFA::addition(const DFA&)  {
    
    //обратните финални състояния
}   

//template <typename T>
void DFA::print() const {

}

//template <typename T>
std::string DFA::transform() {


}