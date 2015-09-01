/*
    ChibiOS - Copyright (C) 2006..2015 Giovanni Di Sirio

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
*/

#ifndef _BOARD_H_
#define _BOARD_H_

/*
 * Setup for the ST INEMO-M1 Discovery board.
 */

/*
 * Board identifier.
 */
#define BOARD_NAME              "EVB1000"

/*
 * Board frequencies.
 */
#define STM32_LSECLK            0

#define STM32_HSECLK            12000000

/*
 * MCU type, supported types are defined in ./os/hal/platforms/hal_lld.h.
 */
#define STM32F10X_CL

/*
 * IO pins assignments.
 */
#define GPIOA_PIN0              0
#define GPIOA_PIN1              1
#define GPIOA_PIN2              2
#define GPIOA_PIN3              3
#define GPIOA_PIN4              4
#define GPIOA_PIN5              5
#define GPIOA_PIN6              6
#define GPIOA_PIN7              7
#define GPIOA_PIN8              8
#define GPIOA_PIN9              9
#define GPIOA_PIN10              10
#define GPIOA_PIN11              11
#define GPIOA_PIN12              12
#define GPIOA_PIN13              13
#define GPIOA_PIN14              14
#define GPIOA_PIN15              15

#define GPIOB_PIN0              0
#define GPIOB_PIN1              1
#define GPIOB_PIN2              2
#define GPIOB_PIN3              3
#define GPIOB_PIN4              4
#define GPIOB_PIN5              5
#define GPIOB_PIN6              6
#define GPIOB_PIN7              7
#define GPIOB_PIN8              8
#define GPIOB_PIN9              9
#define GPIOB_PIN10              10
#define GPIOB_PIN11              11
#define GPIOB_PIN12              12
#define GPIOB_PIN13              13
#define GPIOB_PIN14              14
#define GPIOB_PIN15              15

#define GPIOC_PIN0              0
#define GPIOC_PIN1              1
#define GPIOC_PIN2              2
#define GPIOC_PIN3              3
#define GPIOC_PIN4              4
#define GPIOC_PIN5              5
#define GPIOC_PIN6              6
#define GPIOC_PIN7              7
#define GPIOC_PIN8              8
#define GPIOC_PIN9              9
#define GPIOC_PIN10              10
#define GPIOC_PIN11              11
#define GPIOC_PIN12              12
#define GPIOC_PIN13              13
#define GPIOC_PIN14              14
#define GPIOC_PIN15              15

#define GPIOD_OSC_IN            0
#define GPIOD_OSC_OUT           1
#define GPIOD_PD2               2

/*
 * I/O ports initial setup, this configuration is established soon after reset
 * in the initialization code.
 *
 * The digits have the following meaning:
 *   0 - Analog input.
 *   1 - Push Pull output 10MHz.
 *   2 - Push Pull output 2MHz.
 *   3 - Push Pull output 50MHz.
 *   4 - Digital input.
 *   5 - Open Drain output 10MHz.
 *   6 - Open Drain output 2MHz.
 *   7 - Open Drain output 50MHz.
 *   8 - Digital input with PullUp or PullDown resistor depending on ODR.
 *   9 - Alternate Push Pull output 10MHz.
 *   A - Alternate Push Pull output 2MHz.
 *   B - Alternate Push Pull output 50MHz.
 *   C - Reserved.
 *   D - Alternate Open Drain output 10MHz.
 *   E - Alternate Open Drain output 2MHz.
 *   F - Alternate Open Drain output 50MHz.
 * Please refer to the STM32 Reference Manual for details.
 */

#define PIN_MODE_OUTPUT_2M          0x2
#define PIN_MODE_OUTPUT_10M         0x1
#define PIN_MODE_OUTPUT_50M         0x3
#define PIN_MODE_INPUT              0x0

#define PIN_CONF_IN_ANALOG          0b0000
#define PIN_CONF_IN_FLOATING        0b0100
#define PIN_CONF_IN_PULLUP_PULLDOWN 0b1000

#define PIN_CONF_OUT_PUSH_PULL      0b0000
#define PIN_CONF_OUT_OPEN_DRAIN     0b0100
#define PIN_CONF_OUT_AF_PUSH_PULL   0b1000
#define PIN_CONF_OUT_AF_OPEN_DRAIN  0b1100

#define PINCONFIG(pin, mode, conf)          (((mode) + (conf)) << ((pin) * 4U))
#define PINCONFIGH(pin, mode, conf)          (((mode) + (conf)) << (((pin) - 8) * 4U))

/*
 * Port A setup.
 * Everything input with pull-up except:
 * PA2  - Alternate output          (GPIOA_USART_TX).
 * PA3  - Normal input              (GPIOA_USART_RX).
 * PA5  - Push Pull output          (GPIOA_LED_GREEN).
 * PA13 - Pull-up input             (GPIOA_SWDIO).
 * PA14 - Pull-down input           (GPIOA_SWCLK).
 */
