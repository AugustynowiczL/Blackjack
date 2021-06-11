#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "deck.h"

#define MAX_STRING_SIZE 64

typedef struct dealer {
    int hand_value;
    int aces;
    int ncards;
    int cards[11];
}dealer;

dealer* dealer_init() {
    dealer *p = NULL;
    p = (dealer *)calloc(sizeof(dealer), 1);
    p->aces = 0;
    p->ncards = 0;
    p->hand_value = 0;
    return p;
}

typedef struct player {
    char name[MAX_STRING_SIZE];
    int hand_value;
    int balance;
    //choose 11 because max amount of cards possible before busting
    int aces;
    int ncards;
    int cards[11];
} player;

player* player_init(char *name, int balance) {
    //Initalize player struct with input name being the players name
    // and input balance being players starting balance. 
    player *p;
    p = (player *)calloc(sizeof(player), 1);
    strcpy(p->name, name);
    p->aces = 0;
    p->hand_value = 0;
    p->ncards = 0;
    p->balance = balance;
    return p;
}

void checkAce(player *p) {
    if (cardValue(p->cards[p->ncards-1]) == 1) {
        if ((p->hand_value + 10) <= 21) {
            p->aces += 1;
            p->hand_value += 10;
        }
    }
}

void checkAceD(dealer *p) {
    if (cardValue(p->cards[p->ncards-1]) == 1) {
        if ((p->hand_value + 10) <= 21) {
            p->aces += 1;
            p->hand_value += 10;
        }
    }
}

void adjustAce(player *p) {
    while (p->aces > 0) {
        if ((p->hand_value) > 21 && p->aces > 0) {
            p->aces -= 1;
            p->hand_value -= 10;
        }
    }
}
void adjustAceD(dealer *p) {
    while (p->aces > 0) {
        if ((p->hand_value) > 21 && p->aces > 0) {
            p->aces -= 1;
            p->hand_value -= 10;
        }
    }
}

void resetPlayer(player* p) {
    p->ncards = 0;
    p->hand_value = 0;
    return;
}

void resetDealer(dealer* p) {
    p->ncards = 0;
    p->hand_value = 0;
    return;
}

//Return the value of the players hand
int handValue(player* p) {
    return p->hand_value;
}
//Return the value of the dealers hand
int dealerHandValue(dealer* p) {
    return p->hand_value;
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
    checkAceD(dl);
    popFromDeck(d);
    printf("Dealer gets %s of %s\n", faceValue(dl->cards[dl->ncards-1]), stringValue(dl->cards[dl->ncards-1]));
    printf("Dealers new hand value is: %d\n", dealerHandValue(dl));
}

//Player hits, takes card from deck
void hit(player* p, deck* d) {
    p->cards[p->ncards] = d->cards[0]; 
    p->ncards++;
    p->hand_value += cardValue(d->cards[0]);
    checkAce(p);
    popFromDeck(d);
    printf("You got a %s of %s\n", faceValue(p->cards[p->ncards-1]), stringValue(p->cards[p->ncards-1]));
    printf("Your new hand value is: %d\n", handValue(p));
}