#ifndef deck_h
#define deck_h
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define NUM_CARDS 52

class Deck {
    int cards[NUM_CARDS];
    int number;
    friend class Player;
    public:
        Deck();
        static void popFromDeck(Deck *d); 
        void resetDeck();
        void shuffle();
};
 
//Method to initalize new deck with 52 cards
Deck::Deck() {
    for (int i = 0; i < NUM_CARDS; i++) {
        cards[i] = i;
    }
    number = NUM_CARDS;
}

//Method to remove first card of the deck because it has been put into a players hand
void Deck::popFromDeck(Deck *d) {
    for (int i = 0; i < d->number-1; i++) {
        d->cards[i] = d->cards[i+1];
    }
    d->number -= 1;
}

void Deck::resetDeck() {
    for (int i = 0; i < NUM_CARDS; i++) {
        cards[i] = i;
    }
    number = NUM_CARDS;
    shuffle();
}


// Code below found online
// Used to randomize an array of numbers
// C Program to shuffle a given array
// A utility function to swap to integers
void swap (int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}
  
// A function to generate a random permutation of arr[]
void Deck::shuffle()
{
    // Use a different seed value so that we don't get same
    // result each time we run this program
    srand ( time(NULL) );
 
    // Start from the last element and swap one by one. We don't
    // need to run for the first element that's why i > 0
    for (int i = number-1; i > 0; i--)
    {
        // Pick a random index from 0 to i
        int j = rand() % (i+1);
 
        // Swap arr[i] with the element at random index
        swap(&cards[i], &cards[j]);
    }
}

//Timer for delay after printf
void delay(int number_of_seconds)
{
    // Converting time into milli_seconds
    int milli_seconds = 1000 * number_of_seconds;
  
    // Storing start time
    clock_t start_time = clock();
  
    // looping till required time is not achieved
    while (clock() < start_time + milli_seconds)
        ;
}
#endif