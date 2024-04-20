#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include "card.h"      // Include header file for card-related functions
#include "ui.h"        // Include header file for user interface functions
#include "load.h"
#include "command.h"   // Include header file for command parsing functions


// Function prototypes
void initializeGame(Card *list[], int pile[], char lastCommand[], Card** deck);
void playGame(Card *list[], int pile[], char lastCommand[], Card** deck);
void autoMove(Card* list[], int pile[]);

// Function to initialize the game
void initializeGame(Card *list[], int pile[], char lastCommand[], Card **deck) {

    //Card *deck = NULL;
    char inp[100];
    char lastCom[100] = "";
    char message[100] = "";

    bool continueLoop = true;

    while(continueLoop){
      printf("LAST Command: %s\n", lastCom);
      printf("Message: %s\n", message);
      printf("INPUT > ");
      fgets(inp, sizeof(inp), stdin);

      // Replace newline with null character
      if (inp[strlen(inp) - 1] == '\n') {
          inp[strlen(inp) - 1] = '\0';
      }

      int status = checkCommand(inp);

      strcpy(lastCom,inp);

      switch (status) {
        case -2:
          system("cls");
          strcpy(message,"OK");
          break;
        case -1:
          strcpy(message,"ERROR: Could not read input");
          break;
        case 0:
          *deck = createDeck();
          strcpy(message,"No Input file for 'LD' command, a ordered deck is made");
          break;
        case 1:
          *deck = loadFile(inp + 3, *deck);
          //sprintf(message, "Deck Loaded from file: %s", inp + 3);
          strcpy(message,"OK");
          break;
        case 2:
          if(deck != NULL){
            //printDeck(deck);
            displayDeck(*deck);
            strcpy(message,"OK");
          } else {
            strcpy(message,"Error no deck Loaded");
          }
          break;
        case 3:
          // random shuffle
          srand(time(NULL));
          shuffleCards(deck,(rand() % 51) + 1);
          strcpy(message,"OK");
          break;
        case 4:
          //shuffle med integer
          shuffleCards(deck,inp[3] - '0');
          strcpy(message,"OK");
          break;
        case 5:
          //shuffle med integer
          shuffleCards(deck,(inp[3] - '0') * 10 + (inp[4] - '0'));
          strcpy(message,"OK");
          break;
        case 6:
          SR(deck);
          break;
        case 7:
          continueLoop = false;
          strcpy(message,"OK");
          break;
        case 8:
          save_deck_to_file(*deck,inp + 2);
          strcpy(message,"OK");
          break;
        default:
          strcpy(message,"ERROR: Could not read input");
          break;
      }
    }

/* deal cards
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
    */
}

// Function to play the game
void playGame(Card *list[], int pile[], char lastCommand[], Card** deck) {

    if(*deck == NULL){
      printf("deck is NULL\n");
    }

    Card* temp = copy_linked_list(*deck);

    // Assign cards from the shuffled deck to the 7 lists on the game board
    list[0] = temp;
    if(temp == NULL){
      printf("retuns NULL!");
    }
    list[1] = getCardByIndex(temp,1);
    printf("HER2"); // JEG ER NÅET HER TIL!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    list[2] = getCardByIndex(temp,7);
    list[3] = getCardByIndex(temp,14);
    list[4] = getCardByIndex(temp,22);
    list[5] = getCardByIndex(temp,31);
    list[6] = getCardByIndex(temp,41);


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

    bool loop = true;

    while(1) {

        system("cls");  // Clear the console screen
        printGameState(list);  // Print the current game state
        printPile(pile);        // Print the number of cards in the piles
        printf("LAST Command: %s", lastCommand);  // Print the last command entered by the player
        printf("Message: %s\n", "OK");            // Print a message indicating game status

        char input[100];       // Variable to store player input
        printf("INPUT > ");    // Prompt the player to enter a command
        fgets(input, sizeof(input), stdin);  // Read player input from the console
/*
        if(input[0] == 'Q' && input[1] == '\n'){
          loop = 0;
        }*/
      //  int status = checkCommand(input);   // Check and process the player's command
        strcpy(lastCommand, input);  // Store the player's command as the last command entered

        convertInputToMove(list, input);  // Convert player's input to a move action
        moveToPile(list,pile);   // Moves end card to pile
        updateEndCard(list);              // Update the end cards in each list
    }
}



int main() {
    char lastCommand[100] = "\n";  // Variable to store the last command entered by the player
    Card *list[7];                 // Array to store pointers to 7 card lists
    int pile[4] = {0};             // Array to store the number of cards in 4 card piles
    Card *deck = NULL;


    while(1){
      initializeGame(list, pile, lastCommand, &deck); // Initialize the game
      if(deck == NULL){
        printf("deck is NULL!!!\n");
      }
      playGame(list, pile, lastCommand, &deck);        // Start playing the game
    }

    return 0;  // Return 0 to indicate successful program execution
}
