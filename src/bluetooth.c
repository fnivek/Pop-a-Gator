#include "bluetooth.h"

void (*bluetooth_cb)(void) = 0;

void SetupBluetooth(void) {
	// Setup GPIO
	rcc_periph_clock_enable(RCC_GPIOA);
	gpio_mode_setup(GPIOA, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO2 | GPIO3);
	gpio_set_af(GPIOA, GPIO_AF7, GPIO2 | GPIO3);

	// Setup uart
	rcc_periph_clock_enable(RCC_USART2);
	usart_set_baudrate(USART2, 38400);
	usart_set_databits(USART2, 8);
	usart_set_stopbits(USART2, USART_STOPBITS_1);
	usart_set_mode(USART2, USART_MODE_TX_RX);
	usart_set_parity(USART2, USART_PARITY_NONE);
	usart_set_flow_control(USART2, USART_FLOWCONTROL_NONE);
	usart_enable(USART2);
	nvic_enable_irq(NVIC_USART2_IRQ);
	usart_enable_rx_interrupt(USART2);

	// Setup bluetooth module with AT commands
	// This only needs to be done once
	// TODO: Write script or mode that will automatically program an HC-05

}

uint16_t BluetoothReadBlocking(uint32_t timeout) {
	uint32_t end = system_millis + timeout;
	while(!(USART_SR(USART2) & USART_SR_RXNE) && end > system_millis);

	return usart_recv(USART2);
}

uint16_t BluetoothRead(void) {
	return usart_recv(USART2);
}

void BluetoothWrite(uint16_t data) {
	usart_send_blocking(USART2, data);
}

void BluetoothFlushInput(void) {
	volatile uint16_t _ = usart_recv(USART2);
}

void BluetoothAddCb(void (*callback)(void)) {
	bluetooth_cb = callback;
}

void usart2_isr(void) {
	if (bluetooth_cb != 0) {
		bluetooth_cb();
	}
}