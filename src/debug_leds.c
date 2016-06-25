#include "debug_leds.h"

void SetupDebugLeds(void)
{
	heartbeat_led = DEBUG_RED_LED;

	rcc_periph_clock_enable(RCC_GPIOD);
	gpio_mode_setup(GPIOD, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, DEBUG_ALL_LEDS);

	// Setup heartbeat
	AddSystickCallback(Beat, 1000);
}

// Heartbeat function
void Beat(void)
{
	gpio_toggle(GPIOD, heartbeat_led);
}

void SetHeartbeatLed(DebugLed color)
{
	heartbeat_led = color;
}

void SetDebugLed(DebugLed color)
{
	gpio_set(GPIOD, color);
}

void ClearDebugLed(DebugLed color)
{
	gpio_clear(GPIOD, color);
}

void ToggleDebugLed(DebugLed color)
{
	gpio_toggle(GPIOD, color);
}
