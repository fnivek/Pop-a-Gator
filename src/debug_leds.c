#include "debug_leds.h"

void setup_debug_leds(void)
{
	heartbeat_led = DEBUG_RED_LED;

	rcc_periph_clock_enable(RCC_GPIOD);
	gpio_mode_setup(GPIOD, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, DEBUG_ALL_LEDS);

	// Setup heartbeat
	add_systick_callback(beat, 1000);
}

// Heartbeat function
void beat(void)
{
	gpio_toggle(GPIOD, heartbeat_led);
}

void set_heartbeat_led(debug_led color)
{
	heartbeat_led = color;
}

void set_debug_led(debug_led color)
{
	gpio_set(GPIOD, color);
}

void clear_debug_led(debug_led color)
{
	gpio_clear(GPIOD, color);
}

void toggle_debug_led(debug_led color)
{
	gpio_toggle(GPIOD, color);
}
