int checkCommand(char command[]) {
    // Check for exit command (QQ)
    if (command[0] == 'Q' && command[1] == 'Q') {
        exit(0);
    }

    // Check for empty command
    if (command[0] == '\0') {
        return -2;
    }

    // Check for LD command
    if (command[0] == 'L' && command[1] == 'D') {
        if (command[2] == '\0') {
            return 0;
        }
        return 1;
    }

    // Check for SW command
    if (command[0] == 'S' && command[1] == 'W') {
        return 2;
    }

    // Check for SL command
    if (command[0] == 'S' && command[1] == 'I' && command[2] == '\0') {
        return 3;
    }

    // Check for SI command without space
    if (command[0] == 'S' && command[1] == 'I' && command[2] == ' ' && command[3] >= '0' && command[3] <= '9' && command[4] == '\0') {
        return 4;
    }

    // Check for SI command with space
    if (command[0] == 'S' && command[1] == 'I' && command[2] == ' ' && command[3] >= '0' && command[4] >= '0' && command[4] <= '9' && command[5] == '\0') {
        return 5;
    }

    // Check for SR command
    if (command[0] == 'S' && command[1] == 'R' && command[2] == '\0') {
        return 6;
    }

    // Check for SD command
    if (command[0] == 'S' && command[1] == 'D') {
        return 8;
    }

    // Check for P command
    if (command[0] == 'P' && command[1] == '\0') {
        return 7;
    }

    // Check for Q command with newline
    if (command[0] == 'Q' && command[1] == '\n') {
        return 9;
    }

    // Check for C command with specific format
    if (command[2] == ':' && command[5] == '-' && command[6] == '>' && command[9] == '\n') {
        return 10;
    }

    // Check for C command with specific format
    if (command[2] == '-' && command[3] == '>' && command[6] == '\n') {
        return 10;
    }

    // Default case for unrecognized commands
    return -1;
}
