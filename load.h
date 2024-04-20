// check if file has 52 lines
int checkFileLines(const char *filename, int lines) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        return -1; // Return -1 if file couldn't be opened
    }

    int lineCount = 0;
    char buffer[1024]; // Buffer to hold each line
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        lineCount++;
    }

    fclose(file);

    if (lineCount == lines) {
        return 1; // Return 1 if file has 52 lines
    } else {
        return 0; // Return 0 if file doesn't have 52 lines
    }
}



bool isValidCard(char firstChar) {
    switch (firstChar) {
        case 'A':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
        case 'T':
        case 'J':
        case 'Q':
        case 'K':
            return true; // Return true if the character is one of the specified cards
        default:
            return false; // Return false otherwise
    }
}

// checks valid first char in each line
int checkFirstCard(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        return -1; // Return -1 if file couldn't be opened
    }

    char buffer[1024]; // Buffer to hold each line
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        if (!isValidCard(buffer[0])) {
            fclose(file);
            return 0; // Return 0 if the first character in any line is not a valid card
        }
    }

    fclose(file);

    return 1; // Return 1 if the first character in each line is a valid card
}

bool isValidSuit(char secondChar) {
    switch (secondChar) {
        case 'S':
        case 'D':
        case 'H':
        case 'C':
            return true; // Return true if the character is one of the specified suits
        default:
            return false; // Return false otherwise
    }
}

int checkSecondSuit(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        return -1; // Return -1 if file couldn't be opened
    }

    char buffer[1024]; // Buffer to hold each line
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        if (!isValidSuit(buffer[1])) {
            fclose(file);
            return 0; // Return 0 if the second character in any line is not a valid suit
        }
    }

    fclose(file);

    return 1; // Return 1 if the second character in each line is a valid suit
}

int checkDuplicates(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        return -1; // Return -1 if file couldn't be opened
    }

    bool cardSuits[13][4] = {false}; // Array to keep track of seen combinations
    char buffer[1024]; // Buffer to hold each line
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        char firstChar = buffer[0];
        char secondChar = buffer[1];

        if (!isValidCard(firstChar) || !isValidSuit(secondChar)) {
            fclose(file);
            return 0; // Return 0 if the combination is invalid
        }

        int cardIndex = firstChar >= '2' && firstChar <= '9' ? firstChar - '2' : (firstChar == 'T' ? 8 : (firstChar == 'J' ? 9 : (firstChar == 'Q' ? 10 : (firstChar == 'K' ? 11 : 12))));
        int suitIndex = secondChar == 'S' ? 0 : (secondChar == 'D' ? 1 : (secondChar == 'H' ? 2 : 3));

        if (cardSuits[cardIndex][suitIndex]) {
            fclose(file);
            return 0; // Return 0 if the combination has been seen before
        }

        cardSuits[cardIndex][suitIndex] = true;
    }

    fclose(file);

    return 1; // Return 1 if all combinations are unique
}


#define MAX_LINES 52
#define MAX_LINE_LENGTH 256

// Function to read lines from a file into a char* array
char **readLinesFromFile(const char *filename, int *numLines) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        return NULL;
    }

    char **lines = (char **)malloc(MAX_LINES * sizeof(char *));
    if (lines == NULL) {
        fclose(file);
        perror("Memory allocation failed");
        return NULL;
    }

    char line[MAX_LINE_LENGTH];
    int count = 0;
    while (fgets(line, sizeof(line), file) != NULL) {
        // Allocate memory for the line and copy it
        lines[count] = strdup(line);
        if (lines[count] == NULL) {
            fclose(file);
            perror("Memory allocation failed");
            // Free previously allocated memory
            for (int i = 0; i < count; i++) {
                free(lines[i]);
            }
            free(lines);
            return NULL;
        }
        count++;
        // Check if the number of lines exceeds MAX_LINES
        if (count >= MAX_LINES) {
            break;
        }
    }

    *numLines = count;
    fclose(file);
    return lines;
}

Card* createDeckFromLines(char **lines, int numLines) {
    if (numLines <= 0) {
        printf("Invalid number of lines.\n");
        return NULL;
    }

    // Create the first card
    Card *deck = createCardFromString(lines[0]);
    Card *prev = deck;

    // Create cards from subsequent lines and link them together
    for (int i = 1; i < numLines; i++) {
        Card *current = createCardFromString(lines[i]);
        prev->next = current;
        prev = current;
    }

    return deck;
}


Card* loadFile(const char *filename, Card* deck){
  //  printf("Checking file: %s\n", filename);
    if (!access(filename, F_OK)) {
    } else {
      perror("Error checking file existence");
      return 0;
    }

  if(!checkFileLines(filename,52)){
    printf("File does not have 52 lines\n");
    return 0; // not 52 lines
  }
  if(!checkFirstCard(filename)){
    printf("some first carachter in file is not valid\n");
    return 0; // some lines first character is not valid
  }
  if(!checkSecondSuit(filename)){
    printf("some second carachter in file is not valid\n");
    return 0; // some lindes second character is not valid
  }
  if(!checkDuplicates(filename)){
    printf("file has duplicates\n");
    return 0; // some lines has duplicates
  }
  int numberoflines;
  char** lines = readLinesFromFile(filename,&numberoflines);
  return createDeckFromLines(lines,numberoflines);
  //printDeck(deck);
}
