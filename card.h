// Define the structure for a card
typedef struct Card {
    int value;
    char suit;
    bool faceDown;
    struct Card *next;
} Card;

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

void move(Card* card1, Card* card2, int i, char c) {
    // Hvis det første kort i card2 matcher værdien og kulør
    if (card2->value == i && card2->suit == c) {
        // Find slutningen af card1
        Card* endCard1 = card1;
        while (endCard1->next != NULL) {
            endCard1 = endCard1->next;
        }
        // Flyt card2 til slutningen af card1
        endCard1->next = card2;
        card2 = NULL;
        return;
    }

    // Søg i resten af card2 for at finde det matchende kort
    Card* prev = card2;
    Card* current = card2->next;
    while (current != NULL) {
        if (current->value == i && current->suit == c) {
            // Find slutningen af card1
            Card* endCard1 = card1;
            while (endCard1->next != NULL) {
                endCard1 = endCard1->next;
            }
            // Flyt current til slutningen af card1
            endCard1->next = current;
            // Opdater forbindelserne i card2
            prev->next = NULL;
            return;
        }
        prev = current;
        current = current->next;
    }
}

void convertInputToMove(Card* list[], char* input) {
    // Analyser inputstrengen
    int pile1;
    int pile2;
    int value;
    char suit;

    sscanf(input, "C%d:%d%c->C%d", &pile2, &value, &suit, &pile1);

    pile1--;
    pile2--;

    // Kald move-funktionen med de genererede parametre
    move(list[pile1], list[pile2], value, suit);
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

void removeEndCard(Card* list) {
    if (list == NULL) {
        return;  // Hvis listen er tom, skal der ikke gøres noget
    }

    if(getLength(list) == 1){
      list = NULL;
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
