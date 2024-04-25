#include "../constant/gpio.h"

// for uart setup
extern int custom_baudrate;
extern int custom_data_bit;
extern int custom_stop_bit;
extern char parity_bit[100];
extern char hand_shaking[100];
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
void uart_setup();