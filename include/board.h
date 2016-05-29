#ifndef BOARD_H
#define BOARD_H

#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/rcc.h>

#include "usb.h"
#include "systick_handler.h"
#include "bluetooth.h"

void setup_board(void);
void beat(void);

#endif