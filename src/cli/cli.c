#include "./cli.h"

char commandLine[COMMAND_LINE_SIZE]; // Fixed-size array for the command line
char set_up_buffer[COMMAND_LINE_SIZE];
char suggestionBuffer[COMMAND_LINE_SIZE];

int set_up_index = 0;

int suggestionLenght;
int commandIndex = 0; // Index to keep track of the current position in commandLine
char commandBuffer[COMMAND_LINE_SIZE][COMMAND_LINE_SIZE] = {0};
char history_buffer[COMMAND_LINE_SIZE];
volatile int numberOfPlusPresses = 0;
volatile int numberOfMinusPresses = 0;
int helpIndex;
int setColorIndex;
int tabIndex;
int found = 0;

// flag for display message
volatile int isWelcomeMsgDisp = 0;

// flag for baud rate setup
volatile int isBaudRateChoose = 0;
volatile int isDataFrameChoose = 0;

// flag for exercise 2
volatile int isSetUpSelected = 0;

char *textColor;
char *backGroundColor;

// flag for auto complete proccess
volatile int helpTabPressed = 0;
volatile int isHelpFound = 0;

// flag for setcolor auto completion
volatile int isSetColorPressed = 0;
volatile int setColorTabPressed = 0;

//flag for command auto completion
volatile int isTabPressed = 0;

// For setup recap
char parity_print[COMMAND_LINE_SIZE];
char hand_shaking_print[COMMAND_LINE_SIZE];


// Utility function to reset the commandLine buffer
void resetCommandLine() {
    for (int i = 0; i < COMMAND_LINE_SIZE; i++) {
        commandLine[i] = '\0';
    }
    commandIndex = 0;
}

