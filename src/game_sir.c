#include "game_sir.h"

// Constants
const uint8_t kStartIndicator =					0xA1;	// The value of the byte that precedes all messages packages
const uint8_t kStdMsgIndicator =				0xC4;	// The value of the byte that precedes a standard message package
const uint8_t kHomeBtnMsgIndicator =			0x12;	// The value of the byte that precedes a home btn message package

void GameSirNewData(uint8_t new_data)
{
	// IDLE state
	if(current_msg_decode_state == kIdle)
	{
		if(new_data == kStartIndicator)
		{
			// New message detected
			current_msg_decode_state = kDeterminePkgType;
		}
	}

	// kDeterminePkgType state
	else if(current_msg_decode_state == kDeterminePkgType)
	{
		// Reset the byte counter
		current_byte = 0;

		if(new_data == kStdMsgIndicator)
		{
			current_msg_decode_state = kStdPkg;
		}
		else if(new_data == kHomeBtnMsgIndicator)
		{
			current_msg_decode_state = kHomeBtnPkg;
		}
		else // Message skew detected!!!
		{
			// ERROR!!!!
			current_msg_decode_state = kIdle;
		}
	}

	// kHomeBtnPkg state
	else if(current_msg_decode_state == kHomeBtnPkg)
	{
		if(current_byte == remote[kHomeBtnIndex].byte_position)
		{
			remote[kHomeBtnIndex].value = remote[kHomeBtnIndex].mask & new_data;
		}
		else if(current_byte >= (kHomeBtnMsgPkgSize - 1))
		{
			current_msg_decode_state = kIdle;
		}
		++current_byte;
	}

	// kStdPkg state
	else if(current_msg_decode_state == kStdPkg)
	{
		// Since there is an empty byte at the end of the std message package we can skip the final for loop
		if(current_byte >= (kStdMsgPkgSize - 1))
		{
			current_msg_decode_state = kIdle;
			return;
		}

		// Loop through all buttons
		int btn_index = kLeftStickLRIndex;		// Skip the home button
		for(; btn_index < kNumBtns; ++btn_index)
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
uint8_t game_sir_get_btn_value(enum ControllerIndices button_index)
{
	return remote[button_index].value;
}