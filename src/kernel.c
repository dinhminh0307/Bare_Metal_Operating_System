#include "./cli/cli.h"

#include "./mailbox/mailbox.h"
#include "./constant/tag.h"
#include "./constant/font.h"


void view_firmware_revision(void) {
    // mailbox data buffer: Read ARM frequency
    mBuf[0] = 7*4; // Message Buffer Size in bytes (8 elements * 4 bytes (32 bit) each)
    mBuf[1] = MBOX_REQUEST; // Message Request Code (this is a request message)
    mBuf[2] = FIRMWARE_REVISION; // TAG Identifier: Get firmware revision command,
    mBuf[3] = 4; // Value buffer size in bytes (max of request and response lengths)
    mBuf[4] = 0; // REQUEST CODE = 0
    mBuf[5] = 0; // clear value buffer
    mBuf[6] = MBOX_TAG_LAST;
    if (mbox_call(ADDR(mBuf), MBOX_CH_PROP)) {
        uart_puts("Response Code for whole message: ");
        uart_hex(mBuf[1]);
        uart_puts("\n");
        uart_puts("Response Code in Message TAG: ");
        uart_hex(mBuf[4]);
        uart_puts("\n");
        uart_puts("DATA: Firmware revision = ");
        uart_hex(mBuf[5]);
        uart_puts("\n");
    } else {
        uart_puts("Unable to query!\n");
    }
}

void view_all_buffer_request(void) {
    // mailbox data buffer: Read ARM frequency
    mBuf[0] = 8*4; // Message Buffer Size in bytes (8 elements * 4 bytes (32 bit) each)
    mBuf[1] = MBOX_REQUEST; // Message Request Code (this is a request message)
    mBuf[2] = UART_CLOCK; // TAG Identifier: Get uart clock command,
    mBuf[3] = 8; // Value buffer size in bytes (max of request and response lengths)
    mBuf[4] = 0; // REQUEST CODE = 0
    mBuf[5] = 3; // clear output buffer (response data are mBuf[5] & mBuf[6])
    mBuf[6] = 0; // clear output buffer (response data are mBuf[5] & mBuf[6])
    mBuf[7] = MBOX_TAG_LAST;
    if (mbox_call(ADDR(mBuf), MBOX_CH_PROP)) {
        uart_puts("Response Code for whole message: ");
        uart_hex(mBuf[1]);
        uart_puts("\n");
        uart_puts("Response Code in Message TAG: ");
        uart_hex(mBuf[4]);
        uart_puts("\n");
        uart_puts("DATA:  ARM clock rate = ");
        uart_dec(mBuf[5]);
        uart_puts("\n");
    } else {
        uart_puts("Unable to query!\n");
    }
}

void uart_clock_request(void) {
    // mailbox data buffer: Read ARM frequency
    mBuf[0] = 8*4; // Message Buffer Size in bytes (8 elements * 4 bytes (32 bit) each)
    mBuf[1] = MBOX_REQUEST; // Message Request Code (this is a request message)
    mBuf[2] = 0x00030002; // TAG Identifier: Get clock rate
    mBuf[3] = 8; // Value buffer size in bytes (max of request and response lengths)
    mBuf[4] = 0; // REQUEST CODE = 0
    mBuf[5] = 0x000000002; // clock id: UART clock
    mBuf[6] = 0; // clear output buffer (response data are mBuf[5] & mBuf[6])

    //... more tag
    mBuf[7] = MBOX_TAG_LAST; // end tage
    if (mbox_call(ADDR(mBuf), MBOX_CH_PROP)) {
        uart_puts("Response Code for whole message: ");
        uart_hex(mBuf[1]);
        uart_puts("\n");
        uart_puts("Response Code in Message TAG: ");
        uart_hex(mBuf[4]);
        uart_puts("\n");
        uart_puts("DATA: ARM clock rate = ");
        uart_dec(mBuf[6]);
        uart_puts("\n");
    } else {
        uart_puts("Unable to query!\n");
    }
}

void view_board_model(void) {
    // mailbox data buffer: Read ARM frequency
    mBuf[0] = 8*4; // Message Buffer Size in bytes (8 elements * 4 bytes (32 bit) each)
    mBuf[1] = MBOX_REQUEST; // Message Request Code (this is a request message)
    mBuf[2] = BOARD_MODEL; // TAG Identifier: view board model
    mBuf[3] = 4; // Value buffer size in bytes (max of request and response lengths)
    mBuf[4] = 0; // REQUEST CODE = 0
    mBuf[5] = 0; // clear output buffer (response data are mBuf[5] & mBuf[6])
    mBuf[6] = MBOX_TAG_LAST; // end tage
    if (mbox_call(ADDR(mBuf), MBOX_CH_PROP)) {
        uart_puts("Response Code for whole message: ");
        uart_hex(mBuf[1]);
        uart_puts("\n");
        uart_puts("Response Code in Message TAG: ");
        uart_hex(mBuf[4]);
        uart_puts("\n");
        uart_puts("DATA: Board Model info = ");
        uart_dec(mBuf[5]);
        uart_puts("\n");
    } else {
        uart_puts("Unable to query!\n");
    }
}

void view_board_revision(void) {
    mBuf[0] = 7*4; // Message Buffer Size in bytes (8 elements * 4 bytes (32 bit) each)
    mBuf[1] = MBOX_REQUEST; // Message Request Code (this is a request message)
    mBuf[2] = BOARD_REVISION_TAG; // TAG Identifier: Get uart clock command,
    mBuf[3] = 4; // Value buffer size in bytes (max of request and response lengths)
    mBuf[4] = 0; // REQUEST CODE = 0
    mBuf[5] = 0; // clear output buffer (response data are mBuf[5] & mBuf[6])
    mBuf[6] = MBOX_TAG_LAST;
     if (mbox_call(ADDR(mBuf), MBOX_CH_PROP)) {
        // uart_puts("Response Code for whole message: ");
        // uart_hex(mBuf[1]);
        // uart_puts("\n");
        // uart_puts("Response Code in Message TAG: ");
        // uart_hex(mBuf[4]);
        // uart_puts("\n");
        uart_puts("DATA: Board Revision Info = ");
        uart_dec(mBuf[5]);
        uart_puts("\n");
    } else {
        uart_puts("Unable to query!\n");
    }
}

void main()
{
    // set up serial console
    uart_init();
    printWelcomeMsg(hexArray);
    while(1) {
        typeCommand();
    }
}