void clearSuggestionbuffer() {
    for (int i = 0; i < COMMAND_LINE_SIZE; i++) {
        suggestionBuffer[i] = '\0';
    }
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

void printWelcomeMsg(void) {
    uart_puts(BRIGHT_YELLOW_COLOR);
    uart_puts("      :::::::::: :::::::::: :::::::::: ::::::::::: ::::::::   :::     ::::::::   :::::::\n ");
    uart_puts("     :+:        :+:        :+:            :+:    :+:    :+: :+:     :+:    :+: :+:   :+: \n");
    uart_puts("    +:+        +:+        +:+            +:+          +:+ +:+ +:+  +:+    +:+ +:+   +:+  \n");
    uart_puts("   +#++:++#   +#++:++#   +#++:++#       +#+        +#+  +#+  +:+   +#++:++#+ +#+   +:+   \n");
    uart_puts("  +#+        +#+        +#+            +#+      +#+   +#+#+#+#+#+       +#+ +#+   +#+    \n");
    uart_puts(" #+#        #+#        #+#            #+#     #+#          #+#  #+#    #+# #+#   #+#     \n");
    uart_puts("########## ########## ##########     ###    ##########    ###   ########   #######       \n\n");
    uart_puts("      :::::::::      :::     :::::::::  ::::::::::       ::::::::   ::::::::        \n");
    uart_puts("     :+:    :+:   :+: :+:   :+:    :+: :+:             :+:    :+: :+:    :+:      \n");
    uart_puts("    +:+    +:+  +:+   +:+  +:+    +:+ +:+             +:+    +:+ +:+                \n");
    uart_puts("   +#++:++#+  +#++:++#++: +#++:++#:  +#++:++#        +#+    +:+ +#++:++#++           \n");
    uart_puts("  +#+    +#+ +#+     +#+ +#+    +#+ +#+             +#+    +#+        +#+          \n");
    uart_puts(" #+#    #+# #+#     #+# #+#    #+# #+#             #+#    #+# #+#    #+#             \n");
    uart_puts("#########  ###     ### ###    ### ##########       ########   ########    \n");
    uart_puts("\nDeveloped by Dinh Ngoc Minh-s3925113");
    uart_puts(RESET_COLOR);
    printOS();
}

void printClearInfor(void) {
    uart_puts(backGroundColor);  // Set background color
    uart_puts(textColor);        // Set text color
    uart_puts("+----+--------------+---------------------------------------------------------+\n");
    uart_puts("| 2  | clear        | - Clear screen (in our terminal it will scroll down to  |\n");
    uart_puts("|    |              |   current position of the cursor).                      |\n");
    uart_puts("|    |              | - Example: MyOS> clear                                  |\n");
    uart_puts("+----+--------------+---------------------------------------------------------+\n");
     printOS();
}

void printSetColorCommand(void) {
    uart_puts(backGroundColor);  // Set background color
    uart_puts(textColor);        // Set text color 
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

void printSetUpCommand(void) {
    uart_puts(backGroundColor);  // Set background color
    uart_puts(textColor);        // Set text color
    uart_puts("+----+--------------+---------------------------------------------------------+\n");
    uart_puts("| 5  | setup        | - This command will let user to setup the PLL01 UART    |\n");
    uart_puts("|    |              |                                                         |\n");
    uart_puts("|    |              |                                                         |\n");
    uart_puts("+----+--------------+---------------------------------------------------------+\n");
    
    printOS();
}

void printShowCommand(void) {
    uart_puts(backGroundColor);  // Set background color
    uart_puts(textColor);        // Set text color
    uart_puts("+----+--------------+---------------------------------------------------------+\n");
    uart_puts("| 4  | showinfo     | - Show board revision and board MAC address in correct  |\n");
    uart_puts("|    |              |   format/meaningful information                         |\n");
    uart_puts("|    |              | - Example: MyOS> showinfo                               |\n");
    uart_puts("+----+--------------+---------------------------------------------------------+\n");
    
    printOS();
}

void printMenu() {
    uart_puts(backGroundColor);  // Set background color
    uart_puts(textColor);        // Set text color
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
    uart_puts("| 5  | boot         | - This command will let user to setup the PLL01 UART    |\n");
    uart_puts("|    |              |                                                         |\n");
    uart_puts("|    |              |                                                         |\n");
    uart_puts("+----+--------------+---------------------------------------------------------+\n");
    printOS();
}

void selectFunction(char *s) {
    if(isSetUpSelected == 0) {
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
        } else if(matchCommand(s) == 9 ) {
            isSetUpSelected = 1;
            askBaudRate();
        } else if(matchCommand(s) == 10) {
            printSetUpCommand();
        } else  {
            if(*s == '\n') {
                printOS(); // Print the prompt again for a new command
            } else {
                uart_puts(RED_COLOR "Invalid command\n" RESET_COLOR);
                printOS();
            }
        }
    }
}

void clearSetUpBuffer(void) {
    set_up_buffer[set_up_index] = '\0';
        if(set_up_index > 0) {
            set_up_index--; // to avoid delete
        }
        if(set_up_index == 0) {
            set_up_buffer[set_up_index] = '\0'; // Null-terminate the
        }
}

void deleteChar() {
    // will delete the last element in the commandLine
        uart_backspace();
        commandLine[commandIndex] = '\0';
        if(commandIndex > 0) {
            commandIndex--; // to avoid delete
        }
        if(commandIndex == 0) {
            commandLine[commandIndex] = '\0'; // Null-terminate the
            isHelpFound = 0;
        }
        found = 0;
}

void resetSetUpBuffer() {
    for (int i = 0; i < COMMAND_LINE_SIZE; i++) {
        set_up_buffer[i] = '\0';
    }
    set_up_index = 0;
}

/**@brief Function to check type of parity bit user selectd
 */
void check_parity_bit() {
    if(compare(set_up_buffer, "even")) {
        parity_bit = EVEN_PARITY_BIT;
        strcpy_custom(parity_print, set_up_buffer);
    } else if(compare(set_up_buffer, "odd")) {
        parity_bit = ODD_PARITY_BIT;
        strcpy_custom(parity_print, set_up_buffer);
    } else {
        parity_bit = DEFAULT;
        strcpy_custom(parity_print, "Default");
    }
}

/**@brief Function to check the line control of uart
 */
void check_hand_shaking() {
    if(compare(set_up_buffer, "yes")) {
        hand_shaking = RTS_CTS_EN;
        strcpy_custom(hand_shaking_print, set_up_buffer);
    } else {
        hand_shaking = DEFAULT;
        strcpy_custom(hand_shaking_print, "no");
    } 
}

void uart_setting_notification(void) {
    uart_puts(backGroundColor);  // Set background color
    uart_puts(textColor);        // Set text color
    uart_puts("\n================ UART Configuration ================\n");
    uart_puts("| Setting               | Value      |\n");
    uart_puts("|-----------------------|------------|\n");

    // Baud Rate
    uart_puts("| Baud Rate             | ");
    uart_dec(custom_baudrate);
    uart_puts("         |\n");

    // Data Bits
    uart_puts("| Data Bits             | ");
    uart_dec(custom_data_bit);
    uart_puts("         |\n");

    // Stop Bits
    uart_puts("| Stop Bits             | ");
    uart_dec(custom_stop_bit);
    uart_puts("         |\n");

    // Parity Bit
    uart_puts("| Parity Bit            | ");
    uart_puts(parity_print);
    uart_puts("        |\n");

    // Handshaking
    uart_puts("| Handshaking           | ");
    uart_puts(hand_shaking_print);
    uart_puts("        |\n");

    uart_puts("====================================================\n");
}

void set_up_type(char c) {
    if(c != 0x08 && c!= '\n') {
        if (set_up_index < COMMAND_LINE_SIZE - 1) {
        set_up_buffer[set_up_index] = c; // Add the character to commandLine and increment index
        set_up_index++;
        set_up_buffer[set_up_index] = '\0'; // Null-terminate the string
        } else {
        // Handle overflow, for example, by resetting the command line
        resetSetUpBuffer();
        uart_puts(RED_COLOR"\nIndex out of length for your command\n"RESET_COLOR);
        // printOS();
        }
    } else if(c == 0x08) {
        deleteChar();
        clearSetUpBuffer(); // to avoid conflict when user mistakenly typo
    } else if(c == '\n') { // check if the uart setup is entered
        if(isSetUpSelected == 1) {
            int index = find_char_index(set_up_buffer, '\n');
            extract_char(set_up_buffer, index);
            custom_baudrate = stringToInt(set_up_buffer);
            resetSetUpBuffer();
            isSetUpSelected++;
            uart_puts("\nPlease enter data bits:\n");
        } else if(isSetUpSelected == 2) {
            // used for data bit
            int index = find_char_index(set_up_buffer, '\n');
            extract_char(set_up_buffer, index);
            custom_data_bit = stringToInt(set_up_buffer);
            resetSetUpBuffer();
            isSetUpSelected++;
            uart_puts("\nPlease enter stop bit:\n");
        } else if(isSetUpSelected == 3) {
            // used for stop bit
            int index = find_char_index(set_up_buffer, '\n');
            extract_char(set_up_buffer, index);
            custom_stop_bit = stringToInt(set_up_buffer);
            resetSetUpBuffer();
            isSetUpSelected++;
            uart_puts("\nEnter parity bit:\n");
        } else if(isSetUpSelected == 4) {
            // set a while to check the valid input
            int index = find_char_index(set_up_buffer, '\n');
            extract_char(set_up_buffer, index);
            strcpy_custom(parity_bit, set_up_buffer);
            check_parity_bit();
            resetSetUpBuffer();
            isSetUpSelected++;
            uart_puts("\nSelect handshaking control: \n");
        } else if(isSetUpSelected == 5) {
            // set a while to check the valid input
            int index = find_char_index(set_up_buffer, '\n');
            extract_char(set_up_buffer, index);
            strcpy_custom(hand_shaking, set_up_buffer);
            check_hand_shaking();
            resetSetUpBuffer();
            isSetUpSelected = 0;
            isUartSetUp = 1;
            //After this, add a function to recap all change
            uart_setting_notification();
        }
    }
    uart_sendc(c); // bug here
}

void inputChar(char c) {
    if(c != 0x08 && c != '\t' && c != '+' && c != '_') {
        if (commandIndex < COMMAND_LINE_SIZE - 1) {
        commandLine[commandIndex] = c; // Add the character to commandLine and increment index
        commandIndex++;
        commandLine[commandIndex] = '\0'; 
        } else {
        // Handle overflow
        resetCommandLine();
        uart_puts(RED_COLOR"\nIndex out of length for your command\n"RESET_COLOR);
        printOS();
        }
    } else if(c == 0x08 && commandIndex > 0 && c != '\t' && c != '+' && c != '_') {
        deleteChar();
    }
}

void clearCommandLineBuffer() {
    while(commandIndex > 0) {
            uart_backspace();
            commandIndex--;
        }
}


void onTabPress(char c) {
     // Send back the character (echo), if the command line is fully deleted and people backspace, it is not allowed
    if(c != '\t' && c != '+' && c != '_') {
        uart_sendc(c); // avoid corruption
    } else if(c == '\t') {
        isTabPressed++;
        clearCommandLineBuffer(); // clear the old cmd when press tab
        if(strncmp_custom(commandLine, "help ", 5) == 0) {
            helpTabPressed++;
            findHelpCommand();
        } else if(strncmp_custom(commandLine, "setcolor ", 9) == 0) {
            setColorTabPressed++; 
            find_set_color_command();
        } else {
            autocomplete(commandLine);
        }
    }
}


void onEnterPress(char c) {
    // Check for the 'Enter' key
    if(isWelcomeMsgDisp == 0) {
        isWelcomeMsgDisp = 1;
    } 
    if (c == '\n') {
            selectFunction(commandLine);
            int index = find_char_index(commandLine, '\n');
            extract_char(commandLine, index); // extract the new line
            push(commandBuffer, commandLine); // sotre the extracted command line into the command buffer history

            //clear all flag
            resetCommandLine();
            numberOfPlusPresses = 0;
            numberOfMinusPresses = 0;
            currentIndex = 0;
            isTabPressed = 0;
            helpTabPressed = 0; // clear flag
            setColorTabPressed = 0;
            isSetColorPressed = 0;
            setColorIndex = 0;
            helpIndex = 0;
            tabIndex = 0;
    }
}

void onPlusPress(char c) { // some error here
    if(c == '+') {
        numberOfPlusPresses++;
        numberOfMinusPresses = 0;
        int len = getLength(commandLine);
        while(len  > 0) {
            uart_backspace(); //clear the current command line 
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
        numberOfPlusPresses = 0;
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
    while(isSetUpSelected > 0) {
        char c = uart_getc();
        set_up_type(c);
    }
    if(isSetUpSelected == 0) { // avoid corruption
        // Read each char
        char c = uart_getc();
        inputChar(c);
        onTabPress(c);
        onEnterPress(c);
        onPlusPress(c);
        onMinusPress(c);
    }
    return 0;
}

void clearCommand(void) {
    uart_puts("\x1B[1;1H\x1B[2J");
    printOS();
}

/*when user type s => the corresponding last character of that command is sugessted (it will loop thru the enum and suggest, meanwhile the cursor still in current position)
  after user press tab, it will suggest other as well and if user hit enter, it will select
  hit enter again to send the command */

//this function used to avoid overlap of autocompletion function
void getCompleteCommand(char *input) {
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

void autocomplete(const char *input) {
        if(found == 0) {
            getCompleteCommand(input);
        } else {
            if(isTabPressed == 1) {
            tabIndex = find_string_index(commands, commandLine);
            } else {
                tabIndex++;
            }
            clearCommandLineBuffer();
            strcpy_custom(commandLine, get_string_index(commands, tabIndex)); // error here
            if(tabIndex > 4) {
                tabIndex = 0;
            }
            commandIndex = getLength(commandLine);
            uart_puts(commandLine);
        }
}

void find_set_color_command() {
     // for help command
        // key value: tab:1 - index 0
        if(setColorTabPressed == 1) {
            setColorIndex = find_set_color_index(setcolor, commandLine);
        } else {
            setColorIndex++;
        }
        clearCommandLineBuffer();
        strcpy_custom(commandLine, get_set_color_index(setcolor, setColorIndex)); // error here
        if(setColorIndex > getSizeSetColor() - 1) {
            setColorIndex = 0;
        }
        commandIndex = getLength(commandLine);
        uart_puts(commandLine);
}

void findHelpCommand() {
    // for help command
        // key value: tab:1 - index 0
        if(helpTabPressed == 1) {
            helpIndex = find_string_help_index(help, commandLine);
        } else {
            helpIndex++;
        }
        clearCommandLineBuffer();
        strcpy_custom(commandLine, get_help_by_index(help, helpIndex)); // error here
        if(helpIndex > getSizeHelp() - 1) {
            helpIndex = 0;
        }
        commandIndex = getLength(commandLine);
        uart_puts(commandLine);
}


int getBoardRevision(void) {
     // mailbox data buffer: Read ARM frequency
    mBuf[0] = 7*4; // Message Buffer Size in bytes (7 elements * 4 bytes (32 bit) each)
    mBuf[1] = MBOX_REQUEST; // Message Request Code (this is a request message)
    mBuf[2] = BOARD_REVISION_TAG; // TAG Identifier: Get uart clock command,
    mBuf[3] = 4; // Value buffer size in bytes (max of request and response lengths)
    mBuf[4] = 0; // REQUEST CODE = 0
    mBuf[5] = 0; // clear output buffer (response data are mBuf[5] & mBuf[6])
    mBuf[6] = MBOX_TAG_LAST;
    if (mbox_call(ADDR(mBuf), MBOX_CH_PROP)) {
        return mBuf[5];
    } else {
        return 0;
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
    uart_puts(backGroundColor);  // Set background color
    uart_puts(textColor);        // Set text color
    uart_puts("+---------------------------------------------------------+\n");
    uart_puts(backGroundColor);  // Set background color
    uart_puts(textColor);        // Set text color
    uart_puts("| Board Info             | Value                          |\n");
    uart_puts(backGroundColor);  // Set background color
    uart_puts(textColor);        // Set text color
    uart_puts("+---------------------------------------------------------+\n");
    
    // Board Revision
    uart_puts(backGroundColor);  // Set background color
    uart_puts(textColor);        // Set text color
    uart_puts("| Board Revision         | ");
    uart_puts(backGroundColor);  // Set background color
    uart_puts(textColor);        // Set text color
    uart_hex(getBoardRevision());
    uart_puts(backGroundColor);  // Set background color
    uart_puts(textColor);        // Set text color
    uart_puts("                         |\n"); // Adjust spaces manually to align the table
    
    // MAC Address
    uart_puts(backGroundColor);  // Set background color
    uart_puts(textColor);        // Set text color
    uart_puts("| MAC Address            | ");
    uart_puts(backGroundColor);  // Set background color
    uart_puts(textColor);        // Set text color
    formatMacAdress(getMacAddress());
    uart_puts(backGroundColor);  // Set background color
    uart_puts(textColor);        // Set text color
    uart_puts("                         |\n"); // Adjust spaces based on expected length of MAC address
    uart_puts(backGroundColor);  // Set background color
    uart_puts(textColor);        // Set text color
    uart_puts("+---------------------------------------------------------+\n");
    printOS();
}

void printMsgSetColor(const char *color) {
    uart_puts("Color has set to ");
    uart_puts(color);
    uart_puts("\n");
}

char *returnTextColor(char *input) {
     // Check for the "setcolor -t " prefix
     
     extract_char(input, find_char_index(input, '\n'));
    if (strncmp_custom(input, "setcolor -t ", 12) == 0) {
        const char* color = input + 12; // Get the color part of the string
        // Compare and return the corresponding color code
        if (compare(color, "red")) {
            printMsgSetColor(color);
            textColor = DIM_RED_COLOR;
            return DIM_RED_COLOR;
        } else if (compare(color, "green")) {
            printMsgSetColor(color);
            textColor = DIM_GREEN_COLOR;
            return DIM_GREEN_COLOR;
        } else if (compare(color, "yellow")) {
            printMsgSetColor(color);
            textColor = DIM_YELLOW_COLOR;
            return DIM_YELLOW_COLOR;
        } else if (compare(color, "blue")) {
            printMsgSetColor(color);
            textColor = DIM_BLUE_COLOR;
            return DIM_BLUE_COLOR;
        } else if (compare(color, "magenta")) {
            printMsgSetColor(color);
            textColor = DIM_MAGENTA_COLOR;
            return DIM_MAGENTA_COLOR;
        } else if (compare(color, "cyan")) {
            printMsgSetColor(color);
            textColor = DIM_CYAN_COLOR;
            return DIM_CYAN_COLOR;
        } else if (compare(color, "white")) {
            printMsgSetColor(color);
            textColor = DIM_WHITE_COLOR;
            return DIM_WHITE_COLOR;
        } else if (compare(color, "black")) {
            printMsgSetColor(color);
            textColor = DIM_BLACK_COLOR;
            return DIM_BLACK_COLOR;
        } else if(compare(color, "reset")) {
            printMsgSetColor(color);
            textColor = RESET_COLOR;
            return RESET_COLOR;
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
            printMsgSetColor(color);
            backGroundColor = ANSI_COLOR_RED;
            return ANSI_COLOR_RED;
        } else if (compare(color, "green")) {
            printMsgSetColor(color);
            backGroundColor = ANSI_COLOR_GREEN;
            return ANSI_COLOR_GREEN;
        } else if (compare(color, "yellow")) {
            printMsgSetColor(color);
            backGroundColor = ANSI_COLOR_YELLOW;
            return ANSI_COLOR_YELLOW;
        } else if (compare(color, "blue")) {
            printMsgSetColor(color);
            backGroundColor = ANSI_COLOR_BLUE;
            return ANSI_COLOR_BLUE;
        } else if (compare(color, "magenta")) {
            printMsgSetColor(color);
            backGroundColor = ANSI_COLOR_MAGENTA;
            return ANSI_COLOR_MAGENTA;
        } else if (compare(color, "cyan")) {
            printMsgSetColor(color);
            backGroundColor = ANSI_COLOR_CYAN;
            return ANSI_COLOR_CYAN;
        } else if (compare(color, "white")) {
            printMsgSetColor(color);
            backGroundColor = ANSI_COLOR_WHITE;
            return ANSI_COLOR_WHITE;
        } else if (compare(color, "black")) {
            printMsgSetColor(color);
            backGroundColor = ANSI_COLOR_BLACK;
            return ANSI_COLOR_BLACK;
        } else if(compare(color, "reset")) {
            printMsgSetColor(color);
            backGroundColor = RESET_COLOR;
            return RESET_COLOR;
        }
    }
}

void askBaudRate(void) {
    uart_puts("Please enter the baud rate you want:\n");
}

