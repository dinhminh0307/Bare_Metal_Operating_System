#include "./cli.h"

char commandLine[COMMAND_LINE_SIZE]; // Fixed-size array for the command line
int commandIndex = 0; // Index to keep track of the current position in commandLine
char commandBuffer[COMMAND_LINE_SIZE][COMMAND_LINE_SIZE] = {0};
volatile int numberOfPlusPresses = 0;
volatile int numberOfMinusPresses = 0;
char *textColor = DIM_YELLOW_COLOR;
char *backGroundColor = BLACK_COLOR;

// Utility function to reset the commandLine buffer
void resetCommandLine() {
    for (int i = 0; i < COMMAND_LINE_SIZE; i++) {
        commandLine[i] = '\0';
    }
    commandIndex = 0;
}

void resetBuffer() {
    for (int i = 0; i < COMMAND_LINE_SIZE; i++) {
        commandLine[i] = '\0';
    }
}

void debugTool() {
    char *c = "123456";
    uart_puts(getLength(c));
}

void printOS(void) {
    uart_puts("\nC:/DELL/Minh_OS>");
}

void printWelcomeMsg(char *msg) {
    uart_puts(msg);
    printOS();
}

void printClearInfor(void) {
    uart_puts("+----+--------------+---------------------------------------------------------+\n");
    uart_puts("| 2  | clear        | - Clear screen (in our terminal it will scroll down to  |\n");
    uart_puts("|    |              |   current position of the cursor).                      |\n");
    uart_puts("|    |              | - Example: MyOS> clear                                  |\n");
    uart_puts("+----+--------------+---------------------------------------------------------+\n");
     printOS();
}

void printSetColorCommand(void) {
    uart_puts("+----+--------------+---------------------------------------------------------+\n");
    uart_puts("| 3  | setcolor     | - Set text color, and/or background color of the        |\n");
    uart_puts("|    |              |   console to one of the following colors: BLACK, RED,   |\n");
    uart_puts("|    |              |   GREEN, YELLOW, BLUE, PURPLE, CYAN, WHITE              |\n");
    uart_puts("|    |              | - Examples:                                             |\n");
    uart_puts("|    |              |   MyOS> setcolor -t yellow                              |\n");
    uart_puts("|    |              |   MyOS> setcolor -b yellow -t white                     |\n");
    uart_puts("+----+--------------+---------------------------------------------------------+\n");
     printOS();
}

void printShowCommand(void) {
    uart_puts(backGroundColor);  // Set background color
    uart_puts(textColor);        // Set text color
    uart_puts("+----+--------------+---------------------------------------------------------+\n");
    uart_puts(RESET_COLOR);
    uart_puts(backGroundColor);  // Set background colorRESET_COLOR
    uart_puts(textColor);        // Set text colorRESET_COLOR
    uart_puts("| 4  | showinfo     | - Show board revision and board MAC address in correct  |\n"RESET_COLOR);
    uart_puts(backGroundColor);  // Set background colorRESET_COLOR
    uart_puts(textColor);        // Set text colorRESET_COLOR
    uart_puts("|    |              |   format/meaningful information                         |\n"RESET_COLOR);
    uart_puts(backGroundColor);  // Set background colorRESET_COLOR
    uart_puts(textColor);        // Set text colorRESET_COLOR
    uart_puts("|    |              | - Example: MyOS> showinfo                               |\n"RESET_COLOR);
    uart_puts(backGroundColor);  // Set background colorRESET_COLOR
    uart_puts(textColor);        // Set text colorRESET_COLOR
    uart_puts("+----+--------------+---------------------------------------------------------+\n"RESET_COLOR);
    
    printOS();
}

