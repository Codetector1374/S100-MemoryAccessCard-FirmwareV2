/*
    ChibiOS - Copyright (C) 2006..2018 Giovanni Di Sirio

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
 * Board identifier.
 */
#define BOARD_NAME              "S100 Memory Programmer"

/*
 * Board frequencies.
 */
#define STM32_HSECLK            8000000

/*
 * MCU type, supported types are defined in ./os/hal/platforms/hal_lld.h.
 */
#define STM32F103xB

/*
 * IO pins assignments
 *
 * numbering is sorted by onboard/connectors, as from the schematics in
 * https://github.com/leaflabs/maplemini
 */

/* on-board */

#define LED_GREEN               PAL_LINE(GPIOA, 0 )
#define LED_RED                 PAL_LINE(GPIOB, 0 )
#define LED_YELLOW              PAL_LINE(GPIOB, 1 )

// Disable Lines
#define CCDSB                   PAL_LINE(GPIOB, 8 )
#define SDSB                    PAL_LINE(GPIOB, 9 )
#define ADSB                    PAL_LINE(GPIOB, 10)
#define DODSB                   PAL_LINE(GPIOB, 11)

// ADDR OUTPUT Control
#define AO_DATA         PAL_LINE(GPIOA, 1)
#define AO_CLK          PAL_LINE(GPIOA, 2)
#define AO_LATCH        PAL_LINE(GPIOA, 3)
#define AO_OE           PAL_LINE(GPIOA, 4) // Active Low

// Data Out
#define DO_DATA     PAL_LINE(GPIOA, 5)
#define DO_CLK      PAL_LINE(GPIOA, 6)
#define DO_LATCH    PAL_LINE(GPIOA, 7)
#define DO_OE       PAL_LINE(GPIOA, 8) // Active Low

#define P_WRITE     PAL_LINE(GPIOB, 12) // Active Low

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

/*
 * Port A setup.
 * Everything input with pull-up except:
 * PA2  - Alternate output  (USART2 TX).
 * PA3  - Normal input      (USART2 RX).
 * PA9  - Alternate output  (USART1 TX).
 * PA10 - Normal input      (USART1 RX).
 */
#define VAL_GPIOACRL            0x33333333      /*  PA7...PA0 */
#define VAL_GPIOACRH            0x844444B3      /* PA15...PA8 */
#define VAL_GPIOAODR            0x00000000

/*
 * Port B setup.
 * Everything input with pull-up except:
 * PB1    - Push Pull output  (LED).
 * PB9    - Push Pull output  (USB switch).
 */
#define VAL_GPIOBCRL            0x88888833      /*  PB7...PB0 */
#define VAL_GPIOBCRH            0x88877747      /* PB15...PB8 */
#define VAL_GPIOBODR            0xFFFFFFFC

/*
 * Port C setup.
 * Everything input with pull-up except:
 */
#define VAL_GPIOCCRL            0x88888888      /*  PC7...PC0 */
#define VAL_GPIOCCRH            0x88888888      /* PC15...PC8 */
#define VAL_GPIOCODR            0xFFFFFFFF

/*
 * Port D setup.
 * Everything input with pull-up except:
 * PD0  - Normal input (XTAL).
 * PD1  - Normal input (XTAL).
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
