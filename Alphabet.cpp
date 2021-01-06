#include "Alphabet.h"

void Alphabet::copy(const Alphabet& other) {

    this->letters = other.letters;
}

Alphabet::Alphabet() : letters(std::unordered_set<char>( {'@'})) {

}

Alphabet::Alphabet(const std::unordered_set<char>& letters) {

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

void Alphabet::setLetters(const std::unordered_set<char>& letters) {

    this->letters = letters;
}

std::unordered_set<char> Alphabet::getLetters() const {

    return this->letters;
}

void Alphabet::addLetter(const char& letter) {

    //TODO add the invalid symbols to a set and check set.find(letter)
    if(letter != '&' && letter != '(' && letter != ')' && letter != '*' &&
       letter != '+' && letter != '.' && letter != '?' && letter != '@' &&
       this->letters.find(letter) == this->letters.end()) {

        this->letters.insert(letter);
    }
}

void Alphabet::removeLetter(const char& letter) {

    if(this->letters.find(letter) != this->letters.end()) {
        
        this->letters.erase(letter);
    }
}