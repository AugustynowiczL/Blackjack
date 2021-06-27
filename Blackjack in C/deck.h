#ifndef deck_h
#define deck_h
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define NUM_CARDS 52

typedef struct deck {
    int cards[NUM_CARDS];
    int number;
} deck;
 
deck* deck_init() {
    //Initalize deck struct with 52 card deck
    deck *p = NULL;
    p = (deck *)calloc(sizeof(deck), 1);
    for (int i = 0; i < NUM_CARDS; i++) {
        p->cards[i] = i;
    }
    p->number = NUM_CARDS;
    return p;
}
//Remove first card of the deck because it has been put into a players hand
void popFromDeck(deck *d) {
    for (int i = 0; i < d->number-1; i++) {
        d->cards[i] = d->cards[i+1];
    }
    d->number -= 1;
}

//Return the numerical value of the card given the input
int cardValue(int card) {
    if (((card % 13) + 1) < 10) {
        return ((card % 13) + 1);
    } else {
        return 10;
    }
}

char *faceValue(int card) {
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

}

//Return the name of the card given as the input
char *stringValue(int card) {
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

//Line 90-138 adapted from online sources to implement array shuffling, and timer

// C Program to shuffle a given array
// A utility function to swap to integers
void swap (int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}
 
// A utility function to print an array
void printArray (int arr[], int n)
{
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");
}
 
// A function to generate a random permutation of arr[]
void shuffle ( int arr[], int n )
{
    // Use a different seed value so that we don't get same
    // result each time we run this program
    srand ( time(NULL) );
 
    // Start from the last element and swap one by one. We don't
    // need to run for the first element that's why i > 0
    for (int i = n-1; i > 0; i--)
    {
        // Pick a random index from 0 to i
        int j = rand() % (i+1);
 
        // Swap arr[i] with the element at random index
        swap(&arr[i], &arr[j]);
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

void resetDeck(deck *p) {
    for (int i = 0; i < NUM_CARDS; i++) {
        p->cards[i] = i;
    }
    p->number = NUM_CARDS;
    shuffle(p->cards, p->number);
}
#endif