void printMenu() {
    uart_puts(backGroundColor);  // Set background color
    uart_puts(textColor);        // Set text color
    uart_puts("+----+--------------+---------------------------------------------------------+\n"RESET_COLOR);
    uart_puts(backGroundColor);  // Set background color
    uart_puts(textColor);        // Set text color
    uart_puts("| No.| Command Name | Usage                                                   |\n"RESET_COLOR);
    uart_puts(backGroundColor);  // Set background color
    uart_puts(textColor);        // Set text color
    uart_puts("+----+--------------+---------------------------------------------------------+\n"RESET_COLOR);
    uart_puts(backGroundColor);  // Set background color
    uart_puts(textColor);        // Set text color
    uart_puts("| 1  | help         | - Show brief information of all commands                |\n"RESET_COLOR);
    uart_puts(backGroundColor);  // Set background color
    uart_puts(textColor);        // Set text color
    uart_puts("|    |              | - Example: MyOS> help                                   |\n"RESET_COLOR);
    uart_puts(backGroundColor);  // Set background color
    uart_puts(textColor);        // Set text color
    uart_puts("|    | help         | - Show full information of the command                  |\n"RESET_COLOR);
    uart_puts(backGroundColor);  // Set background color
    uart_puts(textColor);        // Set text color
    uart_puts("|    | <command>    | - Example: MyOS> help hwinfo                            |\n"RESET_COLOR);
    uart_puts(backGroundColor);  // Set background color
    uart_puts(textColor);        // Set text color
    uart_puts("+----+--------------+---------------------------------------------------------+\n"RESET_COLOR);
    uart_puts(backGroundColor);  // Set background color
    uart_puts(textColor);        // Set text color
    uart_puts("| 2  | clear        | - Clear screen (in our terminal it will scroll down to  |\n"RESET_COLOR);
    uart_puts(backGroundColor);  // Set background color
    uart_puts(textColor);        // Set text color
    uart_puts("|    |              |   current position of the cursor).                      |\n"RESET_COLOR);
    uart_puts(backGroundColor);  // Set background color
    uart_puts(textColor);        // Set text color
    uart_puts("|    |              | - Example: MyOS> clear                                  |\n"RESET_COLOR);
    uart_puts(backGroundColor);  // Set background color
    uart_puts(textColor);        // Set text color
    uart_puts("+----+--------------+---------------------------------------------------------+\n"RESET_COLOR);
    uart_puts(backGroundColor);  // Set background color
    uart_puts(textColor);        // Set text color
    uart_puts("| 3  | setcolor     | - Set text color, and/or background color of the        |\n"RESET_COLOR);
    uart_puts(backGroundColor);  // Set background color
    uart_puts(textColor);        // Set text color
    uart_puts("|    |              |   console to one of the following colors: BLACK, RED,   |\n"RESET_COLOR);
    uart_puts(backGroundColor);  // Set background color
    uart_puts(textColor);        // Set text color
    uart_puts("|    |              |   GREEN, YELLOW, BLUE, PURPLE, CYAN, WHITE              |\n"RESET_COLOR);
    uart_puts(backGroundColor);  // Set background color
    uart_puts(textColor);        // Set text color
    uart_puts("|    |              | - Examples:                                             |\n"RESET_COLOR);
    uart_puts(backGroundColor);  // Set background color
    uart_puts(textColor);        // Set text color
    uart_puts("|    |              |   MyOS> setcolor -t yellow                              |\n"RESET_COLOR);
    uart_puts(backGroundColor);  // Set background color
    uart_puts(textColor);        // Set text color
    uart_puts("|    |              |   MyOS> setcolor -b yellow -t white                     |\n"RESET_COLOR);
    uart_puts(backGroundColor);  // Set background color
    uart_puts(textColor);        // Set text color
    uart_puts("+----+--------------+---------------------------------------------------------+\n"RESET_COLOR);
    uart_puts(backGroundColor);  // Set background color
    uart_puts(textColor);        // Set text color
    uart_puts("| 4  | showinfo     | - Show board revision and board MAC address in correct  |\n"RESET_COLOR);
    uart_puts(backGroundColor);  // Set background color
    uart_puts(textColor);        // Set text color
    uart_puts("|    |              |   format/meaningful information                         |\n"RESET_COLOR);
    uart_puts(backGroundColor);  // Set background color
    uart_puts(textColor);        // Set text color
    uart_puts("|    |              | - Example: MyOS> showinfo                               |\n"RESET_COLOR);
    uart_puts(backGroundColor);  // Set background color
    uart_puts(textColor);        // Set text color
    uart_puts("+----+--------------+---------------------------------------------------------+\n"RESET_COLOR);
    printOS();
}

void selectFunction(char *s) {
    if(matchCommand(s) == 1) {
        printMenu();
    }else if(matchCommand(s) == 2) {
        printClearInfor();
    } else if(matchCommand(s) == 3) {
        printSetColorCommand();
    } else if(matchCommand(s) == 4) {
        printShowCommand();
    } else if(matchCommand(s) == 5) {
        clearCommand();
    } else if(matchCommand(s) == 6) {
        display_system_info();
    } else if(matchCommand(s) == 7) {
        returnTextColor(s);
        printOS();
    } else if(matchCommand(s) == 8) {
        returnBackGroundColor(s);
        printOS();
    } else  {
        printOS(); // Print the prompt again for a new command
    }
}

