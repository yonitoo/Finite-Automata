#include "DFA.h"
#include <fstream>
#include <iostream>
#include <vector>
#include <queue>

void DFA::copy(const DFA& other) {

    this->alphabet = other.alphabet;
    this->states = other.states;
    this->delta = other.delta;
    this->qs = qs;
    this->finalStates = other.finalStates;
}

void DFA::renameStates(DFA& dfa) {

}

void DFA::dfs(PDFA& pdfa, const DFA& dfa, const std::pair<std::string, std::string>& currentState, std::map<std::pair<std::string, std::string>, bool>& visited) {

    visited[currentState] = true;
    for(auto it : this->alphabet.getLetters()) {
        
        pdfa.addTransition(std::make_pair(currentState, it), 
        std::make_pair(this->delta[std::make_pair(currentState.first, it)], 
        dfa.getDelta()[std::make_pair(currentState.second, it)]));
        pdfa.addState(std::make_pair(this->delta[std::make_pair(currentState.first, it)], 
                                dfa.getDelta()[std::make_pair(currentState.second, it)]));
        if(visited.find(std::make_pair(this->delta[std::make_pair(currentState.first, it)], 
                                        dfa.getDelta()[std::make_pair(currentState.second, it)])) == visited.end()) {
            
            this->dfs(pdfa, dfa, std::make_pair(this->delta[std::make_pair(currentState.first, it)], 
                                        dfa.getDelta()[std::make_pair(currentState.second, it)]), visited);
        }
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

/*
DFA::DFA(const DFA& other) {

    copy(other);
}*/

DFA::DFA(const PDFA& pdfa) {

    this->alphabet = pdfa.getAlphabet();
    std::map<std::pair<std::string, std::string>, std::string> mapStates;
    int i = 0;
    for(auto it : pdfa.getStates()) {
        
        std::string state = "q" + i;
        mapStates[it] = state;
        i++;
    }
    for(auto it : pdfa.getStates()) {
        
        if(it == pdfa.getInitialState()) {

            this->setQs(mapStates[it]);
        }
        if(pdfa.getFinalStates().find(it) != pdfa.getFinalStates().end()) {

            this->addFinalState(mapStates[it]);
        }
        this->addState(mapStates[it]);
    }

    for(auto it : pdfa.getDelta()) {
                
        this->addTransition(std::make_pair(mapStates[it.first.first], it.first.second), mapStates[it.second]);
    }
}

/*
DFA& DFA::operator= (const DFA& other) {

    if(this != &other) {

        copy(other);
    }

    return *this;
}*/

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
    for (auto it : this->delta) {

        if(it.first.second == letter) {

            this->delta.erase(it.first);
        }
    }

    return this->alphabet;
}

void DFA::removeState(const std::string& state) {

    this->states.erase(state);
    for (auto it : this->delta) {

        if(it.first.first == state || it.second == state) {

            this->delta.erase(it.first);
        }
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

bool DFA::isRecognized(const std::string& word) {
    std::map<std::pair<int, std::string>, bool> cache;
    std::queue<std::pair<std::string, int>> Q;
    Q.push(std::make_pair(this->getQs(), 0));
    cache[std::make_pair(0, this->getQs())] = true;

    while(!Q.empty()) {
        std::string state = Q.front().first;
        int pos = Q.front().second;
        Q.pop();

        if(pos == (int)word.size()) {
            break;
        }

        if(this->delta.count(std::make_pair(state, word[pos]))) {
            std::string nextState = this->delta[std::make_pair(state, word[pos])];
            if(!cache.count(std::make_pair(pos + 1, nextState))) {
                Q.push({nextState, pos + 1});
                cache[std::make_pair(pos + 1, nextState)] = true;
            }
        }

        if(this->delta.count(std::make_pair(state, '@'))) {
            std::string nextState = this->delta[std::make_pair(state, '@')];
            if(!cache.count(std::make_pair(pos, nextState))) {
                Q.push({nextState, pos});
                cache[std::make_pair(pos, nextState)] = true;
            }
        }
    }
    
    for(std::string w: this->getFinalStates()) {
        if(cache.count(std::make_pair((int)word.size(), w))) {
             return true;
        }
    }

    return false;
}

PDFA& DFA::uni(const DFA& dfa) {

    PDFA pdfa;
    pdfa.setQs(std::make_pair(this->getQs(), dfa.getQs()));
    for (auto it : this->alphabet.getLetters()) {

        if(it != '@') {

            pdfa.addLetter(it); 
        }
    }

    for (auto it : dfa.getAlphabet().getLetters()) {

        if(it != '@') {

            pdfa.addLetter(it);
        }
    }

    std::pair<std::string, std::string> initialState = pdfa.getInitialState();
    std::map<std::pair<std::string, std::string>, bool> visited;
    this->dfs(pdfa, dfa, initialState, visited);

    for (auto it : pdfa.getStates()) {

        if((this->finalStates.find(it.first) != this->finalStates.end()) &&
           (dfa.getFinalStates().find(it.second) != dfa.getFinalStates().end())) {

            pdfa.addFinalState(it);
        }
    }
    return pdfa;
}

NFA& DFA::uni_2(DFA& dfa) {

    NFA nfa;
    for (auto it : this->alphabet.getLetters()) {

        nfa.addLetter(it);
    }

    for (auto it : dfa.getAlphabet().getLetters()) {

        nfa.addLetter(it);
    }

    for (auto it : this->states) {

        nfa.addState(it);
    }

    for (auto it : dfa.getStates()) {

        nfa.addState(it);
    }

    nfa.addInitialState(this->qs);
    nfa.addInitialState(dfa.getQs());
    
    for (auto it : this->delta) {

        nfa.addTransition(it.first, it.second);
    }

    for (auto it: dfa.getDelta()) {

        nfa.addTransition(it.first, it.second);
    }

    for (auto it : this->finalStates) {

        nfa.addFinalState(it);
    }

    for (auto it : dfa.getFinalStates()) {

        nfa.addFinalState(it);
    }

    return nfa;
}

PDFA& DFA::intersection(const DFA& dfa) {

    PDFA pdfa;
    pdfa.setQs(std::make_pair(this->getQs(), dfa.getQs()));
    for (auto it : this->alphabet.getLetters()) {

        pdfa.addLetter(it);
    }

    for (auto it : dfa.getAlphabet().getLetters()) {

        pdfa.addLetter(it);
    }

    std::pair<std::string, std::string> initialState = pdfa.getInitialState();
    std::map<std::pair<std::string, std::string>, bool> visited;
    this->dfs(pdfa, dfa, initialState, visited);

    for (auto it : pdfa.getStates()) {

        if((this->finalStates.find(it.first) != this->finalStates.end()) &&
           (dfa.getFinalStates().find(it.second) != dfa.getFinalStates().end())) {

            pdfa.addFinalState(it);
        }
    }
    return pdfa;
}        

DFA& DFA::concatenation(const DFA& dfa) {

    for (auto it : dfa.getAlphabet().getLetters()) {

        if(it != '@') {

            this->addLetter(it); 
        }
    }

    for (auto it : dfa.getStates()) {

        this->addState(it);
    }

    for (auto it : dfa.getDelta()) {

        this->addTransition(it.first, it.second);
    }

    std::set<std::string> temp = this->finalStates;
    this->finalStates.clear();

    for (auto it : temp) {
        
        this->addTransition(std::make_pair(it, '@'), dfa.getQs());
    }

    for (auto it : dfa.getFinalStates()) {

        this->addFinalState(it);
    }

    return *this;
}

DFA& DFA::iteration() {

    this->addState("newQs");
    this->addTransition(std::make_pair("newQs", '@'), this->qs);
    this->setQs("newQs");
    this->addFinalState("newQs");
    for (auto it : this->finalStates) {
        //epsilon transition to the previous initial state
        this->addTransition(std::make_pair(it, '@'), this->qs);
    }
    return *this;
}

DFA& DFA::addition()  {

    bool found = false;
    std::set<std::string> newFinals;
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

void DFA::print() const {
    std::vector<std::vector<std::string>> transitions(this->states.size() + 1, 
                std::vector<std::string>(this->alphabet.getLetters().size() + 1, "NULL"));
    std::vector<std::string> st;
    std::vector<char> letters;
    std::cout << "The letters of the alphabet are:";
    for(auto it : this->alphabet.getLetters()) {

        if(it != '@') {

            std::cout << it << " ";
        }
        letters.push_back(it);
    }

    std::cout << std::endl << "The initial state is: " << this->qs << std::endl;

    std::cout << "The states are: ";
    for(auto it : this->states) {

        std::cout << it << " ";
        st.push_back(it);
    }

    std::cout << std::endl << "The final states are: ";
    for(auto it : this->finalStates) {

        std::cout << it << " ";
    }
    std::cout << std::endl << std::endl << '\t';
    
    for(int i = 0 ; i < st.size() ; i++) {
        transitions[i][0] = st[i];
        for(int j = 1 ; j <= letters.size() ; j++) {
                
            if(this->delta.count(std::make_pair(st[i], letters[j - 1]))) {

                transitions[i][j] = this->getDelta()[std::make_pair(st[i], letters[j - 1])];
            }
        }
    }

    for(auto it : this->alphabet.getLetters()) {

        std::cout << it << '\t';
    }

    std::cout << std::endl;
    for(int i = 0 ; i < st.size() ; i++) {
        for(int j = 0 ; j <= letters.size() ; j++) {

            std::cout << transitions[i][j] << '\t';
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

std::string DFA::transform() {
    
}

NFA& DFA::toNFA() {

    NFA nfa;
    nfa.setAlphabet(this->alphabet);
    for(auto it : this->states) {
        
        if(it == this->qs) {

            nfa.addInitialState(it);
        }
        if(this->finalStates.find(it) != this->finalStates.end()) {

            nfa.addFinalState(it);
        }
        nfa.addState(it);
    }

    for(auto it : this->delta) {
                
        nfa.addTransition(it.first, it.second);
    }

    return nfa;
}

void DFA::processInput(const std::string& input) {
     
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