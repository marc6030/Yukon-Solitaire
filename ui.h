
int listLength(Card* card){
  int l = 1;
  while(card->next != NULL){
    l++;
    card = card->next;
  }
  return l;
}

void printCard(void* card){
  Card *c = (Card*)card;
  if(c == NULL){
    return;
  }
  if (c->faceDown) {
    printf("[]");
  } else {
    printf("%d%c", c->value, c->suit);
  }
}

char* getCard(void* card) {
    Card *c = (Card*)card;
    char* output = (char*)malloc(3 * sizeof(char)); // Allocate memory for the output

    if (c == NULL) {
        output[0] = '\0'; // Return an empty string if card is NULL
    } else {
        if (c->faceDown) {
            sprintf(output, "[]");
        } else {
            sprintf(output, "%d%c", c->value, c->suit);
        }
    }

    return output;
}


// Function to print the game state
void printGameState(Card* cards[]) {
    printf("C1\tC2\tC3\tC4\tC5\tC6\tC7\n\n");

    // Get the length of the longest linked list
    int longestLinkList = 0;
    int lengths[7];
    for (int i = 0; i < 7; i++) {
        lengths[i] = listLength(cards[i]);
        if (lengths[i] > longestLinkList) {
            longestLinkList = lengths[i];
        }
    }

    // Initialize double array
    char* board[7][longestLinkList];
    for (int i = 0; i < 7; i++) {
        for (int j = 0; j < longestLinkList; j++) {
            board[i][j] = ""; // Set to empty string by default
        }
    }

    // Fill double array
    for (int i = 0; i < 7; i++) {
        int j = 0;
        Card *current = cards[i];
        while (current != NULL) {
            board[i][j] = getCard(current);
            j++;
            current = current->next;
        }
    }

    // Print double array
    for (int i = 0; i < longestLinkList; i++) {
        for (int j = 0; j < 7; j++) {
            printf("%s\t", board[j][i]);
        }
        printf("\n");
    }
}



void printPile(int pile[]) {
    char suits[] = {'H', 'D', 'C', 'S'};

    printf("\n");
    for (int i = 0; i < 4; i++) {
        printf("%c%d ", suits[i], i + 1);  // Print the suit followed by the pile number
        printf("[%d]\t\t", pile[i]);       // Print the number of cards in the pile
    }
    printf("\n\n");
}
