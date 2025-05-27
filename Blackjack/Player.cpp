#include "Player.hpp"
#include "card.hpp"
#include <algorithm>
#include <iostream>  // Added for cout
using namespace std;

Player::Player(const string& playerName, bool dealer)
    : score(0), isDealer(dealer), isStanding(false), name(playerName) {}

void Player::hit(const Card& card) {
    hand.push_back(card);
    calculateScore();
}

void Player::stand() {
    isStanding = true;
}

bool Player::hasBlackjack() const {
    if (hand.size() != 2) return false;
    
    bool hasAce = false;
    bool hasTen = false;
    
    for (const Card& card : hand) {
        int value = card.getValue();
        if (value == 11) hasAce = true;
        if (value == 10) hasTen = true;
    }
    
    return hasAce && hasTen;
}

bool Player::isBusted() const {
    return score > 21;
}

int Player::getScore() const {
    return score;
}

bool Player::standing() const {
    return isStanding;
}

bool Player::dealer() const {
    return isDealer;
}

string Player::getName() const {
    return name;
}

std::vector<Card> Player::getHand() const {
    return hand;
}


void Player::reset() {
    hand.clear();
    score = 0;
    isStanding = false;
}

bool Player::dealerDecision() const {
    if (!isDealer) return false;
    return score < 17;
}

void Player::printHand() const {
    cout << name << "'s hand: ";
    for (size_t i = 0; i < hand.size(); i++) {
        if (i > 0) cout << ", ";  
        cout << hand[i].toString();
    }
    cout << " → Total: " << getScore() << endl;
}

void Player::calculateScore(){
    score = 0;
    int aceCount = 0;
    
    // First pass: count all non-ace cards
    for (const Card& card : hand) {
        int value = card.getValue();
        if (value == 11) {
            aceCount++;
        } else {
            score += value;
        }
    }
    
    // Handle aces
    for (int i = 0; i < aceCount; i++) {
        // Count ace as 11 if it won't bust, otherwise 1
        if (score + 11 <= 21) {
            score += 11;
        } else {
            score += 1;
        }
    }
}