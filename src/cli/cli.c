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

void resetCLI() {
    for(int i = 0; i < commandIndex;i++) {
        commandLine[i] = '\0';
    }
}

void debugTool() {
    char *c = "123456";
    uart_puts(getLength(c));
}

void printOS(void) {
    uart_puts("\n\nC:/DELL/MInh_OS> ");
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
    } else  {
        printOS(); // Print the prompt again for a new command
    }
    resetCLI();
    resetCommandLine(); // Reset commandLine after processing the command
}

int typeCommand() {
    // Read each char
    char c = uart_getc();

    // Check for buffer overflow
    if (commandIndex < COMMAND_LINE_SIZE - 1) {
        commandLine[commandIndex] = c; // Add the character to commandLine and increment index
        commandIndex++;
        commandLine[commandIndex] = '\0'; // Null-terminate the string
    } else {
        // Handle overflow, for example, by resetting the command line
        resetCommandLine();
        uart_puts("\nCommand too long. Please try again.\n");
        printOS();
    }

    // Send back the character (echo)
    uart_sendc(c);

    // Check for the 'Enter' key and if the command is "help"
    if (c == '\n') {
        selectFunction(commandLine);
    }

    return 0;
}