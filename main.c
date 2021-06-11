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
    printf("What is your name?\n");
    char name[MAX_STRING_SIZE];
    scanf("%s", name);
    printf("How much money would you like to start with?\n");
    int balance;
    scanf("%d", &balance);
    printf("What will be your current bet?\n");
    int bet;
    scanf("%d", &bet);

    //Initalize player and deck
    player *p;
    p = player_init(name, balance);
    deck *d;
    d = deck_init();
    shuffle(d->cards, NUM_CARDS);
    //Initialize dealer hand
    dealer *dl;
    dl = dealer_init();

    //Welcome Message to the User
    printf("/////WELCOME TO BLACKJACK CASINO//////\n");
    delay(2);
    printf("%s, you are starting with %d dollars today. Enjoy your stay!\n", p->name, p->balance);
    delay(2);

    //Begin main gameplay loop
    while (p->balance > 0) {
        //Give player first and second card and take card out of the deck
        hit(p, d);
        delay(2);
        hit(p, d);
        delay(2);
        //Give dealer his first card
        dealerHit(dl, d);
        delay(2);
        char move;
        bool pbust = false;
        bool dbust = false;
        bool playon = true;
        //Inform the user of current situation
        printf("Your balance is: %d\n", p->balance);
        delay(2);
        //Ask the user for his next move
        printf("What would you like to do?\n");
        printf("H: Hit, S: Stand: D: Double, C: Change Bet\n");
        scanf(" %c", &move);
        toupper(move);
        //when the user decides to hit
        if (move == 'H' || move == 'D') {
            //If the user doubles display this message
            if (move == 'D') {
                printf("User has doubled!\n");
                delay(2);
                p->balance -= 2*bet;
                printf("New Balance: %d\n", p->balance);
                delay(2);
            //If the user hits display this message
            } else {
                printf("User has hit!\n");
                delay(2);
                p->balance -= bet;
                printf("New Balance: %d\n", p->balance);
                delay(2);
            }
            //Loop for the user to play on
            while (playon && move != 'D') {
                hit(p, d);
                adjustAce(p);
                delay(2);
                //If User busts then exit loop and check dealers hand
                if (handValue(p) > 21) {
                    printf("User has bust with %d\n", handValue(p));
                    delay(2);
                    pbust = true;
                    break;
                //If the user gets blackjack exit loop and check dealers hand
                } else if (handValue(p) == 21) {
                    printf("User has gotten %d, thats blackjack. Lets check the dealers hand!\n", handValue(p));
                    delay(2);
                    playon = false;
                }
                //Ask the user if he wants to hit again or stand
                printf("What would you like to do?\n");
                printf("H: Hit, S: Stand\n");
                scanf(" %c", &move);
                toupper(move);
                //If user decides to hit again repeat this loop
                if (move == 'H') {
                    continue;
                //If user decides to stand exit loop and check dealers hand
                } else {
                    playon = false;
                }
            }
        //If the user wants to change his current bet
        } else if (move == 'C') {
            printf("What would you like to change the bet to?\n");
            scanf(" %d", &bet);
            printf("The bet has been changed to: %d\n", bet);
            delay(2);
        //If the user stands, do nothing and check the dealers hand
        } else {
            printf("User has stood\n");
            p->balance -= bet;
            delay(2);
        }

        //User has completed his move, let the dealer get his cards
        //If user has bust, do not check dealers hand and reset deck
        if (pbust == false) {
            printf("Dealer will stand until 17\n");
            delay(2);
            //Dealer keeps drawing cards until he busts or get >= 17
            while (dealerHandValue(dl) < 17 && !dbust) {
                dealerHit(dl, d);
                adjustAceD;
                delay(2);
                //If the dealer busts exit the loop
                if (dealerHandValue(dl) > 21) {
                    printf("Dealer has bust!, the user wins!\n");
                    delay(2);
                    //Credit the users account
                    p->balance += 2*bet;
                    printf("The user has been creditted %d\n", 2*bet);
                    delay(2);
                    dbust = true;
                }
            }
        }
        //If neither the dealer or the player has busts, compare their two hands and decide a winner
        if (!pbust && !dbust) {
            //If the player wins 
            if (dealerHandValue(dl) < handValue(p)) {
                printf("Dealer loses, player wins %d\n", 2*bet);
                p->balance += 2*bet;
                delay(2);
            //If the dealer wins 
            } else if (dealerHandValue(dl) > handValue(p)) {
                printf("Dealer wins, player loses!\n");
                delay(2);
            //If the dealer and player tie
            } else {
                printf("There is a push!\n");
                p->balance += bet;
                delay(2);
            }
        }
        //Check if player has a negative balance, tell him he is out of money and must leave.
        if (p->balance <= 0) {
            printf("It seems like your you've run out of money. Thanks for playing, better luck next time\n");
        }
        //Reset the players hand
        //Reset the deck
        resetDeck(d);
        resetPlayer(p);
        resetDealer(dl);
        //Give a message to the player if he wants to continue
        printf("Would you like to play another hand? (Y/N)\n");
        scanf(" %c", &move);
        toupper(move);
        //Closing statement to the player
        if (move == 'N') {
            printf("Thank you for playing today: %s, you ended today with a final balance of: %d\n", p->name, p->balance);
            delay(2);
            if (p->balance < balance) {
                printf("You lost %d today. Better luck next time\n", balance - p->balance);
                delay(2);
            } else {
                printf("Congratulations, you won %d today. We hope you come back!\n", p->balance - balance);
                delay(2);
            }
            //While loop condition is until player balance is < 0, therefore to exit give player negative balance
            p->balance = -1;
        } else {
            printf("Your balance is: %d. We will deal you another hand\n", p->balance);
            delay(4);
        }
    }
    return 0;
}