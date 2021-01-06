#ifndef ALPHABET_H
#define ALPHABET_H

#include <unordered_set>

//Клас за азбуката на автомат
class Alphabet {

    private:
        std::unordered_set<char> letters;

        void copy(const Alphabet&);

    public:
        //Default constructor
        Alphabet();
        //Constructor with argument
        Alphabet(const std::unordered_set<char>&);
        //Copy constructor
        Alphabet(const Alphabet&);
        //Operator=
        Alphabet& operator=(const Alphabet&);
        //Destructor
        ~Alphabet();

        //Setter
        void setLetters(const std::unordered_set<char>&);
        //Getter
        std::unordered_set<char> getLetters() const;

        //Add character to the alphabet
        void addLetter(const char&);
        //Remove letter from the alphabet       
        void removeLetter(const char&);
};

#endif