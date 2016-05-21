#ifndef BLUETOOTH_H
#define BLUETOOTH_H

#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/usart.h>
#include <libopencm3/stm32/rcc.h>

#include "systick_handler.h"

void setup_bluetooth(void);

uint16_t read_bluetooth(uint32_t timeout);

void write_bluetooth(uint16_t data);

void flush_bluetooth_input(void);
#endif