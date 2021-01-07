#include <iostream>
#include "Alphabet.cpp"
#include "DFA.cpp"

int main() {

    Alphabet alphabet;
    alphabet.addLetter('v');
    alphabet.addLetter('i');
    alphabet.addLetter('k');
    DFA dfa;
    dfa.setAlphabet(alphabet);
    dfa.addState("qs");
    dfa.setQs("qs");
    dfa.addTransition(std::make_pair("qs", 'v'), "qs"); 
    dfa.addTransition(std::make_pair("qs", 'i'), "qs"); 
    dfa.addTransition(std::make_pair("qs", 'k'), "qs");
    dfa.addFinalState("qs");
    if(dfa.canBeRecognized("vik")) {

        std::cout << "Successfully recognized the word!" << std::endl;
    }
    else {

        std::cout << "The DFA doesn't recognize the word!" << std::endl;
    }

    dfa.removeLetter('k');
    if(dfa.canBeRecognized("vik")) {

        std::cout << "Successfully recognized the word!" << std::endl;
    }
    else {

        std::cout << "The DFA doesn't recognize the word!" << std::endl;
    }
    return 0;
}