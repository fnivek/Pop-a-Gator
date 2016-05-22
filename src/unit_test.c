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

// Test USB debug comms
int8_t test_usb(void)
{
	while(!is_usb_ready());

	usb_write_string("\n\r\n\rStarting USB test\n\rPlease type pop...\n\r\t");
	usb_write_string("\n\rTODO: Write a USB read funciton");
	usb_write_string("\n\rUSB test results: Unkown");
	return -1;
}

// Test the bluetooth module
int8_t test_bluetooth(void)
{
	// Clear read
	flush_bluetooth_input();

	usb_write_string("\n\r\n\rStart bluetooth test");
	usb_write_string("\n\rWriting AT to bluetooth chip\n\r");

	char buf[] = "Bluetooth chip replied w/: ##";
	// Write AT
	write_bluetooth('A');
	write_bluetooth('T');

	// Read result
	uint16_t data = read_bluetooth(1000);
	buf[27] = data;
	data = read_bluetooth(1000);
	buf[28] = data;
	usb_write(buf, sizeof(buf));

	if( buf[27] == 'O' && buf[28] == 'K' )
	{
		usb_write_string("\n\rBluetooth test past!");
		return 0;
	}
	else
	{
		usb_write_string("\n\rBluetooth test failed!");
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

	// Begin tests
	int8_t result = 
		test_usb() | 
		test_bluetooth();

	if(!result)
	{
		usb_write_string("\n\r\n\rAll test complete succesfully!");
		gpio_set(GPIOD, GPIO12);
	}
	else
	{
		 usb_write_string("\n\r\n\rSome test failed!");
		 gpio_set(GPIOD, GPIO14);
	}

	usb_write_string("\n\rFinished");

	
	// Infinite loop
	while(true)
	{
		if(!(system_millis % 5000))
		{
		}
	}
}