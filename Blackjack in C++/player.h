#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <string.h>
#include "deck.h"

#define MAX_STRING_SIZE 64

class Player {
    std::string name;
    int hand_value;
    int hidden_value;
    int balance;
    int aces;
    int ncards;
    int cards[11];
    bool isDealer;

    public:
        Player(std::string const &name, int balance);
        Player();
        void setDealer(bool dealer);
        void setName(std::string const &name);
        std::string getName();
        void setBalance(int balance);
        int  getBalance();
        void setHandValue(int handvalue);
        void setAces(int aces);
        void setnCards(int ncards);
        void checkAce();
        int  cardValue(int card);
        void adjustAce();
        void resetPlayer();
        int  getHandValue();
        void setHiddenHandValue(int value);
        int getHiddenHandValue();
        void printHand();
        void hit(Deck *d);
        void hiddenhit(Deck *d);
        std::string const faceValue(int card); 
        std::string const stringValue(int card);
        void revealHidden();
        bool checkBlackjack();
};

//Constructor for player class
Player::Player(std::string const &p_name, int p_balance){
    setName(p_name);
    setBalance(p_balance);
    setHandValue(0);
    setAces(0);
    setnCards(0);
    setDealer(false);
    
};
//Overloaded constructor for player class, will be used to initiate dealer 
//as a player class, but without a name and balance
Player::Player() {
    setHandValue(0);
    setAces(0);
    setnCards(0);
    setDealer(true);
}

//Set dealer setter method for boolean if the class is dealer or not
void Player::setDealer(bool dealer) {
    isDealer = dealer;
}

//Set name setter method for player class
void Player::setName(std::string const &p_name) {
    name = p_name;
}

//Get name getter method for player class
std::string Player::getName() {
    return name;
}

//Set balance setter method for player class
void Player::setBalance(int p_balance) {
    balance = p_balance;
}

//Get balance getter method for player class
int Player::getBalance() {
    return balance;
}
//Set Hand Value setter method for player class
void Player::setHandValue(int p_hand_value) {
    hand_value = p_hand_value;
}

//Set Aces setter method for player class
void Player::setAces(int p_aces) {
    aces = p_aces;
}

//Set nCards setter method for player class 
void Player::setnCards(int p_ncards) {
    ncards = p_ncards;
}

//Return value of card for player class
int Player::cardValue(int p_card) {
    if (((p_card % 13) + 1) < 10) {
        return ((p_card % 13) + 1);
    } else {
        return 10;
    }
}

//Method to check if the player recieved an ace, and to change number of aces
// and hand value of the player accordingly
void Player::checkAce() {
    if (cardValue(cards[ncards-1]) == 1) {
        if ((hand_value + 10) <= 21) {
            setAces(aces + 1);
            setHandValue(hand_value + 10);
        }
    }
}
//Method to change value of users aces from 11 to 1 if he has busted.
void Player::adjustAce() {
    while (aces > 0) {
        if ((hand_value) > 21 && aces > 0) {
            setAces(aces - 1);
            setHandValue(hand_value - 10);
        }
        if (hand_value <= 21) {
            break;
        }
    }
}

//Method to reset player back to original state
void Player::resetPlayer() {
    setnCards(0);
    setHandValue(0);
}

//Method to return the value of the players hand
int Player::getHandValue() {
    return hand_value;
}

//Method to set hidden hand value of the dealer
void Player::setHiddenHandValue(int value) {
    hidden_value = value;
}

int Player::getHiddenHandValue() {
    return hidden_value;
}

//Method to print out the hand that the player currently has
void Player::printHand() {
    for (int i = 0; i < ncards; i++) {
        std::cout << faceValue(cards[i]) << " of " << stringValue(cards[i]) << std::endl;
    }
}

//Method for player hiting i.etakes card from deck
void Player::hit(Deck *d) {
    cards[ncards] = d->cards[0]; 
    setnCards(ncards + 1);
    setHandValue(hand_value + cardValue(d->cards[0]));
    setHiddenHandValue(hand_value);
    checkAce();
    Deck::popFromDeck(d);
    if (isDealer) {
        std::cout << "Dealer got a " << faceValue(cards[ncards-1]) << " of " << stringValue(cards[ncards-1]) << std::endl;
        std::cout << "Dealer's new hand value is: " << getHandValue() << std::endl;
    } else {
        std::cout << "You got a " << faceValue(cards[ncards-1]) << " of " << stringValue(cards[ncards-1]) << std::endl;
        std::cout << "Your new hand value is: " << getHandValue() << std::endl;
    }
}

void Player::hiddenhit(Deck *d) {
    cards[ncards] = d->cards[0];
    setnCards(ncards + 1);
    setHandValue(hand_value + cardValue(d->cards[0]));
    checkAce();
    Deck::popFromDeck(d);
    if (isDealer) {
        std::cout << "Dealer has got his face down card" << std::endl;  
        std::cout << "Dealer's hand value is: " << getHiddenHandValue() << std::endl; 
    } 
}

//Method to return the face value of the card given as a string
std::string const Player::faceValue(int card) {
    int value = card % 13 + 1;
    switch(value) {
        case 1 :
            return "Ace";
        case 2: 
            return "Two";
        case 3: 
            return "Three";
        case 4: 
            return "Four";
        case 5:
            return "Five";
        case 6: 
            return "Six";
        case 7:
            return "Seven";
        case 8:
            return "Eight";
        case 9:
            return "Nine";
        case 10:
            return "Ten";
        case 11:
            return "Jack";
        case 12:
            return "Queen";
        case 13:
            return "King";
    }
    return "Not possible";
}

//Method to return the color of the card given as the input
std::string const Player::stringValue(int card) {
    if (card % 4 == 0) {
        return "Diamond";
    } else if (card % 4 == 1) {
        return "Hearts";
    } else if (card % 4 == 2) {
        return "Clubs";
    } else {
        return "Spades";
    }
}

//Method to reveal to the user what the dealers face down card was
void Player::revealHidden() {
    std::cout << "The dealers hidden card was " << faceValue(cards[ncards-1]) << " of " << stringValue(cards[ncards-1]) << std::endl;
    std::cout << "Dealer's new hand value is: " << getHandValue() << std::endl;
    delay(2);
}

//Method to chedk if the user got blackjack 
bool Player::checkBlackjack() {
    if (getHandValue() == 21) {
        std::cout << "The User has gotten blackjack. Let's see what the dealer gets" << std::endl;
        return true;
    }
}

//Useful button functions that are used
int ifPressed (bool isPressed[4]) {
    for (int i = 0; i < 4; i++) {
        if (isPressed[i]) {
            return i;
        }
    }
    return -1;
}

void clearInput (bool isPressed[4]) {
    for (int i = 0; i < 4; i++) {
        isPressed[i] = false;
    }
    return;
}