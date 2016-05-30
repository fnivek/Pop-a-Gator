#include "bluetooth.h"

void setup_bluetooth(void)
{
	// Setup GPIO
	rcc_periph_clock_enable(RCC_GPIOA);
	gpio_mode_setup(GPIOA, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO2 | GPIO3);
	gpio_set_af(GPIOA, GPIO_AF7, GPIO2 | GPIO3);

	// Setup uart
	rcc_periph_clock_enable(RCC_USART2);
	usart_set_baudrate(USART2, 9600);
	usart_set_databits(USART2, 8);
	usart_set_stopbits(USART2, USART_STOPBITS_1);
	usart_set_mode(USART2, USART_MODE_TX_RX);
	usart_set_parity(USART2, USART_PARITY_NONE);
	usart_set_flow_control(USART2, USART_FLOWCONTROL_NONE);
	usart_enable(USART2);

	// Setup bluetooth module with AT commands

}

uint16_t read_bluetooth(uint32_t timeout)
{
	uint32_t end = system_millis + timeout;
	while(!(USART_SR(USART2) & USART_SR_RXNE) && end > system_millis);

	if(end <= system_millis)
	{
		return 0xFFFF;
	}

	return usart_recv(USART2);
}

void write_bluetooth(uint16_t data)
{
	usart_send_blocking(USART2, data);
}

void flush_bluetooth_input(void)
{
	volatile uint16_t _ = usart_recv(USART2);
}