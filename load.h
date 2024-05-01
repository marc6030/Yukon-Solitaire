// check if file has 52 lines
int checkFileLines(const char *filename, int lines) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        return -1;
    }

    int lineCount = 0;
    char buffer[1024];
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        lineCount++;
    }

    fclose(file);

    if (lineCount == lines) {
        return 1;
    } else {
        return 0;
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
            return true;
        default:
            return false;
    }
}

// checks valid first char in each line
int checkFirstCard(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        return -1;
    }

    char buffer[1024];
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        if (!isValidCard(buffer[0])) {
            fclose(file);
            return 0;
        }
    }

    fclose(file);

    return 1;
}

bool isValidSuit(char secondChar) {
    switch (secondChar) {
        case 'S':
        case 'D':
        case 'H':
        case 'C':
            return true;
        default:
            return false;
    }
}

int checkSecondSuit(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        return -1;
    }

    char buffer[1024];
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        if (!isValidSuit(buffer[1])) {
            fclose(file);
            return 0;
        }
    }

    fclose(file);

    return 1;
}

int checkDuplicates(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        return -1;
    }

    bool cardSuits[13][4] = {false};
    char buffer[1024];
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        char firstChar = buffer[0];
        char secondChar = buffer[1];

        if (!isValidCard(firstChar) || !isValidSuit(secondChar)) {
            fclose(file);
            return 0;
        }

        int cardIndex = firstChar >= '2' && firstChar <= '9' ? firstChar - '2' : (firstChar == 'T' ? 8 : (firstChar == 'J' ? 9 : (firstChar == 'Q' ? 10 : (firstChar == 'K' ? 11 : 12))));
        int suitIndex = secondChar == 'S' ? 0 : (secondChar == 'D' ? 1 : (secondChar == 'H' ? 2 : 3));

        if (cardSuits[cardIndex][suitIndex]) {
            fclose(file);
            return 0;
        }

        cardSuits[cardIndex][suitIndex] = true;
    }

    fclose(file);

    return 1;
}

// Function to read lines from a file into a char* array
char **readLinesFromFile(const char *filename, int *numLines) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        return NULL;
    }

    char **lines = (char **)malloc(52 * sizeof(char *));
    if (lines == NULL) {
        fclose(file);
        perror("Memory allocation failed");
        return NULL;
    }

    char line[256];
    int count = 0;
    while (fgets(line, sizeof(line), file) != NULL) {
        lines[count] = strdup(line);
        if (lines[count] == NULL) {
            fclose(file);
            perror("Memory allocation failed");
            for (int i = 0; i < count; i++) {
                free(lines[i]);
            }
            free(lines);
            return NULL;
        }
        count++;
        if (count >= 52) {
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
    if (!access(filename, F_OK)) {
    } else {
      perror("Error checking file existence");
      return 0;
    }

  if(!checkFileLines(filename,52)){
    printf("File does not have 52 lines\n");
    return 0;
  }
  if(!checkFirstCard(filename)){
    printf("some first carachter in file is not valid\n");
    return 0;
  }
  if(!checkSecondSuit(filename)){
    printf("some second carachter in file is not valid\n");
    return 0;
  }
  if(!checkDuplicates(filename)){
    printf("file has duplicates\n");
    return 0;
  }
  int numberoflines;
  char** lines = readLinesFromFile(filename,&numberoflines);
  return createDeckFromLines(lines,numberoflines);
}
