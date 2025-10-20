#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <conio.h>

typedef enum { CLUBS, DIAMONDS, HEARTS, SPADES, CARD } Suit;
typedef enum { TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING, ACE, CARD2 } Rank;

// Card structure
typedef struct {
    Suit suit;
    Rank rank;
} Card;
Card deck[52];
Card hand[52];
Card empty = {CARD, CARD2};
int deckSize;

// Function to print a card (for demonstration)
void printCard(Card c) {
    const char* suitNames[] = {"Clubs", "Diamonds", "Hearts", "Spades", "BLANK"};
    const char* rankNames[] = {"Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten", "Jack", "Queen", "King", "Ace", "BLANK"};
    printf("%s of %s\n", rankNames[c.rank], suitNames[c.suit]);
    return;
}
void printDeck(Card deck[52]){
    int deckpos = 0;
    for(int i = 0; i <= 3; i++){
        for (int j = 0; j <= 12; j++){
            
            deckpos++;
            Card c = {i, j};
            deck[deckpos] = c;

        }
    }
    for(int i = 0; i < 52; i++){
        hand[i].suit = CARD;   
        hand[i].rank = CARD2;
        deck[i];
        if(deck[i].suit == 4 || deck[i].rank == 13){
            continue;
        }else{
            deckSize++;
        }
    }
    printf("Deck initialized... \n");
    printf("\n");
    return;

}
void countDeck(Card deck[52]){
    deckSize = 0;

    for(int i = 0; i < 52; i++){
    
        deck[i];
        if(deck[i].suit == 4 || deck[i].rank == 13){
            continue;
        }else{
            deckSize++;
        }
    }
    printf("Deck size: %d \n",deckSize);
    return;
}
void drawCard(Card deck[52]){
    printf(" \nCard Drawn: \n");
    for(int i = 0; i < 52; i++){
        
        if(hand[i].suit == CARD || hand[i].rank == CARD2){
            int index = rand() % (52 - 0 + 1) + 0;
            while (deck[index].suit == CARD && deck[index].rank == CARD2) {
                index = rand() % 52;
            }
            hand[i]= deck[index];
            deck[index].suit = CARD;  
            deck[index].rank = CARD2;
            printCard(hand[i]);
            countDeck(deck); 
            break; 
        }else{
            continue;
        }
        
    }


    return;
}
void printHand(Card hand[52]){
    printf("\nHand: \n");
    int hands = 52-deckSize;
    for(int i = 0; i < hands; i++){
        printCard(hand[i]);
    }
    return;
}

void startGame(Card deck[52], Card hand[52]){

    srand(time(NULL)); 
    bool deal = true;
    countDeck(deck);
    printf("HAND: \n");
    for(int i = 0; i < 5; i++){
        int index = rand() % (52 - 0 + 1) + 0;
        
        hand[i]= deck[index];
        deck[index] = empty;
        printCard(hand[i]);
    }
    countDeck(deck);
    printf("Turn 1: \n");
    drawCard(deck);
    return;
}
int main() {
    char ch;
    printDeck(deck);
    startGame(deck, hand);


    printf("Press 'd' to draw, 'h' to show hand, 'q' to quit\n");
    while (1) {
        if (_kbhit()) {       // checks if a key was pressed
            ch = _getch();    // gets the key without waiting for Enter

            if (ch == 'd') drawCard(deck);
            else if (ch == 'h') printHand(hand);
            else if (ch == 'q') break;  // quit the loop
        }
    }

    return 0;
}