void deleteChar() {
    // will delete the last element in the commandLine
        uart_backspace();
        commandLine[commandIndex] = '\0'; // Null-terminate the
        if(commandIndex > 0) {
            commandIndex--; // to avoid negative
        }
        if(commandIndex == 0) {
            commandLine[commandIndex] = '\0'; // Null-terminate the
        }
}

void inputChar(char c) {
    if(c != 0x08 && c != '\t' && c != '+' && c != '_') {
        if (commandIndex < COMMAND_LINE_SIZE - 1) {
        commandLine[commandIndex] = c; // Add the character to commandLine and increment index
        commandIndex++;
        commandLine[commandIndex] = '\0'; // Null-terminate the string
        } else {
        // Handle overflow, for example, by resetting the command line
        resetCommandLine();
        uart_puts(RED_COLOR"\nIndex out of length for your command\n"RESET_COLOR);
        printOS();
        }
    } else if(c == 0x08 && commandIndex > 0 && c != '\t' && c != '+' && c != '_') {
        deleteChar();
    }
}

void onTabPress(char c) {
     // Send back the character (echo), if the command line is fully deleted and people backspace, it is not allowed
    if(c != '\t' && c != '+' && c != '_') {
        uart_sendc(c); // avoid corruption
    } else if(c == '\t') {
        while(commandIndex > 0) {
            uart_backspace();
            commandIndex--;
        }
        autocomplete(commandLine);
    }
}

void onEnterPress(char c) {
    // Check for the 'Enter' key 
    if (c == '\n') {
        selectFunction(commandLine);
        int index = find_char_index(commandLine, '\n');
        extract_char(commandLine, index);
        push(commandBuffer, commandLine);
        resetCommandLine();
        numberOfPlusPresses = 0;
        numberOfMinusPresses = 0;
        currentIndex = 0;
    }
}

void onPlusPress(char c) {
    if(c == '+') {
        numberOfPlusPresses++;
        int len = getLength(commandLine);
        while(len  > 0) {
            uart_backspace(); // error: after press +, the select function does not work
            len--;
        }
        resetBuffer();
        char *temp = peek(commandBuffer, numberOfPlusPresses); // get the string to temp and send to buffer
        strcpy_custom(commandLine, temp);
        commandIndex = getLength(commandLine);
        uart_puts(commandLine); 
    }
}

void onMinusPress(char c) {
    if(c == '_') {
        numberOfMinusPresses++;
        int len = getLength(commandLine);
        while(len  > 0) {
            uart_backspace(); // error: after press +, the select function does not work
            len--;
        }
        resetBuffer();
        char *temp = returnPeek(commandBuffer, numberOfMinusPresses); // get the string to temp and send to buffer
        strcpy_custom(commandLine, temp);
        commandIndex = getLength(commandLine);
        uart_puts(commandLine); 
    }
}

int typeCommand() {
    // Read each char
    char c = uart_getc();
    inputChar(c);
    onTabPress(c);
    onEnterPress(c);
    onPlusPress(c);
    onMinusPress(c);
    return 0;
}

void clearCommand(void) {
    uart_puts("\x1B[1;1H\x1B[2J");
    printOS();
}

void autocomplete(const char *input) {
    int found = 0;
    for (int i = 0; i < 5; i++) {
        if (strncmp_custom(commands[i], input, getLength(input)) == 0) { // check if the string is mentioned
            commandIndex = getLength(commands[i]);
            strcpy_custom(commandLine, commands[i]);
            uart_puts(commandLine);
            found = 1;
        }
    }
}

int getBoardRevision(void) {
     // mailbox data buffer: Read ARM frequency
    mBuf[0] = 7*4; // Message Buffer Size in bytes (8 elements * 4 bytes (32 bit) each)
    mBuf[1] = MBOX_REQUEST; // Message Request Code (this is a request message)
    mBuf[2] = BOARD_REVISION_TAG; // TAG Identifier: Get uart clock command,
    mBuf[3] = 4; // Value buffer size in bytes (max of request and response lengths)
    mBuf[4] = 0; // REQUEST CODE = 0
    mBuf[5] = 0; // clear output buffer (response data are mBuf[5] & mBuf[6])
    mBuf[6] = MBOX_TAG_LAST;
    if (mbox_call(ADDR(mBuf), MBOX_CH_PROP)) {
        return mBuf[5];
    } else {
        return "Can not find data";
    }
}

