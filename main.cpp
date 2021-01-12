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
    dfa.addState("q2");
    dfa.setQs("qs");
    dfa.addTransition(std::make_pair("qs", 'v'), "qs");
    dfa.addTransition(std::make_pair("qs", 'i'), "qs");
    dfa.addTransition(std::make_pair("qs", 'k'), "q2");
    dfa.addTransition(std::make_pair("q2", 'i'), "q2");
    dfa.addTransition(std::make_pair("q2", 'k'), "q2");
    dfa.addFinalState("q2");
    if (dfa.isRecognized("vik"))
    {

        std::cout << "Successfully recognized the word!" << std::endl;
    }
    else
    {

        std::cout << "The DFA doesn't recognize the word!" << std::endl;
    }

    //test wrong input
    dfa.print();
    dfa.processInput("input");
    //test correct input
    //regex = v.i.k 
    //Expected message : The word vik on line 2 is recognized!

    //test correct input with ?
    //regex = ?.?.?
    //Expected message : The word vik on line 2 is recognized!
    std::string regex;
    std::cin>>regex;
    RegEx regEx(regex);
    DFA test = regEx.transform();
    test.print();
    std::string inputFileName;
    std::cin >> inputFileName;
    test.processInput(inputFileName);
    return 0;
}

//TESTS
//Test case 1: correct input
//regex = v.i.k 
//inputFileName = input.txt
//Expected message : The word vik on line 2 is recognized!

//Test case 2: correct input with ?
//regex = ?.?.?
//inputFileName = input.txt
//Expected message : The word vik on line 2 is recognized!

//Test case 3: wrong file name
//regex = a
//inputFileName = input
//Expected message : Can't open the file or the path is invalid!
