#include "systick_handler.h"

// Initilize globals
volatile uint32_t system_millis = 0;

void sys_tick_handler(void)
{
	system_millis++;

	if(!(system_millis % systick_callbacks[0].period))
	{
		systick_callbacks[0].callback();
	}
}

void systick_setup(void)
{
	// Clock rate / 1000 = 168000 for one ms
	systick_set_reload(168000);
	systick_set_clocksource(STK_CSR_CLKSOURCE_AHB);
	systick_counter_enable();
	systick_interrupt_enable();
}