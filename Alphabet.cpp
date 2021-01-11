#include "Alphabet.h"

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

    //TODO add the invalid symbols to a set and check set.find(letter)
    if(letter != '&' && letter != '(' && letter != ')' && letter != '*' &&
       letter != '+' && letter != '.' && letter != '?' && letter != '@' &&
       this->letters.find(letter) == this->letters.end()) {

        this->letters.insert(letter);
    }
    //else {exception CannotAddExistingOrInvalidLetter}
    return *this;
}

Alphabet& Alphabet::removeLetter(const char& letter) {

    if(this->letters.find(letter) != this->letters.end()) {
        
        this->letters.erase(letter);
    }
    //else {exception CannotRemoveNonExistingLetter}
    return *this;
}