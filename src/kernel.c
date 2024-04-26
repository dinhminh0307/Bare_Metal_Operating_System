#include "./cli/cli.h"

#include "./mailbox/mailbox.h"
#include "./constant/tag.h"


void main()
{
    // set up serial console
    uart_init();
    printWelcomeMsg();
    while(1) {
        if(isUartSetUp) {
            uart_setup(); // if user setup the uart, it will reset the old one.
        }
        typeCommand();
    }
}