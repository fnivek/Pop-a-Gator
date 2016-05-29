#ifndef DEBUG_LEDS_H
#define DEBUG_LEDS_H

#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/rcc.h>

#include "systick_handler.h"

typedef uint16_t debug_led;
static const debug_led DEBUG_GREEN_LED =	GPIO12;
static const debug_led DEBUG_ORANGE_LED =	GPIO13;
static const debug_led DEBUG_RED_LED =		GPIO14;
static const debug_led DEBUG_BLUE_LED =		GPIO15;
static const debug_led DEBUG_ALL_LEDS =		GPIO12 | GPIO13 | GPIO14 | GPIO15;

static debug_led heartbeat_led;

void setup_debug_leds(void);
void set_heartbeat_led(debug_led color);
void beat(void);
void set_debug_led(debug_led color);
void clear_debug_led(debug_led color);
void toggle_debug_led(debug_led color);

#endif