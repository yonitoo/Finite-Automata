#include "NFA.h"
#include <set>
#include <fstream>
#include <iostream>

void NFA::copy(const NFA& other) {

    this->alphabet = other.alphabet;
    this->states = other.states;
    this->delta = other.delta;
    this->qs = qs;
    this->finalStates = other.finalStates;
}

NFA::NFA() : alphabet (Alphabet()), states (std::set<std::string>()), 
            delta (std::map<std::pair<std::string, char>, std::set<std::string>>()), 
            qs(std::set<std::string>()), finalStates(std::set<std::string>()) {

}

NFA::NFA(const Alphabet& alphabet, const std::set<std::string>& states, 
        const std::map<std::pair<std::string, char>, std::set<std::string>>& delta, 
        const std::set<std::string>& qs, const std::set<std::string>& finalStates) {
    
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

void NFA::addInitialState(const std::string& initial) {

    this->qs.insert(initial);
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
    for (std::map<std::pair<std::string, char>, std::set<std::string>>::iterator it = this->delta.begin(); 
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

        std::cout << "You can't have an automata without initial state!" << std::endl;
    }

    this->qs.erase(initial);
    for (auto it : this->delta) {

        if(it.first.first == initial) {

            it.second.clear();
            this->delta.erase(it.first);
        }
    }
}

void NFA::removeFinalState(const std::string& final) {

    this->finalStates.erase(final);
}

void NFA::setAlphabet(const Alphabet& alphabet) {

    this->alphabet = alphabet;
}

void NFA::setStates(const std::set<std::string>& states) {

    this->states = states;
}

void NFA::setDelta(const std::map<std::pair<std::string, char>, std::set<std::string>>& delta) {

    this->delta = delta;
}

void NFA::setInitialStates(const std::set<std::string>& qs) {

    this->qs = qs;
}

void NFA::setFinalStates(const std::set<std::string>& finalStates) {

    this->finalStates = finalStates;
}

//
Alphabet NFA::getAlphabet() const {

    return this->alphabet;
}

//
std::set<std::string> NFA::getStates() const {

    return this->states;
}

std::map<std::pair<std::string, char>, std::set<std::string>> NFA::getDelta() const {

    return this->delta;
}

std::set<std::string> NFA::getInitialStates() const {

    return this->qs;
}

std::set<std::string> NFA::getFinalStates() const {

    return this->finalStates;
}

bool NFA::isRecognized(const std::string& word) {

    int length = word.size();
    std::string currentStates;
    bool flag = false;
    for(auto it : this->qs) {

        if(isRecognizedHelper(word, it)) {

            flag = true;
        }
    }
    return flag;
}  

bool NFA::isRecognizedHelper(const std::string& word, const std::string& currentState) {

    if(word.size() == 0) {

        return this->finalStates.find(currentState) != this->finalStates.end();
    }
    if(this->delta[std::make_pair(currentState, word[0])].size() == 0) {

        return false;
    }
    for(auto it : this->delta[std::make_pair(currentState, word[0])]) {

        return isRecognizedHelper(word.substr(1), it);
    }
    return false;
}

NFA& NFA::uni(NFA& nfa) {

    NFA result;
    for (auto it : this->alphabet.getLetters()) {

        result.addLetter(it);
    }

    for (auto it : nfa.getAlphabet().getLetters()) {

        result.addLetter(it);
    }

    for (auto it : this->states) {

        result.addState(it);
    }

    for (auto it : nfa.getStates()) {

        result.addState(it);
    }

    result.setInitialStates(this->qs);
    for (auto it : nfa.getInitialStates()) {

        result.addInitialState(it);
    }
    
    for (auto it : this->delta) {
        for (auto it2 : it.second) {

            result.addTransition(it.first, it2);
        }
    }

    for (auto it : nfa.getDelta()) {
        for (auto it2 : it.second) {

            result.addTransition(it.first, it2);
        }
    }

    for (auto it : this->finalStates) {

        nfa.addFinalState(it);
    }

    for (auto it : nfa.getFinalStates()) {

        nfa.addFinalState(it);
    }

    return nfa;
}

void NFA::processInput(const std::string& input) {
     
    std::ifstream file;
    file.open(input, std::ios::in);
    if (!file.is_open())
    {
        std::cout << "Can't open the file or the path is invalid!" << std::endl;
        return;
    }
    std::cout << "File opened successfully!" << std::endl;
    std::multiset<std::string> words;
    std::string line;
    while(std::getline(file, line)) {

        words.insert(line);
    }
    
    file.close();
    int i = 1;
    for(auto it : words) {

        if(this->isRecognized(it)) {

            std::cout << "The word " << it << " on line " << i << " is recognized!" << std::endl; 
        }
        i++;
    }
}