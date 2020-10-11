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

#include <stdio.h>
#include <string.h>

#include "ch.h"
#include "hal.h"
#include "s100.h"
#include "intel_hex.h"


static char iHexBuffer[550] = {};
static size_t iHexBufferIndex = 0;

static uint8_t dataBuffer[256] = {};

/*===========================================================================*/
/* Generic code.                                                             */
/*===========================================================================*/

void executeiHexRecord(void) {

  IHEX_STS status;
  IHEX_TYPE recordType;
  uint8_t filled = 0;
  uint16_t base = 0;

  status = parseiHex
  (
    iHexBuffer, iHexBufferIndex,
    dataBuffer, &filled,
    &base, &recordType
  );

  s100_aquire_bus();

  for (uint16_t i = 0; i < filled; ++i)
  {
    s100_set_address(base + i);
    s100_write_data(dataBuffer[i]);
    palClearLine(P_WRITE);
    chThdSleepMilliseconds(1);
    palSetLine(P_WRITE);
  }

  s100_release_bus();

  sdPut(&SD1, status);
}

/*
 * Blinker thread, times are in milliseconds.
 */
static THD_WORKING_AREA(waThread1, 256);
static __attribute__((noreturn)) THD_FUNCTION(Thread1, arg) {

  (void)arg;
  chRegSetThreadName("iHEX");
  char token;
  uint8_t isRecording = false;
  while (true) {
    token = sdGet(&SD1);
    switch(token) {
      case '\r':
        break;
      case '\n':
        if (isRecording) {
          isRecording = false;
          executeiHexRecord();
        }
        break;
      case ':':
        isRecording = true;
        iHexBufferIndex = 0;
        // fall through
      default:
        if (isRecording) {
          if (iHexBufferIndex < 550)
            iHexBuffer[iHexBufferIndex++] = token;
        }
        break;
    }

  }
}

/*
 * Application entry point.
 */
int main(void) {

  /*
   * System initializations.
   * - HAL initialization, this also initializes the configured device drivers
   *   and performs the board-specific initializations.
   * - Kernel initialization, the main() function becomes a thread and the
   *   RTOS is active.
   */
  halInit();
  chSysInit();

  sdStart(&SD1, NULL);

  // Disable Output of ShiftRegisters
  palSetLine(AO_OE);
  palSetLine(DO_OE);
  s100_release_bus();

  /*
   * Creates the iHEX thread.
   */
  chThdCreateStatic(waThread1, sizeof(waThread1), NORMALPRIO, Thread1, NULL);

  /*
   * Normal main() thread activity, spawning shells.
   */
  while (true) {
    chThdSleepMilliseconds(1000);
  }
}
