#pragma once

#include "ch.h"
#include "hal.h"

void s100_aquire_bus(void);
void s100_release_bus(void);

void s100_set_address(uint16_t address);
void s100_write_data(uint8_t data);
