#ifndef ALPHABET_H
#define ALPHABET_H

#include <set>

//Aзбуката на автомат
class Alphabet {

    private:
        std::set<char> letters;

        void copy(const Alphabet&);

    public:
        //Default constructor
        Alphabet();
        //Constructor with argument
        Alphabet(const std::set<char>&);
        //Copy constructor
        Alphabet(const Alphabet&);
        //Operator=
        Alphabet& operator=(const Alphabet&);
        //Destructor
        ~Alphabet();

        //Setter
        void setLetters(const std::set<char>&);
        //Getter
        std::set<char> getLetters() const;

        //Add letter to the alphabet
        Alphabet& addLetter(const char&);
        //Remove letter from the alphabet       
        Alphabet& removeLetter(const char&);
};

#endif