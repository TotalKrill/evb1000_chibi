#include "ch.h"
#include "hal.h"
#include "usb_related.h"
#include "dw1000_hal.h"
#include "dw1000_lld.h"
#include "dw1000_reg.h"
#include "dw1000.h"
#include "exti.h"
#include "chprintf.h"
#include "dw1000_ranging.h"
#include "debug_print.h"
//#include "system_init.h"
//#include "bootloader.h"

/**
 * @brief Placeholder for error messages.
 */
volatile assert_errors kfly_assert_errors;

extern dw1000_hal_t default_dw1000_hal;
extern SerialUSBDriver SDU1;

extern BaseSequentialStream debug_print;
const EXTConfig extcfg = {
  {
    {EXT_CH_MODE_DISABLED, NULL},
    {EXT_CH_MODE_DISABLED, NULL},
    {EXT_CH_MODE_DISABLED, NULL},
    {EXT_CH_MODE_DISABLED, NULL},
    {EXT_CH_MODE_DISABLED, NULL},
    {EXT_CH_MODE_RISING_EDGE | EXT_CH_MODE_AUTOSTART | EXT_MODE_GPIOB, extcb1},
    {EXT_CH_MODE_DISABLED, NULL},
    {EXT_CH_MODE_DISABLED, NULL},
    {EXT_CH_MODE_DISABLED, NULL},
    {EXT_CH_MODE_DISABLED, NULL},
    {EXT_CH_MODE_DISABLED, NULL},
    {EXT_CH_MODE_DISABLED, NULL},
    {EXT_CH_MODE_DISABLED, NULL},
    {EXT_CH_MODE_DISABLED, NULL},
    {EXT_CH_MODE_DISABLED, NULL},
    {EXT_CH_MODE_DISABLED, NULL}
  }
};

dw1000_driver_t dw;

volatile uint8_t hej =0;

int main(void)
{
    /*
     * System initializations.
     * - HAL initialization, this also initializes the configured
     *   device drivers and performs the board-specific initializations.
     * - Kernel initialization, the main() function becomes a thread
     *   and the RTOS is active.
     */
    halInit();
    chSysInit();
    // enable interrupt
    usbstartup();

    //enable debug print thread
    vInitDebugPrint((BaseSequentialStream *) &SDU1);
    extStart(&EXTD1, &extcfg);

    /*
     *
     * Initialize all drivers and modules.
     *
     */
    //vSystemInit();

    /*
     *
     * Main task loop.
     *
     */
    //while(bSystemShutdownRequested() == false)
    uint8_t rxbuf[4];
    dw1000_conf_t config;

    dw.init = dw1000_init;
    dw.send = dw1000_send;
    dw.receive = dw1000_receive;
    dw.state = UNINITIALIZED;

    // start thread to be activated by interrupt.
    start_thd();

    dw1000_generate_recommended_conf(
            &default_dw1000_hal,
            DW1000_DATARATE_6800,
            DW1000_CHANNEL_2,
            1,
            &config);

    dw.config = &config;

    dw1000_init(&dw);

    volatile uint32_t p = 0;

    //dw.receive(&dw,0);
    // clear interrupts
    uint32_t zero = \
        DW1000_EVENT_TXFRS | \
        DW1000_EVENT_RXDFR \
        ;
   dw1000_set_interrupts(&default_dw1000_hal,zero);
    //dw1000_write_register( &default_dw1000_hal, DW1000_REG_SYS_STATUS, 4, (uint8_t*)&zero);
    uint8_t payload[50] =  {0xDE,
                            0xCA,
                            0xDE,
                            0xAD,
                            0xBE,
                            0xEF,
                            0xC0,
                            0xCE,
                            0x09,
                            0x00
    };
    dw1000_msg_t message;
    message.length = 50;
    message.payload = &payload;
    message.ranging = false;
    message.autoack = false;

//#define SENDER
#define RANGER

#ifndef SENDER
    dw1000_receive(&dw);
#endif
    while(1)
    {

        palTogglePad(GPIOC, GPIOC_PIN8);


        chThdSleepMilliseconds(500);
#ifdef SENDER
#ifndef RANGER
        dw1000_send(&dw, &message);
        payload[49]++;
#else
        uint8_t dst[2] = {0xBE,0xEF};
        request_ranging(&dw, dst);
#endif
#endif
        //clear all the interrupts!!
        //
        chprintf(&debug_print, "Debug printouts!!!\n\r");

    }

    /*
     *
     * Deinitialize all drivers and modules.
     *
     */
    //vSystemDeinit();

   /*
    *
    * All threads, drivers, interrupts and SysTick are now disabled.
    * The main function is now just a "normal" function again.
    *
    */

    /*
     *
     * Start the DFU bootloader.
     * This can be replaced if a custom bootloader is available.
     *
     */
    //vBootloaderResetAndStartDFU();

    /* In case of error get stuck here */
    while (1);
}
