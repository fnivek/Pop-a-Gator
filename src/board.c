#include "board.h"

// Heartbeat function
void beat(void)
{
	gpio_toggle(GPIOD, GPIO14);
}

void setup_board(void)
{
	// Setup clock
	rcc_clock_setup_hse_3v3(&rcc_hse_8mhz_3v3[RCC_CLOCK_3V3_168MHZ]);

	// TODO: Make a debug .h and .c
	rcc_periph_clock_enable(RCC_GPIOD);
	gpio_mode_setup(GPIOD, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO12 | GPIO13 | GPIO14 | GPIO15);
	
	// Setup USB
	setup_usb();

	// Setup Bluetooth
	setup_bluetooth();

	// Start system tic
	systick_setup();

	// Setup heartbeat
	add_systick_callback(beat, 1000);
}