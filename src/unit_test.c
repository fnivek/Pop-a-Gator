/*
 * This is the main file for the nordic interface
 */


#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/spi.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/usart.h>
#include <stdlib.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/usb/usbd.h>
#include <libopencm3/usb/cdc.h>
#include <libopencm3/cm3/scb.h>

#include "usb.h"
#include "systick_handler.h"
#include "bluetooth.h"

// Heartbeat function
void beat(void)
{
	gpio_toggle(GPIOD, GPIO15);
}

// Test the bluetooth module
int8_t test_bluetooth(void)
{
	// Clear read
	flush_bluetooth_input();

	usb_write_string("\n\rStart blue tooth test\n\r");
	write_bluetooth('A');
	write_bluetooth('T');
	usb_write_string("\n\rWrote AT\n\r");

	char buf[] = "BT replied w/: ##";
	
	usb_write_string("\n\rWait for some data\n\r");
	uint16_t data = read_bluetooth(1000);
	buf[15] = data;
	data = read_bluetooth(1000);
	buf[16] = data;
	usb_write(buf, sizeof(buf));

	if( buf[15] == 'O' && buf[16] == 'K' )
	{
		usb_write_string("\n\rBluetooth test past!\n\r");
		return 0;
	}
	else
	{
		usb_write_string("\n\rBluetooth test failed!\n\r");
		return -1;
	}

}

// main funciton
int main(void)
{
	// Setup clock
	rcc_clock_setup_hse_3v3(&rcc_hse_8mhz_3v3[RCC_CLOCK_3V3_168MHZ]);

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


	// Infinite loop
	while(true)
	{

		if( system_millis > 10000)
			test_bluetooth();
	}
}