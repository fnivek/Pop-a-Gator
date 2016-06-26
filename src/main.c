/*
 * This is the main file for Pop-a-Gator
 */
#include "board.h"

 #include "game_sir.h"


// main funciton
int main(void)
{
	SetupBoard();

	uint8_t no_key_pressed = 1;
	uint32_t last_sys_millis = 0;
	MotorsSetDirection(kLeftMotor, kForward);

	// Infinite loop
	while(true)
	{

		// Blink some LEDS
		if(game_sir_get_btn_value(kHomeBtnIndex))
		{
			if (no_key_pressed) {
				ToggleDebugLed(kDebugAllLeds);
			}
			no_key_pressed = 0;

		} else if (game_sir_get_btn_value(kAIndex)) {
			if (no_key_pressed) {
				ToggleDebugLed(kDebugGreenLed);
			}
			no_key_pressed = 0;
			
		} else if (game_sir_get_btn_value(kBIndex)) {
			if (no_key_pressed) {
				ToggleDebugLed(kDebugRedLed);
			}
			no_key_pressed = 0;
			
		} else if (game_sir_get_btn_value(kXIndex)) {
			if (no_key_pressed) {
				ToggleDebugLed(kDebugBlueLed);
			}
			no_key_pressed = 0;
			
		} else if (game_sir_get_btn_value(kYIndex)) {
			if (no_key_pressed) {
				ToggleDebugLed(kDebugOrangeLed);
			}
			no_key_pressed = 0;
			
		} else {
			no_key_pressed = 1;
		}


		// Control some motors
		if (last_sys_millis != system_millis && system_millis % 100) {
			last_sys_millis = system_millis;
			MotorsSetPWM(kLeftMotor, game_sir_get_btn_value(kLeftStickUDIndex) * 10);
		}
	}
}