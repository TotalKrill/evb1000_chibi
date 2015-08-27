/**
 * @file timing.c
 *
 * @brief  Timer module
 * @author Kristoffer Ödmark
 * @version 0.1
 * @date 2015-08-27
 */
#include    "timing.h"



void init_timer(my_timer_t *timer){
    chTMObjectInit(timer->tm);
    timer->accumulated_time = 0;
}

void start_timer(my_timer_t *timer){
    chTMStartMeasurementX(timer->tm);
}

uint32_t get_timer_us(my_timer_t *timer){

    chTMStopMeasurementX(timer->tm);
    /* Some macro to extract the time in us*/
    uint32_t dt = RTC2US(STM32_SYSCLK, timer->tm.last);
    /* append time to the accumulated value */
    timer->accumulated_time += dt;

    chTMStartMeasurementX(timer->tm);

    return timer->accumulated_time;
}

uint32_t stop_timer(my_timer_t *timer){
    chTMStopMeasurementX(timer->tm);
    /* Some macro to extract the time */
    uint32_t dt = RTC2US(STM32_SYSCLK, timer->tm.last);
    timer->accumulated_time += dt;

    return timer->accumulated_time;
}
