#include "./cli.h"

char commandLine[COMMAND_LINE_SIZE]; // Fixed-size array for the command line
int commandIndex = 0; // Index to keep track of the current position in commandLine

// Utility function to reset the commandLine buffer
void resetCommandLine() {
    for (int i = 0; i < COMMAND_LINE_SIZE; i++) {
        commandLine[i] = '\0';
    }
    commandIndex = 0;
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
    uart_puts("+----+--------------+---------------------------------------------------------+\n");
    uart_puts("| 4  | showinfo     | - Show board revision and board MAC address in correct  |\n");
    uart_puts("|    |              |   format/meaningful information                         |\n");
    uart_puts("|    |              | - Example: MyOS> showinfo                               |\n");
    uart_puts("+----+--------------+---------------------------------------------------------+\n");
    printOS();
}

void printMenu() {
    uart_puts("+----+--------------+---------------------------------------------------------+\n");
    uart_puts("| No.| Command Name | Usage                                                   |\n");
    uart_puts("+----+--------------+---------------------------------------------------------+\n");
    uart_puts("| 1  | help         | - Show brief information of all commands                |\n");
    uart_puts("|    |              | - Example: MyOS> help                                   |\n");
    uart_puts("|    | help         | - Show full information of the command                  |\n");
    uart_puts("|    | <command>    | - Example: MyOS> help hwinfo                            |\n");
    uart_puts("+----+--------------+---------------------------------------------------------+\n");
    uart_puts("| 2  | clear        | - Clear screen (in our terminal it will scroll down to  |\n");
    uart_puts("|    |              |   current position of the cursor).                      |\n");
    uart_puts("|    |              | - Example: MyOS> clear                                  |\n");
    uart_puts("+----+--------------+---------------------------------------------------------+\n");
    uart_puts("| 3  | setcolor     | - Set text color, and/or background color of the        |\n");
    uart_puts("|    |              |   console to one of the following colors: BLACK, RED,   |\n");
    uart_puts("|    |              |   GREEN, YELLOW, BLUE, PURPLE, CYAN, WHITE              |\n");
    uart_puts("|    |              | - Examples:                                             |\n");
    uart_puts("|    |              |   MyOS> setcolor -t yellow                              |\n");
    uart_puts("|    |              |   MyOS> setcolor -b yellow -t white                     |\n");
    uart_puts("+----+--------------+---------------------------------------------------------+\n");
    uart_puts("| 4  | showinfo     | - Show board revision and board MAC address in correct  |\n");
    uart_puts("|    |              |   format/meaningful information                         |\n");
    uart_puts("|    |              | - Example: MyOS> showinfo                               |\n");
    uart_puts("+----+--------------+---------------------------------------------------------+\n");
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
    } else  {
        printOS(); // Print the prompt again for a new command
    }
    resetCommandLine(); // Reset commandLine after processing the command
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

/*In the beginning, it can not be backspaced, an it can not backspace out of length of commandLine
  if c = backspace:
    while commandIndex > 0:
        backspace(); */
int typeCommand() {
    // Read each char
    char c = uart_getc();
    // Check for buffer overflow
    if(c != 0x08 && c != '\t') {
        if (commandIndex < COMMAND_LINE_SIZE - 1) {
        commandLine[commandIndex] = c; // Add the character to commandLine and increment index
        commandIndex++;
        commandLine[commandIndex] = '\0'; // Null-terminate the string
        } else {
        // Handle overflow, for example, by resetting the command line
        resetCommandLine();
        uart_puts("\nIndex out of length for your command\n");
        printOS();
        }
    } else if(c == 0x08 && commandIndex > 0 && c != '\t') {
        deleteChar();
    }
    
    // Send back the character (echo), if the command line is fully deleted and people backspace, it is not allowed
    if(c != '\t') {
        uart_sendc(c); // avoid corruption
    } else if(c == '\t') {
        while(commandIndex > 0) {
            uart_backspace();
            commandIndex--;
        }
        autocomplete(commandLine);
    }


    // Check for the 'Enter' key 
    if (c == '\n') {
        selectFunction(commandLine);
        resetCommandLine();
    }
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
            for(int j = 0; j < getLength(commands[i]); j++) {
                commandLine[j] = commands[i][j];
            }
            uart_puts(commandLine);
            found = 1;
        }
    }
}
