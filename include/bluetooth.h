#ifndef BLUETOOTH_H
#define BLUETOOTH_H

#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/usart.h>
#include <libopencm3/stm32/rcc.h>

#include "systick_handler.h"

void SetupBluetooth(void);

uint16_t ReadBluetooth(uint32_t timeout);

void WriteBluetooth(uint16_t data);

void FlushBluetoothInput(void);
#endif