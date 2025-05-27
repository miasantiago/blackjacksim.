#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <vector>
#include <string>
#include <iostream>  
#include "card.hpp" // Ensure this file defines the Card class
#include <algorithm>
using namespace std;

class Player {
private:
    vector<Card> hand;  
    int score;              
    bool isDealer;          
    bool isStanding;        
    string name;       

    void calculateScore();

public:
    Player(const string& playerName, bool dealer = false);

    // Game actions
    void hit(const Card& card);
    void stand();
    void reset();

    bool hasBlackjack() const;
    bool isBusted() const;
    bool standing() const;
    bool dealer() const;
    bool dealerDecision() const;


    int getScore() const;
    string getName() const;
    vector<Card> getHand() const;


    void printHand() const;
};

#endif