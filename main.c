#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
    randomize(d->cards, NUM_CARDS);
    //Initialize dealer hand
    dealer *dl;
    dl = dealer_init();


    //Welcome Message to the User
    printf("/////WELCOME TO BLACKJACK CASINO//////\n");
    printf("%s, you are starting with %d dollars today. Enjoy your stay!\n", p->name, p->balance);

    //Give player first and second card and take card out of the deck
    hit(p, d);
    hit(p, d);
    //Give dealer his first card
    dealerHit(dl, d);
    
    while (p->balance > 0) {
        char move[MAX_STRING_SIZE];
        printf("Current bet is: %d\n", bet);
        printf("What would you like to do?\n");
        printf("H: Hit, S: Stand: D: Double, C: Change Bet\n");
        scanf("%s", move);
        toupper(move);
        if (strcmp("H", move)) {
            continue;
        } else if (strcmp("D", move)) {
            continue;
        } else if (strcmp("C", move)) {
            printf("What would you like to change the bet to?\n");
            scanf("%d", bet);
            printf("The bet has been changed to: %d\n");
            continue;
        } else {

        }

        break;
    }
    return 0;
}