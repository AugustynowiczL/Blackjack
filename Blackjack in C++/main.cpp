#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h> 
#include "player.h"
#include "deck.h"
#define MAX_STRING_SIZE 64

int main() {

    //Get player info
    std::cout << "What is your name?: \n";
    std::string name;
    std::cin >> name;
    std::cout << "How much money would you like to start with?\n";
    int balance;
    std::cin >> balance;
    std::cout << "What will be your current bet?\n";
    int bet;
    std::cin >> bet;

    //Initalize player, dealer, and deck
    Player *p = new Player(name, balance);
    Player *dl = new Player();
    Deck *d = new Deck();
    //Shuffle the deck
    d->shuffle();

    //Welcome Message to the User
    std::cout << "/////WELCOME TO BLACKJACK CASINO//////\n";
    delay(2);
    std::cout << p->getName() << " you are starting with " << p->getBalance() <<
     " dollars today. Enjoy your stay!\n";
    delay(2);

    //Begin main gameplay loop
    while (p->getBalance() > 0) {
        char move;  
        std::cout << "Would you like to change the bet? (Y/N)" << std::endl;
        scanf(" %c", &move);
        toupper(move);
        if (move == 'Y') {
            std::cout << "What would you like to change the bet to?\n";
            scanf(" %d", &bet);
            std::cout << "The bet has been changed to: " << bet << std::endl;
            delay(2);
        }
        std::cout << "Let the game begin\n";
        delay(1);
        std::cout << bet << " dollars have been taken from your account\n";
        delay(1);
        p->setBalance(p->getBalance() - bet);
        std::cout << "New Balance: " << p->getBalance() << std::endl;
        //Give player first and second card and take card out of the deck
        p->hit(d);
        delay(2);
        p->hit(d);
        delay(2);
        //Give dealer his first card
        dl->hit(d);
        delay(2);
        bool pbust = false;
        bool dbust = false;
        bool playon = true;
        //If the user hits blackjack, skip steps where the user hits
        if (p->getHandValue() == 21) {
            std::cout << "User has got blackjack. Lets see what the dealer will get" << std::endl;
        } else {
            std::cout << "What would you like to do?\n";
            std::cout << "H: Hit, S: Stand: D: Double\n";
            scanf(" %c", &move);
            toupper(move);
            //when the user decides to hit
            if (move == 'H' || move == 'D') {
                //If the user doubles display this message
                if (move == 'D') {
                    printf("User has doubled!\n");
                    delay(2);
                    p->setBalance(p->getBalance() - bet);
                    std::cout << "New Balance: " << p->getBalance() << std::endl;
                    delay(2);
                //If the user hits display this message
                } else {
                    std::cout << "User has hit!\n";
                    delay(2);
                    //Loop for the user to play on
                    while (playon) {
                        p->hit(d);
                        p->adjustAce();
                        delay(2);
                        //If User busts then exit loop and check dealers hand
                        if (p->getHandValue() > 21) {
                            std::cout << "User has bust with " << p->getHandValue() << std::endl;
                            delay(2);
                            pbust = true;
                            break;
                        //If the user gets blackjack exit loop and check dealers hand
                        } else if (p->getHandValue() == 21) {
                            std::cout << "User has gotten " << p->getHandValue() << " thats blackjack. Lets check the dealers hand!\n";
                            delay(2);
                            playon = false;
                        }
                        //Ask the user if he wants to hit again or stand
                        std::cout << "What would you like to do?\n";
                        std::cout << "H: Hit, S: Stand\n";
                        scanf(" %c", &move);
                        toupper(move);
                        //If user decides to hit again repeat this loop
                        if (move == 'H') {
                            std::cout << "User hits\n";
                        //If user decides to stand exit loop and check dealers hand
                        } else {
                            std::cout << "User has stood\n";
                            playon = false;
                        }
                    }
                }
            //If the user stands, do nothing and check the dealers hand
            } else {
                std::cout << "User has stood\n";
                delay(2);
            }
        }

        //User has completed his move, let the dealer get his cards
        //If user has bust, do not check dealers hand and reset deck
        if (pbust == false) {
            std::cout << "Dealer will stand until 17\n";
            delay(2);
            //Dealer keeps drawing cards until he busts or get >= 17
            while (dl->getHandValue() < 17 && !dbust) {
                dl->hit(d);
                dl->adjustAce();
                delay(2);
                //If the dealer busts exit the loop
                if (dl->getHandValue() > 21) {
                    std::cout << "Dealer has bust!, the user wins!\n";
                    delay(2);
                    //Credit the users account
                    p->setBalance(p->getBalance() + 2*bet);
                    std::cout << "The user has been creditted " << 2*bet << std::endl;
                    delay(2);
                    dbust = true;
                }
            }
        }
        //If neither the dealer or the player has busts, compare their two hands and decide a winner
        if (!pbust && !dbust) {
            //If the player wins 
            if (dl->getHandValue() < p->getHandValue()) {
                std::cout << "Dealer loses, player wins " << 2*bet << std::endl;
                p->setBalance(p->getBalance() + 2*bet);
                delay(2);
            //If the dealer wins 
            } else if (dl->getHandValue() > p->getHandValue()) {
                std::cout << "Dealer wins, player loses!\n";
                delay(2);
            //If the dealer and player tie
            } else {
                std::cout << "There is a push!\n";
                p->setBalance(p->getBalance() + bet);
                delay(2);
            }
        }
        //Check if player has a negative balance, tell him he is out of money and must leave.
        if (p->getBalance() <= 0) {
            std::cout << "It seems like your you've run out of money. Thanks for playing, better luck next time\n";
        }
        //Reset the players hand
        //Reset the deck
        d->resetDeck();
        p->resetPlayer();
        dl->resetPlayer();
        //Give a message to the player if he wants to continue
        std::cout << "Your updated balance is: " << p->getBalance() << std::endl;
        std::cout << "Would you like to play another hand? (Y/N)\n";
        scanf(" %c", &move);
        toupper(move);
        //Closing statement to the player
        if (move == 'N') {
            std::cout << "Thank you for playing today: " << p->getName() << ", you ended today with a final balance of: "<< p->getBalance() << std::endl;
            delay(2);
            if (p->getBalance() < balance) {
                std::cout << "You lost " << balance - p->getBalance() << " dollars today. Better luck next time\n";
                delay(2);
            } else {
                std::cout << "Congratulations, you won " << p->getBalance() - balance << " dollars today. We hope you come back!\n";
                delay(2);
            }
            //While loop condition is until player balance is < 0, therefore to exit give player negative balance
            p->setBalance(-1);
        } else {
            std::cout << "Your balance is: " << p->getBalance() << ". We will deal you another hand\n";
            delay(4);
        }
    }
    return 0;
}