#include "exti.h"
#include "ch.h"
#include "dw1000.h"

extern dw1000_driver_t dw;

static THD_WORKING_AREA(mythreadwa,512);
static thread_reference_t *trp = NULL;


THD_FUNCTION(myThread, arg) {

  while (true) {
    msg_t msg;

    /* Waiting for the IRQ to happen.*/
    chSysLock();
    msg = chThdSuspendS(&trp);
    chSysUnlock();

    /* Perform processing here.*/
    dw1000_irq_event(&dw);
  }
}

void start_thd(void){

    (void)chThdCreateStatic(mythreadwa, sizeof(mythreadwa),
                          NORMALPRIO, myThread, NULL);
}


/* Triggered when the button is pressed or released. The LED is set to ON.*/
void extcb1(EXTDriver *extp, expchannel_t channel) {
  (void)extp;
  (void)channel;
  chSysLockFromISR();
  chThdResumeI(&trp, (msg_t)0x1337);  /* Resuming the thread with message.*/
  chSysUnlockFromISR();
}

