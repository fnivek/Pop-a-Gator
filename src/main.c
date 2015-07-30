#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/cm3/nvic.h>
#include <libopencm3/cm3/systick.h>

int main(void) {
	int i;

	/* Enable GPIOE clock. */
	rcc_periph_clock_enable(RCC_GPIOE);

	/* Set GPIO12 (in GPIO port E) to 'output push-pull'. */
	gpio_mode_setup(GPIOE, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO12);

	for (;;) {
		gpio_toggle(GPIOE, GPIO12);	/* LED on/off */
		for (i = 0; i < 2000000; i++) /* Wait a bit. */
			__asm__("nop");
	}
	
	return 0;
}
