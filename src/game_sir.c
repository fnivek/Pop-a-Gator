#include "game_sir.h"

void GameSirNewData(uint8_t new_data)
{
	// IDLE state
	if(current_msg_decode_state == IDLE)
	{
		if(new_data == START_INDICATOR)
		{
			// New message detected
			current_msg_decode_state = DETERMINE_PKG_TYPE;
		}
	}

	// DETERMINE_PKG_TYPE state
	else if(current_msg_decode_state == DETERMINE_PKG_TYPE)
	{
		// Reset the byte counter
		current_byte = 0;

		if(new_data == STD_MSG_INDICATOR)
		{
			current_msg_decode_state = STD_PKG;
		}
		else if(new_data == HOME_BTN_MSG_INDICATOR)
		{
			current_msg_decode_state = HOME_BTN_PKG;
		}
		else // Message skew detected!!!
		{
			// ERROR!!!!
			current_msg_decode_state = IDLE;
		}
	}

	// HOME_BTN_PKG state
	else if(current_msg_decode_state == HOME_BTN_PKG)
	{
		if(current_byte == remote[HOME_BTN_INDEX].byte_position)
		{
			remote[HOME_BTN_INDEX].value = remote[HOME_BTN_INDEX].mask & new_data;
		}
		else if(current_byte >= (HOME_BTN_MSG_PKG_SIZE - 1))
		{
			current_msg_decode_state = IDLE;
		}
		++current_byte;
	}

	// STD_PKG state
	else if(current_msg_decode_state == STD_PKG)
	{
		// Since there is an empty byte at the end of the std message package we can skip the final for loop
		if(current_byte >= (STD_MSG_PKG_SIZE - 1))
		{
			current_msg_decode_state = IDLE;
			return;
		}

		// Loop through all buttons
		int btn_index = LEFT_STICK_LR_INDEX;		// Skip the home button
		for(; btn_index < NUM_BUTTONS; ++btn_index)
		{
			// Check if this is the byte coresponding to this button
			if(current_byte == remote[btn_index].byte_position)
			{
				// Set the value of the button
				remote[btn_index].value = remote[btn_index].mask & new_data;
			}			
		}

		// Increment byte counter
		++current_byte;
	}

}

// Function to get a button value
uint8_t game_sir_get_btn_value(enum CONTROLLER_INDICES button_index)
{
	return remote[button_index].value;
}