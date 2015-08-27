/**
 * @file timing.h
 * @brief  Header for timer functions
 * @author Kristoffer Ödmark
 * @version 0.1
 * @date 2015-08-27
 */

#include    "ch.h"
#include    "hal.h"
#include    "stdint.h"

typedef struct{
        time_measurement_t timer;
        uint32_t accumulated_time;
}my_timer_t;

void init_timer(my_timer_t *timer);
void start_timer(my_timer_t *timer);
uint32_t get_timer_us(my_timer_t *timer);
uint32_t stop_timer(my_timer_t *timer);