#define VAL_GPIOACRL            \
    ( PINCONFIG(GPIOA_PIN0, PIN_MODE_OUTPUT_50M, PIN_CONF_OUT_OPEN_DRAIN) | \
    PINCONFIG(GPIOA_PIN1, PIN_MODE_INPUT, PIN_CONF_IN_PULLUP_PULLDOWN) | \
    PINCONFIG(GPIOA_PIN2, PIN_MODE_INPUT, PIN_CONF_IN_PULLUP_PULLDOWN) | \
    PINCONFIG(GPIOA_PIN3, PIN_MODE_INPUT, PIN_CONF_IN_PULLUP_PULLDOWN) | \
    PINCONFIG(GPIOA_PIN4, PIN_MODE_OUTPUT_50M, PIN_CONF_OUT_AF_PUSH_PULL) | \
    PINCONFIG(GPIOA_PIN5, PIN_MODE_OUTPUT_50M, PIN_CONF_OUT_AF_PUSH_PULL) | \
    PINCONFIG(GPIOA_PIN6, PIN_MODE_INPUT, PIN_CONF_IN_FLOATING) | \
    PINCONFIG(GPIOA_PIN7 ,PIN_MODE_OUTPUT_50M, PIN_CONF_OUT_AF_PUSH_PULL))
#define VAL_GPIOACRH            0x88888888      /* PA15...PA8 */
#define VAL_GPIOAODR            0xFFFFBFDF

/*
 * Port B setup.
 * Everything input with pull-up except:
 * PB3  - Pull-up input             (GPIOA_SWO).
 */
#define VAL_GPIOBCRL            0x88888888      /*  PB7...PB0 */
#define VAL_GPIOBCRH            0x88888888      /* PB15...PB8 */
#define VAL_GPIOBODR            0xFFFFFFFF

/*
 * Port C setup.
 * Everything input with pull-up except:
 * PC13 - Normal input              (GPIOC_BUTTON).
 */
#define VAL_GPIOCODR            0xFFFFFFFF
/*
 * Define the lower pins of GPIOC
 */
#define VAL_GPIOCCRL            \
    ( PINCONFIG(GPIOC_PIN0, PIN_MODE_INPUT, PIN_CONF_IN_PULLUP_PULLDOWN) | \
    PINCONFIG(GPIOC_PIN1, PIN_MODE_INPUT, PIN_CONF_IN_PULLUP_PULLDOWN) | \
    PINCONFIG(GPIOC_PIN2, PIN_MODE_INPUT, PIN_CONF_IN_PULLUP_PULLDOWN) | \
    PINCONFIG(GPIOC_PIN3, PIN_MODE_INPUT, PIN_CONF_IN_PULLUP_PULLDOWN) | \
    PINCONFIG(GPIOC_PIN4, PIN_MODE_INPUT, PIN_CONF_IN_PULLUP_PULLDOWN) | \
    PINCONFIG(GPIOC_PIN5, PIN_MODE_INPUT, PIN_CONF_IN_PULLUP_PULLDOWN) | \
    PINCONFIG(GPIOC_PIN6, PIN_MODE_OUTPUT_2M, PIN_CONF_OUT_PUSH_PULL) | \
    PINCONFIG(GPIOC_PIN7 ,PIN_MODE_OUTPUT_2M, PIN_CONF_OUT_PUSH_PULL))
/*
 * Define the higher pins of GPIOC
 */
#define VAL_GPIOCCRH            \
    ( PINCONFIGH(GPIOC_PIN8, PIN_MODE_OUTPUT_2M, PIN_CONF_OUT_PUSH_PULL ) | \
    PINCONFIGH(GPIOC_PIN9, PIN_MODE_OUTPUT_2M, PIN_CONF_OUT_PUSH_PULL) | \
    PINCONFIGH(GPIOC_PIN10, PIN_MODE_INPUT, PIN_CONF_IN_PULLUP_PULLDOWN) | \
    PINCONFIGH(GPIOC_PIN11, PIN_MODE_INPUT, PIN_CONF_IN_PULLUP_PULLDOWN) | \
    PINCONFIGH(GPIOC_PIN12, PIN_MODE_INPUT, PIN_CONF_IN_PULLUP_PULLDOWN) | \
    PINCONFIGH(GPIOC_PIN13, PIN_MODE_INPUT, PIN_CONF_IN_PULLUP_PULLDOWN) | \
    PINCONFIGH(GPIOC_PIN14, PIN_MODE_OUTPUT_2M, PIN_CONF_OUT_PUSH_PULL) | \
    PINCONFIGH(GPIOC_PIN15 ,PIN_MODE_INPUT, PIN_CONF_IN_PULLUP_PULLDOWN))

/*
 * Port D setup.
 * Everything input with pull-up except:
 * PD0  - Normal input              (GPIOD_OSC_IN).
 * PD1  - Normal input              (GPIOD_OSC_OUT).
 */
#define VAL_GPIODCRL            0x88888844      /*  PD7...PD0 */
#define VAL_GPIODCRH            0x88888888      /* PD15...PD8 */
#define VAL_GPIODODR            0xFFFFFFFF

/*
 * Port E setup.
 * Everything input with pull-up except:
 */
#define VAL_GPIOECRL            0x88888888      /*  PE7...PE0 */
#define VAL_GPIOECRH            0x88888888      /* PE15...PE8 */
#define VAL_GPIOEODR            0xFFFFFFFF

/*
 * USB bus activation macro, required by the USB driver.
 */

/*
 * USB bus de-activation macro, required by the USB driver.
 */

#if !defined(_FROM_ASM_)
#ifdef __cplusplus
extern "C" {
#endif
  void boardInit(void);
#ifdef __cplusplus
}
#endif
#endif /* _FROM_ASM_ */

#endif /* _BOARD_H_ */
