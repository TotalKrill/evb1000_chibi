#include "ch.h"
#include "hal.h"
#include "dw1000_hal.h"
#include "dw1000_lld.h"
#include "dw1000_reg.h"
#include "dw1000.h"
#include "exti.h"
//#include "system_init.h"
//#include "bootloader.h"

/**
 * @brief Placeholder for error messages.
 */
volatile assert_errors kfly_assert_errors;

extern dw1000_hal_t default_dw1000_hal;
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
            DW1000_CHANNEL_7,
            1,
            &config);

    dw.config = &config;

    dw.init(&dw);

    //default_dw1000_hal.init(&default_dw1000_hal);
    //dw1000_softreset(&default_dw1000_hal);
    //dw1000_set_interrupts(&default_dw1000_hal, 0xFFFFFFFF );

    volatile uint32_t p = 0;

    //dw.receive(&dw,0);
    // clear interrupts
    uint32_t zero =0xFFFFFFFE;
    //dw1000_write_register( &default_dw1000_hal, DW1000_REG_SYS_STATUS, 4, (uint8_t*)&zero);
    uint8_t payload[10] =  {0xDE,
                            0xCA,
                            0xDE,
                            0xAD,
                            0xBE,
                            0xEF,
                            0xC0,
                            0xCA,
                            0x09,
                            0x0a
    };
    dw1000_msg_t message;
    message.length = 10;
    message.payload = payload;
    dw.receive(&dw,0);
    while(1)
    {

        palTogglePad(GPIOC, GPIOC_PIN8);
        //dw1000_set_preamble_length(&default_dw1000_hal, DW1000_PREAMBLE_LENGTH_512);
        //works
        //dw1000_set_preamble_code(&default_dw1000_hal,DW1000_PREAMBLE_CODE_1); // works
        //dw1000_set_prf(&default_dw1000_hal,DW1000_PRF_64_MHZ); // works
        //dw1000_set_channel(&default_dw1000_hal,DW1000_CHANNEL_3); //works
        //dw1000_read_register(&default_dw1000_hal, DW1000_REG_SYS_STATUS,4,(uint8_t*)&p);

        //p = dw1000_get_dev_id(&default_dw1000_hal);


        chThdSleepMilliseconds(500);
        //dw.send(&dw, &message,0);

        //clear all the interrupts!!

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
