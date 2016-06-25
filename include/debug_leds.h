#ifndef DEBUG_LEDS_H
#define DEBUG_LEDS_H

#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/rcc.h>

#include "systick_handler.h"

typedef uint16_t DebugLed;
static const DebugLed DEBUG_GREEN_LED =		GPIO12;
static const DebugLed DEBUG_ORANGE_LED =	GPIO13;
static const DebugLed DEBUG_RED_LED =		GPIO14;
static const DebugLed DEBUG_BLUE_LED =		GPIO15;
static const DebugLed DEBUG_ALL_LEDS =		GPIO12 | GPIO13 | GPIO14 | GPIO15;

static DebugLed heartbeat_led;

void SetupDebugLeds(void);
void SetHeartbeatLed(DebugLed color);
void Beat(void);
void SetDebugLed(DebugLed color);
void ClearDebugLed(DebugLed color);
void ToggleDebugLed(DebugLed color);

#endif