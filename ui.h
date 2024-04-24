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
    char* output = (char*)malloc(3 * sizeof(char));

    if (c == NULL) {
        output[0] = '\0';
    } else {
        if (c->faceDown) {
            sprintf(output, "[]");
        } else {
            switch(c->value) {
                case 1:
                    sprintf(output, "A%c", c->suit);
                    break;
                case 10:
                    sprintf(output, "T%c", c->suit);
                    break;
                case 11:
                    sprintf(output, "J%c", c->suit);
                    break;
                case 12:
                    sprintf(output, "Q%c", c->suit);
                    break;
                case 13:
                    sprintf(output, "K%c", c->suit);
                    break;
                default:
                    sprintf(output, "%d%c", c->value, c->suit);
                    break;
            }
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
        if (cards[i] != NULL) {
            lengths[i] = listLength(cards[i]);
            if (lengths[i] > longestLinkList) {
                longestLinkList = lengths[i];
            }
        }
    }

    // Initialize double array
    char* board[7][longestLinkList];
    for (int i = 0; i < 7; i++) {
        for (int j = 0; j < longestLinkList; j++) {
            board[i][j] = "";
        }
    }

    // Fill double array
    for (int i = 0; i < 7; i++) {
        if (cards[i] != NULL) {
            int j = 0;
            Card *current = cards[i];
            while (current != NULL) {
                board[i][j] = getCard(current);
                j++;
                current = current->next;
            }
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

void printPile(Card* pile[]) {
    printf("\n");
    for (int i = 0; i < 4; i++) {
        printf("F%d ",i + 1);
        if(pile[i+7] == NULL){
          printf("[]\t\t");
        } else {
          printf("%d%c\t\t", getEndCard(pile[i+7])->value, getEndCard(pile[i+7])->suit);
        }
    }
    printf("\n\n");
}

void displayDeck(Card* deck){
  int i = 7;
  Card* current = deck;
  while(current != NULL){
    char* card = getCard(current);
    printf("%s\t", card);
      current = current->next;
      i--;
      if(i == 0){
        i = 7;
        printf("\n");
      }
  }
  printf("\n");
}
