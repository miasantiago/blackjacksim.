#ifndef CARD_HPP
#define CARD_HPP

#include <string>
using namespace std;

class Card {
private:
    string rank;
    string suit;

public:
    Card(const string& r, const string& s);
    string getRank() const;
    string getSuit() const;
    int getValue() const;
    string toString() const;
};

#endif
