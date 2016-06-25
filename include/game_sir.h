#ifndef GAME_SIR_H
#define GAME_SIR_H

#include <stdint.h>
#include <stdbool.h>

#define START_INDICATOR					0xA1	// The value of the byte that precedes all messages packages
#define STD_MSG_INDICATOR				0xC4	// The value of the byte that precedes a standard message package
#define HOME_BTN_MSG_INDICATOR			0x12	// The value of the byte that precedes a home btn message package

#define HOME_BTN_MASK 					0x8
#define LEFT_STICK_LR_MASK 				0xFF
#define LEFT_STICK_UD_MASK 	
#define RIGHT_STICK_LR_MASK 	
#define RIGHT_STICK_UD_MASK 	
#define LEFT_TRIGGER_MASK 	
#define RIGHT_TRIGGER_MASK 	
#define ABXY_BUMPERS_MASK 	
#define SELECT_START_STICKS_MASK 	
#define DPAD_MASK 	

// Representation of location in message package of a particular btn
enum MESSAGE_FORMAT
{
	// Home message package
	HOME_BTN_BYTE,
	HOME_BTN_EMPTY0,
	HOME_BTN_EMPTY1,
	HOME_BTN_MSG_PKG_SIZE,

	// Standard message
	LEFT_STICK_LR_BYTE = 0,
	LEFT_STICK_UD_BYTE,
	RIGHT_STICK_LR_BYTE,
	RIGHT_STICK_UD_BYTE,
	LEFT_TRIGGER_BYTE,
	RIGHT_TRIGGER_BYTE,
	ABXY_BUMPERS_BYTE,
	SELECT_START_STICKS_BYTE, 		// This byte also contains information about if the left and right triggers are greater than some value but we don't care about that
	DPAD_BYTE,
	STD_MSG_EMPTY0,
	STD_MSG_PKG_SIZE
};

// Representation of index of a particular btn in the gamepad struct
enum CONTROLLER_INDICES
{
	HOME_BTN_INDEX,				// Home button must be first as the code takes advantage of this fact
	LEFT_STICK_LR_INDEX,
	LEFT_STICK_UD_INDEX,
	RIGHT_STICK_LR_INDEX,
	RIGHT_STICK_UD_INDEX,
	LEFT_TRIGGER_INDEX,
	RIGHT_TRIGGER_INDEX,
	A_INDEX,
	B_INDEX,
	X_INDEX,
	Y_INDEX,
	LEFT_BUMPER_INDEX,
	RIGHT_BUMPER_INDEX,
	SELECT_INDEX,
	START_INDEX,
	LEFT_STICK_INDEX,
	RIGHT_STICK_INDEX,
	DPAD_INDEX,

	NUM_BUTTONS
};

// Representation of a single button
typedef struct
{
	const uint8_t byte_position;		// Position of byte in message data
	//const uint8_t toogle;
	const uint8_t mask;					// Button mask for buttons that share a byte
	uint8_t value;						// Current value of the button
} Button;

// All the buttons on the game sir remote
static Button remote[NUM_BUTTONS] =
{
	{/*HOME_BTN_INDEX,*/ 				HOME_BTN_BYTE,				/*true,*/ 	0x08,		0	},
	{/*LEFT_STICK_LR_INDEX,*/ 			LEFT_STICK_LR_BYTE,			/*false,*/ 	0xFF,		128	},
	{/*LEFT_STICK_UD_INDEX,*/ 			LEFT_STICK_UD_BYTE,			/*false,*/ 	0xFF,		128	},
	{/*RIGHT_STICK_LR_INDEX,*/ 			RIGHT_STICK_LR_BYTE,		/*false,*/ 	0xFF,		128	},
	{/*RIGHT_STICK_UD_INDEX,*/ 			RIGHT_STICK_UD_BYTE,		/*false,*/ 	0xFF,		128	},
	{/*LEFT_TRIGGER_INDEX,*/ 			LEFT_TRIGGER_BYTE,			/*false,*/ 	0xFF,		0	},
	{/*RIGHT_TRIGGER_INDEX,*/ 			RIGHT_TRIGGER_BYTE,			/*false,*/ 	0xFF,		0	},
	{/*A_INDEX,*/			 			ABXY_BUMPERS_BYTE,			/*true,*/ 	0x01,		0	},
	{/*B_INDEX,*/			 			ABXY_BUMPERS_BYTE,			/*true,*/ 	0x02,		0	},
	{/*X_INDEX,*/			 			ABXY_BUMPERS_BYTE,			/*true,*/ 	0x08,		0	},
	{/*Y_INDEX,*/			 			ABXY_BUMPERS_BYTE,			/*true,*/ 	0x10,		0	},
	{/*LEFT_BUMPER_INDEX,*/	 			ABXY_BUMPERS_BYTE,			/*true,*/ 	0x40,		0	},
	{/*RIGHT_BUMPER_INDEX,*/ 			ABXY_BUMPERS_BYTE,			/*true,*/ 	0x80,		0	},
	{/*SELECT_INDEX,*/				 	SELECT_START_STICKS_BYTE,	/*true,*/ 	0x04,		0	},
	{/*START_INDEX,*/				 	SELECT_START_STICKS_BYTE,	/*true,*/ 	0x08,		0	},
	{/*LEFT_STICK_INDEX,*/			 	SELECT_START_STICKS_BYTE,	/*true,*/ 	0x20,		0	},
	{/*RIGHT_STICK_INDEX,*/			 	SELECT_START_STICKS_BYTE,	/*true,*/ 	0x40,		0	},
	{/*DPAD_INDEX,*/ 					DPAD_BYTE,					/*false,*/ 	0x0F,		0	}
};

// State indicator for message package decoding
enum MESSAGE_DECODE_STATE
{
	IDLE,
	DETERMINE_PKG_TYPE,
	STD_PKG,
	HOME_BTN_PKG
};

// Current state
static enum MESSAGE_DECODE_STATE current_msg_decode_state = IDLE;
static uint8_t current_byte = 0;

// Function to handle new incoming data
void GameSirNewData(uint8_t new_data);

// Function to get a button value
uint8_t game_sir_get_btn_value(enum CONTROLLER_INDICES button_index);

#endif