#include "systick_handler.h"

// Initilize globals
volatile uint32_t system_millis = 0;
systick_callback_list systick_callbacks = {0};

void sys_tick_handler(void)
{
	system_millis++;

	int i;
	for(i = 0; i < systick_callbacks.index; ++i)
	{
		if(!(system_millis % systick_callbacks.callback_list[i].period))
		{
			systick_callbacks.callback_list[i].callback();
		}
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

int add_systick_callback(void (*callback)(void), uint32_t period)
{
	if(systick_callbacks.index < MAX_CALLBACKS)
	{
		systick_callbacks.callback_list[systick_callbacks.index].callback = callback;
		systick_callbacks.callback_list[systick_callbacks.index++].period = period;
		return 0;
	}
	return -1;
}

int remove_systick_callback(void (*callback)(void))
{
	int not_found = -1;
	int i;
	for(i = 0; i < systick_callbacks.index; ++i)
	{
		if(callback == systick_callbacks.callback_list[i].callback)
		{
			not_found = 0;
			// Shift everything left
			int j;
			for(j = i + 1; j < systick_callbacks.index; ++j)
			{
				systick_callbacks.callback_list[j - 1] = systick_callbacks.callback_list[j];
			}
			systick_callbacks.index--;
		}
	}
	return not_found;
}