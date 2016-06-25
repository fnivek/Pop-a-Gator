/*
 * This is the main file for Pop-a-Gator
 */
#include "board.h"

 #include "game_sir.h"


// main funciton
int main(void)
{
	SetupBoard();

	// Infinite loop
	uint16_t result = 0xFFFF;
	while(true)
	{
		result = read_bluetooth(1000);
		if(result != 0xFFFF)
		{
			game_sir_new_data(result);
			if(game_sir_get_btn_value(HOME_BTN_INDEX))
			{
				set_debug_led(DEBUG_ALL_LEDS);
				continue;
			}
			else
			{
				clear_debug_led(DEBUG_ALL_LEDS);
			}

			if(game_sir_get_btn_value(A_INDEX))
			{
				set_debug_led(DEBUG_GREEN_LED);
			}
			else
			{
				clear_debug_led(DEBUG_GREEN_LED);
			}
			if(game_sir_get_btn_value(B_INDEX))
			{
				set_debug_led(DEBUG_RED_LED);
			}
			else
			{
				clear_debug_led(DEBUG_RED_LED);
			}
			if(game_sir_get_btn_value(X_INDEX))
			{
				set_debug_led(DEBUG_BLUE_LED);
			}
			else
			{
				clear_debug_led(DEBUG_BLUE_LED);
			}
			if(game_sir_get_btn_value(Y_INDEX))
			{
				set_debug_led(DEBUG_ORANGE_LED);
			}
			else
			{
				clear_debug_led(DEBUG_ORANGE_LED);
			}
		}
	}
}