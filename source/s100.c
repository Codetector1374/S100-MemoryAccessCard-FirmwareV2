#include "s100.h"
#include <stdint.h>

static uint8_t has_bus = 0;

void s100_aquire_bus(void)
{
    // Become Bus Master
    palClearLine(CCDSB);
    palClearLine(SDSB);
    palClearLine(ADSB);
    palClearLine(DODSB);

    chThdSleepMilliseconds(1);

    // Enable Bus Output
    palClearLine(AO_OE);
    palClearLine(DO_OE);

    // Update Status
    has_bus = 1;
    palSetLine(LED_GREEN);
}

void s100_release_bus(void)
{
    // Disable Bus Outputs
    palSetLine(AO_OE);
    palSetLine(DO_OE);
    palSetLine(P_WRITE);

    chThdSleepMilliseconds(1);

    // Release Bus Control
    palSetLine(CCDSB);
    palSetLine(SDSB);
    palSetLine(ADSB);
    palSetLine(DODSB);

    has_bus = 0;
    palClearLine(LED_GREEN);
    chThdSleepMilliseconds(1);
}

void s100_set_address(uint16_t address)
{
    palClearLine(AO_CLK);
    palClearLine(AO_LATCH);

    for (int8_t i = 15; i >= 0; i--)
    {
        if ((address >> i) & 0x1)
            palSetLine(AO_DATA);
        else
            palClearLine(AO_DATA);

        palSetLine(AO_CLK);
        palClearLine(AO_CLK);
    }

    palSetLine(AO_LATCH);
    palClearLine(AO_LATCH);
}

void s100_write_data(uint8_t data)
{
    palClearLine(DO_CLK);
    palClearLine(DO_LATCH);

    for (int8_t i = 7; i >= 0; i--)
    {
        if ((data >> i) & 0x1)
            palSetLine(DO_DATA);
        else
            palClearLine(DO_DATA);

        palSetLine(DO_CLK);
        palClearLine(DO_CLK);
    }

    palSetLine(DO_LATCH);
    palClearLine(DO_LATCH);
}
