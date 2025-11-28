#include <iostream>
#include <cstdlib>
#include <ctime>
#include <conio.h>
#include <vector>
using namespace std;

#define LOSS 21

// Enums for Suit and Rank
typedef enum { CLUBS, DIAMONDS, HEARTS, SPADES } Suit;
typedef enum { TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING, ACE } Rank;

// Card structure
typedef struct {
    Suit suit;
    Rank rank;
} Card;

// Global deck,hands and score
vector<Card> deck;
vector<Card> hand;
vector<Card> dealer;
int score = 0;

// -------------------- Display Class --------------------
class Display {
public:
    static void printCard(const Card &c) {
        const char* suitNames[] = {"Clubs", "Diamonds", "Hearts", "Spades"};
        const char* rankNames[] = {"Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten", "Jack", "Queen", "King", "Ace"};
        cout << rankNames[c.rank] << " of " << suitNames[c.suit] << endl;
    }

    static void printHand(const vector<Card> &h) {
        cout << "\nHand:\n";
        for (auto &c : h)
            printCard(c);
    }
};

// -------------------- Deck Class --------------------
class Deck {
public:
    void intDeck() {
        srand(time(NULL));
        deck.clear();
        for (int i = CLUBS; i <= SPADES; i++) {
            for (int j = TWO; j <= ACE; j++) {
                Card c;
                c.suit = (Suit)i;
                c.rank = (Rank)j;
                deck.push_back(c);
            }
        }
        shuffle();
    }

    void shuffle() {
        for (int i = 0; i < deck.size(); i++) {
            int j = i + rand() % (deck.size() - i);
            swap(deck[i], deck[j]);
        }
    }

    int getCVal(Rank r) {
        //card value
        if (r >= TWO && r <= TEN)
            return r + 2;  // TWO=0 → 2, etc.
        else if (r >= JACK && r <= KING)
            return 10;     // Face cards
        else if (r == ACE)
            return 11;     // Ace initially 11
        else
            return 0;
    }

    int check(const vector<Card> &h) {
        //checks value of hand and adjusts for aces
        int tot = 0, aceTot = 0;
        for (auto &c : h) {
            tot += getCVal(c.rank);
            if (c.rank == ACE)
                aceTot++;
        }
        while (tot > LOSS && aceTot > 0) {
            tot -= 10;
            aceTot--;
        }
        return tot;
    }
};

// -------------------- Game Class --------------------
class Game {
public:
    Deck dk;

    Game(Deck &dk) { dk.intDeck(); }

    void startGame() {
        //refreshes board state
        hand.clear();
        dealer.clear();
        dk.intDeck();
        score = score-10;
        cout << "___________________________________________________________ \n";
        cout << "Current earnings: $" << score << endl;
        cout << "\nDealing 2 cards to player...\n";
        drawCard(hand, 2, true);

        cout << "\nDealer hand:\n";
        drawCard(dealer, 1, true);
        drawCard(dealer, 1, false);
        cout << "Hidden card\n";
    }

    void drawCard(vector<Card> &h, int amt, bool show = true) {
        for (int i = 0; i < amt; i++) {
            if (deck.empty()) {
                cout << "Deck is empty!\n";
                return;
            }
            Card c = deck.back();
            h.push_back(c);
            deck.pop_back();
            if (show)
                Display::printCard(c);
        }
    }

    void printPlayerHand() {
        Display::printHand(hand);
    }

    bool stand(int tot) {
        int dealTot = dk.check(dealer);
        cout << "\nRevealed dealer hand:\n";
        Display::printHand(dealer);
        cout << "\nDealer draws...\n";

        while (dealTot < 17) {
            drawCard(dealer, 1, true);
            dealTot = dk.check(dealer);
        }

        if (dealTot > tot && dealTot <= LOSS) {
            cout << "House wins! (" << dealTot << ")\n";
            score = score-10;
            return false;
        } else if (dealTot < tot) {
            cout << "House loses! (" << dealTot << ")\n";
            score = score+20;
            return false;
        } else if (dealTot > LOSS) {
            cout << "House busts! (" << dealTot << ")\n";
            score = score+20;
            return false;
        } else {
            cout << "Push! (" << dealTot << ")\n";
            score = score+10;
            if(tot == 21) score = score -20;
            return false;
        }
    }
};

// -------------------- Main Function --------------------
int main() {
    Deck dk;
    Game game(dk);
    char ch;
    int c;
    int tot;
    game.startGame();

    cout << "Press 'd' to hit, 's' to stand, 'h' to show hand, 'p' to print controls, 'q' to quit\n";

    while (1) {
        if (_kbhit()) {
            ch = _getch();
            switch(ch){
                case 'd':{
                    game.drawCard(hand, 1, true);
                    tot = dk.check(hand);
                    if (tot == LOSS) {
                        cout << "Blackjack!\n";
                        score = score+20;
                    } else if (tot > LOSS) {
                        while (_kbhit()) _getch();
                        cout << "BUST! Play again? (y = yes): \n";
                        char key;
                        do { key = _getch(); } while (_kbhit());
                        if (key == 'y') game.startGame();
                        else break;
                    }
                    break;
                }
                case 's':{
                    tot = dk.check(hand);
                    bool checks = game.stand(tot);
                    if (!checks) {
                        while (_kbhit()) _getch();
                        cout << "Play again? (y = yes): \n";
                        char key;
                        do { key = _getch(); } while (_kbhit());
                        if (key == 'y') game.startGame();
                        else break;
                    }
                    break;
                }
                case 'p': cout << "Press 'd' to hit, 's' to stand, 'h' to show hand, 'p' to print controls, 'q' to quit\n"; break;
                case 'h':
                    game.printPlayerHand();
                    tot = dk.check(hand);
                    cout << "Hand value: " << tot << endl;
                    break;
                case 'q': return 0;
                default: break;
            
            }
        }
    }

    cout << "\nExiting...\n";
    return 0;
}
