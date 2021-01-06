#include <iostream>
#include "DFA.cpp"

int main() {

    DFA dfa;
    dfa.addLetter('v');
    dfa.addLetter('i');
    dfa.addLetter('k');
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
    return 0;
}