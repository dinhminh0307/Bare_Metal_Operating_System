#include "./uart.h"


void uart_init()
{
    /*Using GPIO 32 and 33 for UART1*/
    unsigned int r;
    /* initialize UART */
    AUX_ENABLE |= 1; //enable mini UART (UART1)
    AUX_MU_CNTL = 0; //stop transmitter and receiver
    AUX_MU_LCR = 3; //8-bit mode (also enable bit 1 to be used for RBP3)
    AUX_MU_MCR = 0; //clear RTS (request to send)
    AUX_MU_IER = 0; //disable interrupts
    AUX_MU_IIR = 0xc6; //enable and clear FIFOs
    AUX_MU_BAUD = 54; //configure 57600 baud [system_clk_freq/(baud_rate*8) - 1]
    /* map UART1 to GPIO pins 32 and 33 */
    r = GPFSEL3;
    r &= ~( (7 << 6)|(7 << 9) ); //clear bits 17-12 (FSEL15, FSEL14)
    r |= (2 << 6)|(2 << 9); //set value 2 (select ALT5: TXD1/RXD1)
    GPFSEL3 = r;
    /* enable GPIO 14, 15 */
    GPPUD = 0; //No pull up/down control
    r = 150; while(r--) { asm volatile("nop"); } //waiting 150 cycles
    GPPUDCLK1 = (1 << 32)|(1 << 33); //enable clock for GPIO 32, 33
    r = 150; while(r--) { asm volatile("nop"); } //waiting 150 cycles
    GPPUDCLK1 = 0; //flush GPIO setup
    AUX_MU_CNTL = 3; //enable transmitter and receiver (Tx, Rx)
}

void uart_backspace() {
    // wait until transmitter is empty bit number 5
    do {
    asm volatile("nop");
    } while ( !(AUX_MU_LSR & 0x20) );
    // write the character to the buffer
    // AUX_MU_IO = c; // AUX_MU_IO is used for both read and write data

    // If it's a backspace
    // Send the backspace
        AUX_MU_IO = 0x08;
        // Wait until transmitter is empty again
        do {
            asm volatile("nop");
        } while (!(AUX_MU_LSR & 0x20));
        // Send space to overwrite the last character
        AUX_MU_IO = ' ';
        // Wait until transmitter is empty again
        do {
            asm volatile("nop");
        } while (!(AUX_MU_LSR & 0x20));
        // Send backspace again to move the cursor back
        AUX_MU_IO = 0x08;
}

/**
* Send a character
*/
void uart_sendc(char c) {
    // wait until transmitter is empty bit number 5
    do {
    asm volatile("nop");
    } while ( !(AUX_MU_LSR & 0x20) );
    // write the character to the buffer
    if(c != '\b') {
        AUX_MU_IO = c; // AUX_MU_IO is used for both read and write data
    }
}
/**
* Receive a character
*/
char uart_getc() {
    char c;
    // wait until data is ready (one symbol) bit 0
    do {
    asm volatile("nop");
    } while ( !(AUX_MU_LSR & 0x01) );
    // read it and return
    c = (unsigned char)(AUX_MU_IO); 
    // convert carriage return to newline character
    return (c == '\r' ? '\n' : c);
}
/**
* Display a string
*/
void uart_puts(char *s) {
    while (*s) {
    // convert newline to carriage return + newline
    if (*s == '\n')
    uart_sendc('\r');
    uart_sendc(*s++);
    }
}

void send_string(const char *s) {
    while (*s) { // Loop until the end of the string
        uart_sendc(*s++); // Send each character and increment the pointer
    }
}

/**
* Display a value in hexadecimal format
*/
void uart_hex(unsigned int num) {
    uart_puts("0x");
    for (int pos = 28; pos >= 0; pos = pos - 4) {
    // Get highest 4-bit nibble
    char digit = (num >> pos) & 0xF;
    /* Convert to ASCII code */
    // 0-9 => '0'-'9', 10-15 => 'A'-'F'
    digit += (digit > 9) ? (-10 + 'A') : '0';
    uart_sendc(digit);
    }
}
/**
* Display a value in decimal format
*/
void uart_dec(int num)
{
    //A string to store the digit characters
    char str[33] = "";
    //Calculate the number of digits
    int len = 1;
    int temp = num;
    while (temp >= 10){
    len++;
    temp = temp / 10;
    }
    //Store into the string and print out
    for (int i = 0; i < len; i++){
    int digit = num % 10; //get last digit
    num = num / 10; //remove last digit from the number
    str[len - (i + 1)] = digit + '0';

    }
    str[len] = '\0';
    uart_puts(str);
}