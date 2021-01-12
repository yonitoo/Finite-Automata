#include "Alphabet.h"
#include <iostream>

void Alphabet::copy(const Alphabet& other) {

    this->letters = other.letters;
}

Alphabet::Alphabet() : letters(std::set<char>( {'@'})) {

}

Alphabet::Alphabet(const std::set<char>& letters) {

    this->letters = letters;
}

Alphabet::Alphabet(const Alphabet& other) {

    this->letters = other.letters;
}

Alphabet& Alphabet::operator=(const Alphabet& other) {

    if(this != &other) {

        copy(other);
    }

    return *this;
}
Alphabet::~Alphabet() {

}

void Alphabet::setLetters(const std::set<char>& letters) {

    this->letters = letters;
}

std::set<char> Alphabet::getLetters() const {

    return this->letters;
}

Alphabet& Alphabet::addLetter(const char& letter) {

    if(letter != '&' && letter != '(' && letter != ')' && letter != '*' &&
       letter != '+' && letter != '.' && letter != '?' && letter != '@') {

        this->letters.insert(letter);
    }
    else {
        
        std::cout << "You can't add reserved characters" << std::endl;
    }
    return *this;
}

Alphabet& Alphabet::removeLetter(const char& letter) {

    if(this->letters.find(letter) != this->letters.end()) {
        
        this->letters.erase(letter);
    }
    else {
        
        std::cout << "You can not remove a non-existing letter!" << std::endl;
    }
    return *this;
}