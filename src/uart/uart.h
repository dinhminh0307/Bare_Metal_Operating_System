#include "../constant/gpio.h"

/* Function prototypes */
void uart_init();
void uart_sendc(char c);
char uart_getc();
void uart_puts(char *s);
void send_string(const char * s);
void uart_hex(unsigned int num);
void uart_dec(int num);
void uart_backspace();
char *formatMacAdress(unsigned int mac);