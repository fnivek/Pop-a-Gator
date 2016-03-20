/*
 * This is the main file for the nordic interface
 */

#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/spi.h>
#include <libopencm3/stm32/gpio.h>

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
	rcc_periph_clock_enable(RCC_GPIOB);
	gpio_mode_setup(GPIOB, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO3 | GPIO4 | GPIO5);
	gpio_set_af(GPIOB, GPIO_AF2,  GPIO3);
	gpio_set_af(GPIOB, GPIO_AF1,  GPIO4);	  		
	gpio_set_af(GPIOB, GPIO_AF6,  GPIO5);	  		

	rcc_periph_clock_enable(RCC_GPIOD);
	gpio_mode_setup(GPIOD, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO12 | GPIO13 | GPIO14 | GPIO15);
	
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
	spi_enable(SPI3);	
	

	// Infinite loop
	uint8_t test = 0;
	while(true)
	{
		spi_write(SPI3, test++);
		//spi_read(SPI3);		
		gpio_port_write(GPIOD, test << 12);
		int i;
		for(i = 0; i < 0xFFFFFF; ++i)
		{
			__asm__("nop");
		}
	}
}
