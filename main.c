#define SDL_MAIN_HANDLED
#include "SDL2/SDL.h"
#include <windows.h>

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include "card.h"
#include "ui.h"
#include "load.h"
#include "command.h"
#include "gui.h"

// Function to initialize the game
void initializeGame(Card *list[], char lastCommand[], Card **deck) {

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
          strcpy(message,"OK");
          break;
        case 2:
          if(deck != NULL){
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
}

// Function to play the game
void playGame(Card *list[], char lastCommand[], Card** deck) {

    char* message = malloc(100 * sizeof(char));

    if(*deck == NULL){
      printf("deck is NULL\n");
    }

    Card* temp = copy_linked_list(*deck);
    temp = temp->next;

    // Assign cards from the shuffled deck to the 7 lists on the game board
    list[0] = temp;
    if(temp == NULL){
      printf("retuns NULL!");
    }
    list[1] = getCardByIndex(temp,1);
    list[2] = getCardByIndex(temp,7);
    list[3] = getCardByIndex(temp,14);
    list[4] = getCardByIndex(temp,22);
    list[5] = getCardByIndex(temp,31);
    list[6] = getCardByIndex(temp,41);

    list[7] = createCard(0,'C',true);
    list[8] = createCard(0,'D',true);
    list[9] = createCard(0,'H',true);
    list[10] = createCard(0,'S',true);


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

    while(loop) {
        system("cls");
        printGameState(list);
        printPile(list);
        printf("LAST Command: %s", lastCommand);
        printf("Message: %s\n", message);

        char input[100];
        printf("INPUT > ");
        fgets(input, sizeof(input), stdin);

        int status = checkCommand(input);

        if(status == 9){
          loop = false;
        }

        if(status == 10){
          message = convertInputToMove(list, input);
        }

        Card* cardB[] = {list[7],list[8],list[9],list[10]};

        moveToPile(list,cardB);
        updateEndCard(list);

        if(status != 10 && status != 9){
          printf("Message: %s\n", "COMMAND NOT FOUND");
        }
        strcpy(lastCommand, input);
    }
}

int main(int argc, char *argv[]) {

    char lastCommand[100] = "\n";
    Card *list[11];
    Card *deck = NULL;

    //createWindow();
    HANDLE thread;
    DWORD threadId;

    // Initialize shared data
    SharedData *sharedData = (SharedData*)malloc(sizeof(SharedData));

    //sharedData->lastCommand = lastCommand;

    // Create a thread to run the createWindow function
    thread = CreateThread(NULL, 0, createWindow, sharedData, 0, &threadId);
    if (thread == NULL) {
        printf("Error creating thread\n");
        return 1;
    }


    while(1){
    //  initializeGame(list, lastCommand, &deck);
      initializeGame(sharedData->list, sharedData->lastCommand,&(sharedData->deck));
      if(deck == NULL){
      //  printf("deck is NULL!!!\n");
      }
    //  playGame(list, lastCommand, &deck);
      playGame(sharedData->list, sharedData->lastCommand, &(sharedData->deck));
    }
    return 0;
}
