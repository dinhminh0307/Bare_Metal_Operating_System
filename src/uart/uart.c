#include "./uart.h"
int custom_baudrate = 0;
int custom_data_bit = 0;
int custom_stop_bit = 1;
char parity_bit[100];
char hand_shaking[100];

void uart_setup() {

}

void uart_init()
{
      unsigned int r;

	/* Turn off UART0 */
	UART0_CR = 0x0;

	/* Setup GPIO pins 14 and 15 */

	/* Set GPIO14 and GPIO15 to be pl011 TX/RX which is ALT0	*/
	r = GPFSEL1;
	r &=  ~((7 << 12) | (7 << 15)); //clear bits 17-12 (FSEL15, FSEL14)
	r |= (0b100 << 12)|(0b100 << 15);   //Set value 0b100 (select ALT0: TXD0/RXD0)
	GPFSEL1 = r;
	

	/* enable GPIO 14, 15 */

	GPPUD = 0;            //No pull up/down control
	//Toogle clock to flush GPIO setup
	r = 150; while(r--) { asm volatile("nop"); } //waiting 150 cycles
	GPPUDCLK0 = (1 << 14)|(1 << 15); //enable clock for GPIO 14, 15
	r = 150; while(r--) { asm volatile("nop"); } //waiting 150 cycles
	GPPUDCLK0 = 0;        // flush GPIO setup


	/* Mask all interrupts. */
	UART0_IMSC = 0;

	/* Clear pending interrupts. */
	UART0_ICR = 0x7FF;

	/* Set integer & fractional part of Baud rate
	Divider = UART_CLOCK/(16 * Baud)            
	Default UART_CLOCK = 48MHz (old firmware it was 3MHz); 
	Integer part register UART0_IBRD  = integer part of Divider 
	Fraction part register UART0_FBRD = (Fractional part * 64) + 0.5 */

	//115200 baud
	UART0_IBRD = 26;       
	UART0_FBRD = 3;

	/* Set up the Line Control Register */
	/* Enable FIFO */
	/* Set length to 8 bit */
	/* Defaults for other bit are No parity, 1 stop bit */
	UART0_LCRH = UART0_LCRH_FEN | UART0_LCRH_WLEN_8BIT;

	/* Enable UART0, receive, and transmit */
	UART0_CR = 0x301;     // enable Tx, Rx, FIFO
}

void uart_backspace() {
    // wait until transmitter is empty bit number 5
     // Wait until transmitter is empty (check if transmit FIFO is empty)
    do {
        asm volatile("nop");
    } while (UART0_FR & (1 << 5)); // UART_FR_TXFF is typically the 5th bit, check if FIFO is full.

    // Send the backspace character
    UART0_DR = 0x08;  // Backspace ASCII code

    // Wait until transmitter is empty again
    do {
        asm volatile("nop");
    } while (UART0_FR & (1 << 5)); // Check if FIFO is full again

    // Send space to overwrite the last character
    UART0_DR = ' ';

    // Wait until transmitter is empty again
    do {
        asm volatile("nop");
    } while (UART0_FR & (1 << 5)); // Check if FIFO is full again

    // Send backspace again to move the cursor back
    UART0_DR = 0x08;
}

/**
* Send a character
*/
void uart_sendc(char c) {
    // // wait until transmitter is empty bit number 5
    // do {
    // asm volatile("nop");
    // } while ( !(AUX_MU_LSR & 0x20) );
    // // write the character to the buffer

    /* Check Flags Register */
	/* And wait until transmitter is not full */
	
    do {
        asm volatile("nop");
    } while(UART0_FR & UART0_FR_TXFF); // 0x20 is to indicate bit number 5 to check transmite FIFO is full
    if(c != '\b') {
        UART0_DR = c; // AUX_MU_IO is used for both read and write data
    }
}
/**
* Receive a character
*/
char uart_getc() {
    char c = 0;

    /* Check Flags Register */
    /* Wait until Receiver is not empty
     * (at least one byte data in receive fifo)*/
	do {
		asm volatile("nop");
    } while ( UART0_FR & UART0_FR_RXFE );

    /* read it and return */
    c = (unsigned char) (UART0_DR);

    /* convert carriage return to newline */
    return (c == '\r' ? '\n' : c);
}
/**
* Display a string
*/
void uart_puts(char *s) {
    while (*s) {
        /* convert newline to carriage return + newline */
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

char *formatMacAdress(unsigned int mac) {
    char formatted_mac[18];
    int idx = 17;
    formatted_mac[idx--] = '\0'; // Null terminator
    
    for (int i = 0; i < 6; i++) {
        // Format each byte starting from the least significant byte
        unsigned char byte = (mac >> (i * 8)) & 0xFF;
        
        // Convert the low nibble to hexadecimal character
        char low = byte & 0x0F;
        formatted_mac[idx--] = (low <= 9) ? (low + '0') : (low - 10 + 'A');
        
        // Convert the high nibble to hexadecimal character
        char high = (byte >> 4) & 0x0F;
        formatted_mac[idx--] = (high <= 9) ? (high + '0') : (high - 10 + 'A');
        
        // Insert colon if not at the start
        if (i < 5) {
            formatted_mac[idx--] = ':';
        }
    }
    uart_puts(formatted_mac);
}