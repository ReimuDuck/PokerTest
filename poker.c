#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <conio.h>

#define DECKSIZE 52
typedef enum { CLUBS, DIAMONDS, HEARTS, SPADES, CARD } Suit;
typedef enum { TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING, ACE, CARD2 } Rank;

// Card structure
typedef struct {
    Suit suit;
    Rank rank;
} Card;
Card deck[DECKSIZE];
Card hand[DECKSIZE];
Card empty = {CARD, CARD2};
int deckSize;


void printCard(Card c) {
    const char* suitNames[] = {"Clubs", "Diamonds", "Hearts", "Spades", "BLANK"};
    const char* rankNames[] = {"Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten", "Jack", "Queen", "King", "Ace", "BLANK"};
    printf("%s of %s\n", rankNames[c.rank], suitNames[c.suit]);
    return;
}
void printDeck(void){
    int deckpos = 0;
    for(int i = CLUBS; i <= SPADES; i++){
        for (int j = TWO; j <= ACE; j++){
            deck[deckpos].suit = i;
            deck[deckpos].rank = j;
            deckpos++;
        }
    }
    for (int i = 0; i < DECKSIZE; i++) {
        hand[i] = empty;
    }
    deckSize = DECKSIZE;
    printf("Deck initialized... \n");
    printf("\n");
    return;

}
void countDeck(void){
    deckSize = 0;

    for(int i = 0; i < DECKSIZE; i++){
        
        deck[i];
        if(!(deck[i].suit == 4 && deck[i].rank == 13)){
            deckSize++;
        }
    }
    printf("Deck size: %d \n",deckSize);
    return;
}
void drawCard(void){
    printf(" \nCard Drawn: \n");
    for(int i = 0; i < DECKSIZE; i++){
        
        if(hand[i].suit == CARD || hand[i].rank == CARD2){
            int index =  rand() % DECKSIZE;
            while (deck[index].suit == CARD && deck[index].rank == CARD2) {
                index = rand() % DECKSIZE;
            }
            hand[i]= deck[index];
            deck[index].suit = CARD;  
            deck[index].rank = CARD2;
            printCard(hand[i]);
            countDeck(); 
            break; 
        }else{
            continue;
        }
        
    }


    return;
}
void printHand(void){
    printf("\nHand: \n");
    int hands = DECKSIZE-deckSize;
    for(int i = 0; i < hands; i++){
        printCard(hand[i]);
    }
    return;
}

void startGame(void){

    srand(time(NULL)); 
    countDeck();
    printf("Dealing 5 cards... \n");
    for(int i = 0; i < 5; i++){
        int index = rand() % DECKSIZE;
        
        while (deck[index].suit == CARD && deck[index].rank == CARD2)
            index = rand() % DECKSIZE;
        
        hand[i]= deck[index];
        deck[index] = empty;
        printCard(hand[i]);
    }
    countDeck();
    printf("Turn 1: \n");
    drawCard();
    return;
}
int main() {
    char ch;
    printDeck();
    startGame();


    printf("Press 'd' to draw, 'h' to show hand, 'q' to quit\n");
    while (1) {
        if (_kbhit()) {       // checks if a key was pressed
            ch = _getch();    // gets the key without waiting for Enter

            if (ch == 'd') drawCard();
            else if (ch == 'h') printHand();
            else if (ch == 'q') break;  // quit the loop
        }
    }
    printf("\nExiting...\n");

    return 0;
}