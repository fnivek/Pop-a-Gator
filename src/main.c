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

#include "/home/fnivek/stm32f4_hardware_interface/libopencm3/lib/usb/usb_private.h"

#include "usb.h"
#include "systick_handler.h"
#include "bluetooth.h"

/*
 * 	Pin map
 *		B3 - SPI3_SCK
 * 		B4 - SPI3_MISO
 * 		B5 - SPI3_MOSI
 */

// Heartbeat function
void beat(void)
{
	gpio_toggle(GPIOD, GPIO14);
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

	// Setup GPIO
	//rcc_periph_clock_enable(RCC_GPIOB);
	//gpio_mode_setup(GPIOB, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO3 | GPIO4 | GPIO5);
	//gpio_set_af(GPIOB, GPIO_AF2,  GPIO3);		// SPI3_SCK
	//gpio_set_af(GPIOB, GPIO_AF1,  GPIO4);	  	// SPI3_MISO
	//gpio_set_af(GPIOB, GPIO_AF6,  GPIO5);	  	// SPI3_MOSI

	rcc_periph_clock_enable(RCC_GPIOD);
	gpio_mode_setup(GPIOD, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO12 | GPIO13 | GPIO14 | GPIO15);
	
	/* Setup SPI
	rcc_periph_clock_enable(RCC_SPI3);
	spi_set_master_mode(SPI3);
	spi_set_baudrate_prescaler(SPI3, SPI_CR1_BR_FPCLK_DIV_64);
	spi_set_clock_polarity_0(SPI3);
	spi_set_clock_phase_0(SPI3);
	spi_set_full_duplex_mode(SPI3);
	spi_set_unidirectional_mode(SPI3);
	spi_set_dff_8bit(SPI3);
	spi_enable_software_slave_management(SPI3);
	spi_send_msb_first(SPI3);
	spi_enable(SPI3);	*/
	
	// Setup USB
	setup_usb();

	// Setup Bluetooth
	setup_bluetooth();

	// Start system tic
	systick_setup();

	// Setup heartbeat
	add_systick_callback(beat, 1000);

	// Test bluetooth
	//add_systick_callback(test_bluetooth, 5000);

	// Infinite loop
	while(true)
	{
		/*spi_write(SPI3, test++);
		//spi_read(SPI3);		
		gpio_port_write(GPIOD, test << 12);
		usart_send_blocking(USART2, test + '0');
		usart_send_blocking(USART2, '\r');
		usart_send_blocking(USART2, '\n\r');*/
		if( system_millis > 10000)
			test_bluetooth();
	}
}