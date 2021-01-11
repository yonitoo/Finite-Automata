#include <iostream>
#include "Alphabet.h"
#include "DFA.h"
#include "NFA.h"
#include "PDFA.h"
#include "RegEx.h"

int main()
{

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
    if (dfa.canBeRecognized("vik"))
    {

        std::cout << "Successfully recognized the word!" << std::endl;
    }
    else
    {

        std::cout << "The DFA doesn't recognize the word!" << std::endl;
    }

    std::string regex;
    std::cin>>regex;
    RegEx regEx(regex);
    //regEx.transform().determinize().processInput();

    dfa.processInput("input.txt");
    return 0;
}