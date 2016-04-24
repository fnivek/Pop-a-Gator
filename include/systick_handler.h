#ifndef SYSTICK_HANDLER_H
#define SYSTICK_HANDLER_H

#include <libopencm3/cm3/systick.h>
#include <libopencm3/cm3/nvic.h>

// Types
typedef struct systick_callback
{
	// Callback to a function which performs the desired operation
	void (*callback)(void);

	// The period in milliseconds at which to call the callback
	uint32_t period;
} systick_callback;

// Globals
volatile uint32_t system_millis;

systick_callback systick_callbacks[10]; 

// Functions
void sys_tick_handler(void);

void systick_setup(void);

#endif