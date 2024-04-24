// Card structure
typedef struct Card {
    int value;
    char suit;
    bool faceDown;
    struct Card *next;
} Card;

bool cardExists(Card* head, int value, char suit) {
    if (head == NULL) {
        return false;
    }
    Card* current = head;
    while (current != NULL) {
        if (current->value == value && current->suit == suit) {
            return true;
        }
        current = current->next;
    }
    return false;
}

Card* createCard(int value, char suit, bool faceDown) {
    Card *newCard = (Card*)malloc(sizeof(Card));
    if (newCard == NULL) {
        printf("Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    newCard->value = value;
    newCard->suit = suit;
    newCard->faceDown = faceDown;
    newCard->next = NULL;
    return newCard;
}

Card* copy_linked_list(Card *head) {
    if (head == NULL) {
        return NULL;
    }

    Card *currentOld = head;
    Card *newHead = createCard(currentOld->value,currentOld->suit,currentOld->faceDown);
    Card *currentNew = newHead;

    while(currentOld != NULL){
        currentNew->next = createCard(currentOld->value,currentOld->suit,currentOld->faceDown);
        currentOld = currentOld->next;
        currentNew = currentNew->next;
    }
    return newHead;
}


void save_deck_to_file(Card *deck, char *filenam) {
    char* filename;
    filename = filenam;

    if(filename[0] == '\0'){
      filename = "cards.txt";
    } else {
      filename = filenam + 1;
    }

    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("Error: Unable to create file '%s' for writing.\n", filename);
        return;
    }

    Card *current = deck;
    while (current != NULL) {
        fprintf(file, "%d%c\n", current->value, current->suit);
        current = current->next;
    }
    fclose(file);
}

int get_list_length(Card *head) {
    int length = 0;
    Card *current = head;

    while (current != NULL) {
        length++;
        current = current->next;
    }

    return length;
}

void insert_between(Card *prev_card, Card *new_card, Card *next_card) {
    if (prev_card == NULL || next_card == NULL || new_card == NULL) {
        printf("Error: Invalid input.\n");
        return;
    }
    prev_card->next = new_card;
    new_card->next = next_card;
}

void SR(Card **unshuffled_pile) {
    Card *shuffled_pile = NULL;
    Card *current = *unshuffled_pile;

    while (current != NULL) {
        int r = rand() % get_list_length(current);

        Card *prev = NULL;
        for (int i = 0; i < r; i++) {
            prev = current;
            current = current->next;
        }
        if (prev != NULL) {
            prev->next = current->next;
        } else {
            *unshuffled_pile = current->next;
        }
        current->next = shuffled_pile;
        shuffled_pile = current;
        current = *unshuffled_pile;
    }
    *unshuffled_pile = shuffled_pile;
}

void reverseLinkedList(Card **head) {
    Card *prev = NULL;
    Card *current = *head;
    Card *next = NULL;

    while (current != NULL) {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    *head = prev;
}

void linkCards(Card *card, Card *childCard) {
    if (card == NULL || childCard == NULL) {
        printf("Error: Cannot link cards");
        return;
    }
    card->next = childCard;
}

Card* getCardByIndex(Card* card, int index){
  Card* current = card;
  while(index > 0){
    index--;
    current = current->next;
  }
  return current;
}

void setCardAsEndCard(Card* card){
  card->next = NULL;
}

void cardToggleFacedown(Card* card){
  card->faceDown = !card->faceDown;
}

Card* createDeck() {
    Card *head = NULL;
    Card *current = NULL;
    char suits[] = {'H', 'D', 'C', 'S'};

    for (int value = 1; value <= 13; ++value) {
        for (int suitIndex = 0; suitIndex < 4; ++suitIndex) {
            char suit = suits[suitIndex];
            bool faceDown = false;
            Card *newCard = createCard(value, suit, faceDown);
            if (newCard != NULL) {
                if (head == NULL) {
                    head = newCard;
                    current = head;
                } else {
                    current->next = newCard;
                    current = current->next;
                }
            }
        }
    }

    return head;
}

Card* getEndCard(Card* card){
  Card* current = card;
  while(current->next != NULL){
    current = current->next;
  }
  return current;
}

int getLength(Card *head) {
    int length = 0;
    while (head != NULL) {
        length++;
        head = head->next;
    }
    return length;
}

void removeEndCard(Card* list) {
    if (list == NULL) {
        return;
    }
    if(getLength(list) == 1){
      return;
    }
    Card* secondLast = list;
    while (secondLast->next->next != NULL) {
        secondLast = secondLast->next;
    }
    Card* lastCard = secondLast->next;
    secondLast->next = NULL;
}

bool validMove(Card* from, Card* to){
    return to->value == from->value+1 && to->suit != from->suit;
}

char* convertInputToMove(Card* list[], char* input){

    char* message = malloc(100 * sizeof(char));

    Card* currentFrom;
    Card* currentTo;

    int length = strlen(input);
    char cFrom, cTo, suit;
    int iFrom, iTo, value;

    if(length == 10){
      sscanf(input,"%c%d:%d%c->%c%d",&cFrom,&iFrom,&value,&suit,&cTo,&iTo);
      if(cFrom == 'F'){
        iFrom += 7;
      }
      if(cTo == 'F'){
        iTo += 7;
      }
      iFrom--;
      iTo--;

      bool existsInList = false;
      currentFrom = list[iFrom];
      while(currentFrom != NULL){
        if(currentFrom->value == value && currentFrom->suit == suit){
          existsInList = true;
        }
        currentFrom = currentFrom->next;
      }
      if(!existsInList){
        message = "Error card does not exist in pile";
        return message;
      }


      currentFrom = list[iFrom];

      if(currentFrom == NULL){
        message = "Error FROM list is empty";
        return message;
      }

      while(currentFrom != NULL && currentFrom->next != NULL){
      if(currentFrom->next->value == value && currentFrom->next->suit == suit) {
          break;
      }
      currentFrom = currentFrom->next;
  }


      currentTo = list[iTo];
      if(currentTo == NULL){
        list[iTo] = currentFrom->next;
        currentFrom->next = NULL;
      } else {
        while(currentTo->next != NULL){
          currentTo = currentTo->next;
        }

        currentTo->next = currentFrom->next;
        currentFrom->next = NULL;
      }

      if(list[iFrom]->value == value && list[iFrom]->suit == suit){
        currentTo->next = list[iFrom];
        list[iFrom] = NULL;
        return message;
      }

    }

    if(length == 7){
      sscanf(input,"%c%d->%c%d",&cFrom,&iFrom,&cTo,&iTo);
      if(cFrom == 'F'){
        iFrom += 7;
      }
      if(cTo == 'F'){
        iTo += 7;
      }
      iFrom--;
      iTo--;

      sprintf(message, "cFrom: %c, cTo: %c, suit: %c, iFrom: %d, iTo: %d, value: %d", cFrom, cTo, suit, iFrom, iTo, value);

      currentFrom = list[iFrom];

      if(currentFrom == NULL){
        message = "From Pile cannot be empty";
        return message;
      }

      while(currentFrom != NULL && currentFrom->next != NULL){
        currentFrom = currentFrom->next;
      }

      currentTo = list[iTo];
      if(currentTo == NULL){
        list[iTo] = currentFrom;
      } else {
        while(currentTo != NULL && currentTo->next != NULL){
            currentTo = currentTo->next;
        }
        if(!validMove(currentFrom,currentTo)){
          message = "invalid move";
          return message;
        }
        currentTo->next = currentFrom;
      }

      if(currentFrom == list[iFrom]){
        list[iFrom] = NULL;
      } else {
        removeEndCard(list[iFrom]);
      }
    }
    return message;
}

Card* getNodeAtIndex(Card *head, int index) {
    int count = 0;
    while (head != NULL) {
        if (count == index)
            return head;
        count++;
        head = head->next;
    }
    return NULL;
}

void swap(Card *node1, Card *node2) {
    int temp_value = node1->value;
    char temp_suit = node1->suit;
    bool temp_faceDown = node1->faceDown;

    node1->value = node2->value;
    node1->suit = node2->suit;
    node1->faceDown = node2->faceDown;

    node2->value = temp_value;
    node2->suit = temp_suit;
    node2->faceDown = temp_faceDown;
}

void splitDeckAtPosition(Card *deck, Card **pile1, Card **pile2, int splitPosition) {
    if (deck == NULL) {
        *pile1 = NULL;
        *pile2 = NULL;
        return;
    }

    Card *current = deck;
    int count = 1;

    while (current != NULL && count < splitPosition) {
        current = current->next;
        count++;
    }

    if (current == NULL) {
        *pile1 = deck;
        *pile2 = NULL;
    } else {
        *pile1 = deck;
        *pile2 = current->next;
        current->next = NULL;
    }
}


void shuffleCards(Card **deck, int splitPosition) {
    Card *pile1 = NULL, *pile2 = NULL;
    splitDeckAtPosition(*deck, &pile1, &pile2, splitPosition);

    *deck = NULL;

    while (pile1 != NULL && pile2 != NULL) {
        Card *temp1 = pile1->next;
        Card *temp2 = pile2->next;

        pile1->next = *deck;
        *deck = pile1;
        pile1 = temp1;

        pile2->next = *deck;
        *deck = pile2;
        pile2 = temp2;
    }

    if (pile1 != NULL) {
        while (pile1 != NULL) {
            Card *temp = pile1->next;
            pile1->next = *deck;
            *deck = pile1;
            pile1 = temp;
        }
    } else {
        while (pile2 != NULL) {
            Card *temp = pile2->next;
            pile2->next = *deck;
            *deck = pile2;
            pile2 = temp;
        }
    }
    reverseLinkedList(deck);
}

void updateEndCard(Card* list[]){
  for (int i = 0; i < 7; i++) {
    Card* current = getEndCard(list[i]);
    if(current == NULL){
      continue;
    }
    if(current->faceDown == true){
      current->faceDown = false;
    }
  }
}

void setElementToNull(Card *list[], int index) {
    if (index >= 0 && index < 7) {
        list[index] = NULL;
    } else {
        printf("Invalid index. Index must be between 0 and 6 inclusive.\n");
    }
}

void moveToPile(Card* list[], int pile[]){
  for(int i = 0;i<4;i++){
    char c;
    switch(i) {
        case 0:
            c = 'H';
            break;
        case 1:
            c = 'D';
            break;
        case 2:
            c = 'C';
            break;
        case 3:
            c = 'S';
            break;
        default:
            break;
    }
    for(int j = 0;j<7;j++){
      if(getEndCard(list[j])->suit == c && pile[i] + 1 == getEndCard(list[j])->value){
        if(getLength(list[j]) == 1){
          setElementToNull(list,j);
        }
        pile[i]++;
        removeEndCard(list[j]);
      }
    }
  }
}

Card* createCardFromString(const char *cardString) {
    if (cardString == NULL || cardString[0] == '\0' || cardString[1] == '\0') {
        printf("Invalid card string\n");
        return NULL;
    }

    int value;
    char suit;
    switch (cardString[0]) {
        case 'A':
            value = 1;
            break;
        case '2': case '3': case '4': case '5': case '6': case '7': case '8': case '9':
            value = cardString[0] - '0';
            break;
        case 'T':
            value = 10;
            break;
        case 'J':
            value = 11;
            break;
        case 'Q':
            value = 12;
            break;
        case 'K':
            value = 13;
            break;
        default:
            printf("Invalid card value\n");
            return NULL;
    }

    switch (cardString[1]) {
        case 'S': case 'D': case 'H': case 'C':
            suit = cardString[1];
            break;
        default:
            printf("Invalid card suit\n");
            return NULL;
    }

    return createCard(value, suit, false);
}
