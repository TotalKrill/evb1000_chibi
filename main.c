
#include "ch.h"
#include "hal.h"
#include "usb_related.h"
#include "dw1000_hal.h"
#include "dw1000_lld.h"
#include "dw1000_reg.h"
#include "dw1000.h"
#include "exti.h"
#include "dw1000_ranging.h"
#include "timer.h"


#include "chprintf.h"
#include "debug_print.h"
extern BaseSequentialStream debug_print;
extern SerialUSBDriver SDU1;

#define printf(...) chprintf(&debug_print, __VA_ARGS__)

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

uint16_t counter[12];

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

    palClearPad(GPIOA, GPIOA_PIN0);
    chThdSleepMilliseconds(20000);
    palSetPad(GPIOA, GPIOA_PIN0);
    //enable interrupt
    extStart(&EXTD1, &extcfg);

    // start thread to be activated by interrupt.
    start_thd();

    uint8_t rxbuf[4];
    dw1000_conf_t config;
#ifdef SENDER
    config.shortaddr[0] = 0x5E;
    config.shortaddr[1] = 0x40;
#else
    config.shortaddr[0] = 0x8E;
    config.shortaddr[1] = 0xC1;
#endif


    dw.state = UNINITIALIZED;


    dw1000_generate_recommended_conf(
            &default_dw1000_hal,
            DW1000_DATARATE_850,
            DW1000_CHANNEL_2,
            1,
            &config);

    dw.config = &config;

    dw1000_init(&dw);


    //dw.receive(&dw,0);
    // clear interrupts
    uint32_t zero = \
                    DW1000_EVENT_TXFRS | \
                    DW1000_EVENT_RXFCG | \
                    DW1000_EVENT_RXFCE | \
                    DW1000_EVENT_AFFREJ | \
                    DW1000_EVENT_RXPHE | \
                    DW1000_EVENT_LDEERR | \
                    DW1000_EVENT_HPDWARN | \
                    DW1000_EVENT_RXDFR | \
                    DW1000_EVENT_TXBERR \
                    ;

    //dw1000_set_interrupts(&default_dw1000_hal,zero);

    dw1000_receive(&dw);
    bool sender = false;

    if(palReadPad(GPIOC, GPIOC_PIN5) == PAL_HIGH){
        sender = true;
        //set_ranging_callback(calibration_cb);
        palSetPad(GPIOC, GPIOC_PIN8);
    }
    else{
        palClearPad(GPIOC, GPIOC_PIN8);
    }


    int per_loop =0;

    while(1)
    {
        //palTogglePad(GPIOC, GPIOC_PIN8);

        chThdSleepMilliseconds(4000);
        uint8_t dst[2] = {0xBE,0xEF};
        if(sender){
            request_ranging(&dw, dst);
        }

        dw1000_get_event_counters(&default_dw1000_hal, counter);
        if (per_loop == 100){
            per_loop = 0;
            printf("    PHR_ERRORS:    %u \n\r", counter[PHR_ERRORS]);
            printf("    RSD_ERRORS:    %u \n\r", counter[RSD_ERRORS]);
            printf("    FCS_GOOD:      %u \n\r", counter[FCS_GOOD]);
            printf("    FCS_ERRORS:    %u \n\r", counter[FCS_ERRORS]);
            printf("    FILTER_REJ:    %u \n\r", counter[FILTER_REJECTIONS]);
            printf("    RX_OVERRUNS:   %u \n\r", counter[RX_OVERRUNS]);
            printf("    SFD_TO:        %u \n\r", counter[SFD_TIMEOUTS]);
            printf("    PREAMBLE_TO:   %u \n\r", counter[PREAMBLE_TIMEOUTS]);
            printf("    RX_TIMEOUTS:   %u \n\r", counter[RX_TIMEOUTS]);
            printf("    TX_SENT:       %u \n\r", counter[TX_SENT]);
            printf("    HPWARN:        %u \n\r", counter[HALF_PERIOD_WARNINGS]);
            printf("    TX_PWRUP_WARN: %u \n\r", counter[TX_PWRUP_WARNINGS]);
        }
        per_loop++;


    }

}
