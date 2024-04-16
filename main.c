#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include "card.h"      // Include header file for card-related functions
#include "ui.h"        // Include header file for user interface functions
#include "command.h"   // Include header file for command parsing functions

// Function prototypes
void initializeGame(Card *list[], int pile[], char lastCommand[]);
void playGame(Card *list[], int pile[], char lastCommand[]);
void autoMove(Card* list[], int pile[]);

int main() {
    char lastCommand[100] = "\n";  // Variable to store the last command entered by the player
    Card *list[7];                 // Array to store pointers to 7 card lists
    int pile[4] = {0};             // Array to store the number of cards in 4 card piles

    initializeGame(list, pile, lastCommand);  // Initialize the game
    playGame(list, pile, lastCommand);        // Start playing the game

    return 0;  // Return 0 to indicate successful program execution
}

// Function to initialize the game
void initializeGame(Card *list[], int pile[], char lastCommand[]) {
    // Create a new deck of cards and shuffle it
    Card *deck = createDeck();
    shuffleCards(deck);

    // Assign cards from the shuffled deck to the 7 lists on the game board
    list[0] = deck;
    list[1] = getCardByIndex(deck,1);
    list[2] = getCardByIndex(deck,7);
    list[3] = getCardByIndex(deck,14);
    list[4] = getCardByIndex(deck,22);
    list[5] = getCardByIndex(deck,31);
    list[6] = getCardByIndex(deck,41);

    // Shortens the length of each linked list
    setCardAsEndCard(getCardByIndex(list[0],0));
    setCardAsEndCard(getCardByIndex(list[1],5));
    setCardAsEndCard(getCardByIndex(list[2],6));
    setCardAsEndCard(getCardByIndex(list[3],7));
    setCardAsEndCard(getCardByIndex(list[4],8));
    setCardAsEndCard(getCardByIndex(list[5],9));

    // Toggle the face-down status of certain cards in each list
    for(int j = 1;j<7;j++){
        for(int i = j;i<7;i++){
            cardToggleFacedown(getCardByIndex(list[i],j-1));
        }
    }
}

// Function to play the game
void playGame(Card *list[], int pile[], char lastCommand[]) {
    while(true) {
        system("cls");  // Clear the console screen
        printGameState(list);  // Print the current game state
        printPile(pile);        // Print the number of cards in the piles
        printf("LAST Command: %s", lastCommand);  // Print the last command entered by the player
        printf("Message: %s\n", "OK");            // Print a message indicating game status

        char input[100];       // Variable to store player input
        printf("INPUT > ");    // Prompt the player to enter a command
        fgets(input, sizeof(input), stdin);  // Read player input from the console
        checkCommand(input);   // Check and process the player's command
        strcpy(lastCommand, input);  // Store the player's command as the last command entered

        convertInputToMove(list, input);  // Convert player's input to a move action
        moveToPile(list,pile);   // Moves end card to pile
        updateEndCard(list);              // Update the end cards in each list
    }
}
