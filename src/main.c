/*
 * This is the main file for the nordic interface
 */


#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/spi.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/usart.h>
#include <stdlib.h>
#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/usb/usbd.h>
#include <libopencm3/usb/cdc.h>
#include <libopencm3/cm3/scb.h>

#include "/home/fnivek/stm32f4_hardware_interface/libopencm3/lib/usb/usb_private.h"

#include "usb.h"


//#define MMIO32(addr)		(*(volatile uint32_t *)(addr))
//#define dev_base_address (usbd_dev->driver->base_address)
//#define REBASE(x)        MMIO32((x) + (dev_base_address))
//#define OTG_DIEPCTL(x)			(0x900 + 0x20*(x))
//#define OTG_DIEPCTL0_EPENA		(1 << 31)
//#define OTG_DIEPCTL0_EPDIS		(1 << 30)


/*
 * 	Pin map
 *		B3 - SPI3_SCK
 * 		B4 - SPI3_MISO
 * 		B5 - SPI3_MOSI
 */

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

	//rcc_periph_clock_enable(RCC_GPIOA);
	//gpio_mode_setup(GPIOA, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO2);
	//gpio_set_af(GPIOA, GPIO_AF7, GPIO2);

	rcc_periph_clock_enable(RCC_GPIOD);
	gpio_mode_setup(GPIOD, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO12 | GPIO13 | GPIO14 | GPIO15);
	
	/* Setup uart
	rcc_periph_clock_enable(RCC_USART2);
	usart_set_baudrate(USART2, 9600);
	usart_set_databits(USART2, 8);
	usart_set_stopbits(USART2, USART_STOPBITS_1);
	usart_set_mode(USART2, USART_MODE_TX);
	usart_set_parity(USART2, USART_PARITY_NONE);
	usart_set_flow_control(USART2, USART_FLOWCONTROL_NONE);
	usart_enable(USART2);
	
	// Setup SPI
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
	usbd_device *usbd_dev;
	rcc_periph_clock_enable(RCC_GPIOA);
	rcc_periph_clock_enable(RCC_OTGFS);

	gpio_mode_setup(GPIOA, GPIO_MODE_AF, GPIO_PUPD_NONE,
			GPIO9 | GPIO11 | GPIO12);
	gpio_set_af(GPIOA, GPIO_AF10, GPIO9 | GPIO11 | GPIO12);

	usbd_dev = usbd_init(&otgfs_usb_driver, &dev, &config,
			usb_strings, 2,
			usbd_control_buffer, sizeof(usbd_control_buffer));

	usbd_register_set_config_callback(usbd_dev, cdcacm_set_config);

	// Infinite loop
	uint8_t test = 0;
	while(true)
	{
		/*spi_write(SPI3, test++);
		//spi_read(SPI3);		
		gpio_port_write(GPIOD, test << 12);
		usart_send_blocking(USART2, test + '0');
		usart_send_blocking(USART2, '\r');
		usart_send_blocking(USART2, '\n');*/
		char buf[1];
		buf[0] = (char)(test++ + '0');
		if(test > 80)
			test = 0;
		usb_write(usbd_dev, buf, 1);
		usbd_poll(usbd_dev);

		int i;
		for(i = 0; i < 0xFF; ++i)
		{
			__asm__("nop");
		}
	}
}