int getMacAddress(void) {
    // mailbox data buffer: Read ARM frequency
    mBuf[0] = 7*4; // Message Buffer Size in bytes (8 elements * 4 bytes (32 bit) each)
    mBuf[1] = MBOX_REQUEST; // Message Request Code (this is a request message)
    mBuf[2] = MAC_ADR; // TAG Identifier: Get uart clock command,
    mBuf[3] = 6; // Value buffer size in bytes (max of request and response lengths)
    mBuf[4] = 0; // REQUEST CODE = 0
    mBuf[5] = 0; // clear output buffer (response data are mBuf[5] & mBuf[6])
    mBuf[6] = MBOX_TAG_LAST;
    if (mbox_call(ADDR(mBuf), MBOX_CH_PROP)) {
        return mBuf[5];
    } else {
        return "Can not find data";
    }
}

void display_system_info() {
    uart_puts("+---------------------------------------------------------+\n");
    uart_puts("| Board Info             | Value                          |\n");
    uart_puts("+---------------------------------------------------------+\n");
    
    // Board Revision
    uart_puts("| Board Revision         | ");
    uart_hex(getBoardRevision());
    uart_puts("                         |\n"); // Adjust spaces manually to align the table
    
    // MAC Address
    uart_puts("| MAC Address            | ");
    uart_hex(getMacAddress());
    uart_puts("                         |\n"); // Adjust spaces based on expected length of MAC address
    
    uart_puts("+---------------------------------------------------------+\n");
    printOS();
}

char *returnTextColor(char *input) {
     // Check for the "setcolor -t " prefix
     
     extract_char(input, find_char_index(input, '\n'));
    if (strncmp_custom(input, "setcolor -t ", 12) == 0) {
        const char* color = input + 12; // Get the color part of the string

        // Compare and return the corresponding color code
        if (compare(color, "red")) {
            textColor = RED_COLOR;
            return RED_COLOR;
        } else if (compare(color, "green")) {
            textColor = GREEN_COLOR;
            return GREEN_COLOR;
        } else if (compare(color, "yellow")) {
            textColor = YELLOW_COLOR;
            return YELLOW_COLOR;
        } else if (compare(color, "blue")) {
            textColor = BLUE_COLOR;
            return BLUE_COLOR;
        } else if (compare(color, "magenta")) {
            textColor = MAGENTA_COLOR;
            return MAGENTA_COLOR;
        } else if (compare(color, "cyan")) {
            textColor = CYAN_COLOR;
            return CYAN_COLOR;
        } else if (compare(color, "white")) {
            textColor = WHITE_COLOR;
            return WHITE_COLOR;
        } else if (compare(color, "black")) {
            textColor = BLACK_COLOR;
            return BLACK_COLOR;
        }
    }
}

char *returnBackGroundColor(char *input) {
     // Check for the "setcolor -t " prefix
     
     extract_char(input, find_char_index(input, '\n'));
    if (strncmp_custom(input, "setcolor -b ", 12) == 0) {
        const char* color = input + 12; // Get the color part of the string

        // Compare and return the corresponding color code
        if (compare(color, "red")) {
            backGroundColor = ANSI_COLOR_RED;
            return ANSI_COLOR_RED;
        } else if (compare(color, "green")) {
            backGroundColor = ANSI_COLOR_GREEN;
            return ANSI_COLOR_GREEN;
        } else if (compare(color, "yellow")) {
            backGroundColor = ANSI_COLOR_YELLOW;
            return ANSI_COLOR_YELLOW;
        } else if (compare(color, "blue")) {
            backGroundColor = ANSI_COLOR_BLUE;
            return ANSI_COLOR_BLUE;
        } else if (compare(color, "magenta")) {
            backGroundColor = ANSI_COLOR_MAGENTA;
            return ANSI_COLOR_MAGENTA;
        } else if (compare(color, "cyan")) {
            backGroundColor = ANSI_COLOR_CYAN;
            return ANSI_COLOR_CYAN;
        } else if (compare(color, "white")) {
            backGroundColor = ANSI_COLOR_WHITE;
            return ANSI_COLOR_WHITE;
        } else if (compare(color, "black")) {
            backGroundColor = ANSI_COLOR_BLACK;
            return ANSI_COLOR_BLACK;
        }
    }
}
