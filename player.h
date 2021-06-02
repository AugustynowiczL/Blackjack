#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "deck.h"

#define MAX_STRING_SIZE 64

typedef struct dealer {
    int hand_value;
    int ncards;
    int cards[11];
}dealer;

dealer* dealer_init() {
    dealer *p = NULL;
    p = (dealer *)calloc(sizeof(dealer), 1);
    p->ncards = 0;
    p->hand_value = 0;
    return p;
}

typedef struct player {
    char name[MAX_STRING_SIZE];
    int hand_value;
    int balance;
    //choose 11 because max amount of cards possible before busting
    int ncards;
    int cards[11];
} player;

player* player_init(char *name, int balance) {
    //Initalize player struct with input name being the players name
    // and input balance being players starting balance. 
    player *p;
    p = (player *)calloc(sizeof(player), 1);
    strcpy(p->name, name);
    p->hand_value = 0;
    p->ncards = 0;
    p->balance = balance;
    return p;
}


int checkOutcome(player *p, dealer *dl) {
    
}



//Return the value of the players hand
int handValue(player* p) {
    int value = 0;
    for (int i = 0; i < p->ncards; i++) {
        value += cardValue(p->cards[i]);
    }
    return value;
}
//Return the value of the dealers hand
int dealerHandValue(dealer* p) {
    int value = 0;
    for (int i = 0; i < p->ncards; i++) {
        value += cardValue(p->cards[i]);
    }
    return value;
}

//Print out the hand that the player currently has
void printHand(player *p) {
    for (int i = 0; i < p->ncards; i++) {
        printf("%s of %s\n", faceValue(p->cards[i]), stringValue(p->cards[i]));
    }
}


void dealerHit(dealer* dl, deck *d) {
    dl->cards[dl->ncards] = d->cards[0];
    dl->ncards += 1;
    dl->hand_value += cardValue(d->cards[0]);
    popFromDeck(d);
    printf("Dealer gets %s of %s\n", faceValue(dl->cards[dl->ncards-1]), stringValue(dl->cards[dl->ncards-1]));
    printf("Dealers new hand value is: %d\n", dealerHandValue(dl));
}

//Player hits, takes card from deck
void hit(player* p, deck* d) {
    p->cards[p->ncards] = d->cards[0]; 
    p->ncards++;
    p->hand_value += cardValue(d->cards[0]);
    popFromDeck(d);
    printf("You got a %s of %s\n", faceValue(p->cards[p->ncards-1]), stringValue(p->cards[p->ncards-1]));
    printf("Your new hand value is: %d\n", handValue(p));
}