#ifndef BLUETOOTH_H
#define BLUETOOTH_H

#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/usart.h>
#include <libopencm3/stm32/rcc.h>
#include <libopencm3/cm3/nvic.h>

#include "systick_handler.h"

void SetupBluetooth(void);

uint16_t BluetoothReadBlocking(uint32_t timeout);

uint16_t BluetoothRead(void);

void BluetoothWrite(uint16_t data);

void BluetoothFlushInput(void);

void BluetoothAddCb(void (*callback)(void));

void usart2_isr(void);
#endif