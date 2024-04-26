#include "../constant/gpio.h"
#define DEFAULT 0
#define EVEN_PARITY_BIT 1
#define ODD_PARITY_BIT 2

//For line control
#define RTS_CTS_EN 1
#define UART_CLOCK 48000000


// for uart setup
extern int custom_baudrate;
extern int custom_data_bit;
extern int custom_stop_bit;
extern int parity_bit;
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