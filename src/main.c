#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>

int main(void) {

	int i;
	/* Set main clock to use external 8 MHz crystal */
	rcc_clock_setup_hse_3v3(&hse_8mhz_3v3[CLOCK_3V3_168MHZ]);

	/* Enable GPIOE clock */
	rcc_periph_clock_enable(RCC_GPIOE);

	/* Set GPIO12 (in GPIO port E) to output, push-pull */
	gpio_mode_setup(GPIOE, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO12);

	for (;;) {
		/* Toggle LED GPIO pin */
		gpio_toggle(GPIOE, GPIO12);
		for (i = 0; i < 2000000; i++)
			__asm__("nop");
	}
	
	return 0;
}
