// Define the structure for a card
typedef struct Card {
    int value;
    char suit;
    bool faceDown;
    struct Card *next;
} Card;

// Function to check if a card exists in a linked list
bool cardExists(Card* head, int value, char suit) {
    // Check if the linked list is empty
    if (head == NULL) {
        return false;
    }

    Card* current = head;
    while (current != NULL) {
        if (current->value == value && current->suit == suit) {
            return true; // Card exists in the linked list
        }
        current = current->next;
    }
    return false; // Card does not exist in the linked list
}

// Function to create a new card
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
        return NULL; // If the original list is empty, return NULL
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

    // Open the file for writing
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("Error: Unable to create file '%s' for writing.\n", filename);
        return;
    }

    // Traverse the deck and write each card to the file
    Card *current = deck;
    while (current != NULL) {
        // Write card to the file in the format: <rank><suit>
        fprintf(file, "%d%c\n", current->value, current->suit);
        current = current->next;
    }

    // Close the file
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
        // Invalid input: one or more pointers are NULL
        printf("Error: Invalid input.\n");
        return;
    }

    // Update pointers to insert new_card between prev_card and next_card
    prev_card->next = new_card;
    new_card->next = next_card;
}

void SR(Card **unshuffled_pile) {
    Card *shuffled_pile = NULL;
    Card *current = *unshuffled_pile;

    while (current != NULL) {
        // Randomly select a card to move from unshuffled pile to shuffled pile
        int r = rand() % get_list_length(current);

        // Traverse to the random position in the unshuffled pile
        Card *prev = NULL;
        for (int i = 0; i < r; i++) {
            prev = current;
            current = current->next;
        }

        // Move the selected card from unshuffled pile to shuffled pile
        if (prev != NULL) {
            prev->next = current->next;
        } else {
            *unshuffled_pile = current->next;
        }
        current->next = shuffled_pile;
        shuffled_pile = current;

        // Reset current pointer to the start of unshuffled pile for next iteration
        current = *unshuffled_pile;
    }

    // Update the unshuffled pile to point to the shuffled pile
    *unshuffled_pile = shuffled_pile;
}


void reverseLinkedList(Card **head) {
    Card *prev = NULL;
    Card *current = *head;
    Card *next = NULL;

    while (current != NULL) {
        next = current->next; // Store the next node
        current->next = prev; // Reverse the pointer of the current node

        // Move pointers one position ahead
        prev = current;
        current = next;
    }

    *head = prev; // Update the head to point to the new first node (previously the last node)
}


// Function to link a card to another card in the linked list
void linkCards(Card *card, Card *childCard) {
    if (card == NULL || childCard == NULL) {
        printf("Error: Cannot link cards");
        return;
    }
    card->next = childCard;
}

// Function to get card by index
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

// Function to create a deck of cards
Card* createDeck() {
    Card *head = NULL;
    Card *current = NULL;
    char suits[] = {'H', 'D', 'C', 'S'}; // Hearts, Diamonds, Clubs, Spades

    // Create cards for each suit and value
    for (int value = 1; value <= 13; ++value) {
        for (int suitIndex = 0; suitIndex < 4; ++suitIndex) {
            char suit = suits[suitIndex];
            bool faceDown = false; // Assuming all cards are initially face up
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

// Function to get the length of the linked list
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
        return;  // Hvis listen er tom, skal der ikke gøres noget
    }

    if(getLength(list) == 1){
      return;
    }

    // Find det næstsidste kort i listen
    Card* secondLast = list;
    while (secondLast->next->next != NULL) {
        secondLast = secondLast->next;
    }

    // Gem det sidste kort
    Card* lastCard = secondLast->next;

    // Fjern forbindelsen til det sidste kort
    secondLast->next = NULL;
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

      // Find the right element in the list
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

      while(currentFrom != NULL && currentFrom->next != NULL && (currentFrom->next->value != value && currentFrom->next->suit != suit)){
        currentFrom = currentFrom->next;
      }

      currentTo = list[iTo];
      if(currentTo == NULL){
        list[iTo] = currentFrom->next;
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


      // Find last element in linked list
      currentFrom = list[iFrom];
      while(currentFrom != NULL && currentFrom->next != NULL){
        currentFrom = currentFrom->next;
      }


      // Find last element in linked list
      currentTo = list[iTo];
      if(currentTo == NULL){
        list[iTo] = currentFrom;
      } else {
        while(currentTo != NULL && currentTo->next != NULL){
            currentTo = currentTo->next;
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

// Function to get the node at a specific index in the linked list
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

// Function to swap the data of two nodes
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

// Function to shuffle the linked list of cards
/*
void shuffleCards(Card *head) {
    int length = getLength(head);
    srand(time(NULL));

    for (int i = 0; i < length; i++) {
        int j = i + rand() % (length - i);
        Card *node1 = getNodeAtIndex(head, i);
        Card *node2 = getNodeAtIndex(head, j);
        swap(node1, node2);
    }
}
*/

void splitDeckAtPosition(Card *deck, Card **pile1, Card **pile2, int splitPosition) {
    if (deck == NULL) {
        *pile1 = NULL;
        *pile2 = NULL;
        return;
    }

    Card *current = deck;
    int count = 1;

    // Traverse the deck until the specified split position
    while (current != NULL && count < splitPosition) {
        current = current->next;
        count++;
    }

    // If current is NULL, it means the split position is beyond the end of the deck
    if (current == NULL) {
        *pile1 = deck;
        *pile2 = NULL;
    } else {
        *pile1 = deck;
        *pile2 = current->next;
        current->next = NULL; // Split the deck by setting the next of the current card to NULL
    }
}


void shuffleCards(Card **deck, int splitPosition) {
    Card *pile1 = NULL, *pile2 = NULL;
    splitDeckAtPosition(*deck, &pile1, &pile2, splitPosition); // Split the deck into two piles at the specified position

    *deck = NULL; // Empty the original deck

    while (pile1 != NULL && pile2 != NULL) {
        // Take the top card from each pile and place it into the shuffled pile
        Card *temp1 = pile1->next;
        Card *temp2 = pile2->next;

        pile1->next = *deck;
        *deck = pile1;
        pile1 = temp1;

        pile2->next = *deck;
        *deck = pile2;
        pile2 = temp2;
    }

    // Place the remaining cards from the non-empty pile at the bottom of the shuffled pile
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
            // Handle unexpected cases
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


// Function to create a card from a string
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

    // Assuming all cards are face up when created from a string
    return createCard(value, suit, false);
}

// Function to print the deck of cards
void printDeck(Card *deck) {
    Card *current = deck;
    while (current != NULL) {
        printf("Value: %d, Suit: %c, Face Down: %s\n", current->value, current->suit, current->faceDown ? "true" : "false");
        current = current->next;
    }
}
