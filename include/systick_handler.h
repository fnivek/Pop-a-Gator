#ifndef SYSTICK_HANDLER_H
#define SYSTICK_HANDLER_H

#include <libopencm3/cm3/systick.h>
#include <libopencm3/cm3/nvic.h>

// Defines
#define MAX_CALLBACKS 10

// Types
typedef struct SystickCallback
{
	// Callback to a function which performs the desired operation
	void (*callback)(void);

	// The period in milliseconds at which to call the callback
	uint32_t period;
} SystickCallback;

typedef struct SystickCallbackList
{
	uint8_t index;
	SystickCallback callback_list[MAX_CALLBACKS];

} SystickCallbackList;

// Globals
volatile uint32_t system_millis;
SystickCallbackList systick_callbacks; 

// Functions
void SysTickHandler(void);

void SetupSystick(void);

int AddSystickCallback(void (*callback)(void), uint32_t period);
int RemoveSystickCallback(void (*callback)(void));

#endif