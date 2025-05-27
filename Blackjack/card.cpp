#include "card.hpp"
using namespace std;

Card::Card(const string& r, const string& s) : rank(r), suit(s) {}

string Card::getRank() const {
    return rank;
}

string Card::getSuit() const {
    return suit;
}

int Card::getValue() const {
    if (rank == "Ace") {
        return 11;
    } else if (rank == "2") {
        return 2;
    } else if (rank == "3") {
        return 3;
    } else if (rank == "4") {
        return 4;
    } else if (rank == "5") {
        return 5;
    } else if (rank == "6") {
        return 6;
    } else if (rank == "7") {
        return 7;
    } else if (rank == "8") {
        return 8;
    } else if (rank == "9") {
        return 9;
    } else if (rank == "10" || rank == "Jack" || rank == "Queen" || rank == "King") {
        return 10;
    } else {
        return 0; 
    }
}

string Card::toString() const {
    return rank + " of " + suit;
}
