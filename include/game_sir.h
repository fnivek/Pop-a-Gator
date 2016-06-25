#ifndef GAME_SIR_H
#define GAME_SIR_H

#include <stdint.h>
#include <stdbool.h>

//#define HOME_BTN_MASK 					0x8
//#define LEFT_STICK_LR_MASK 				0xFF
//#define LEFT_STICK_UD_MASK 	
//#define RIGHT_STICK_LR_MASK 	
//#define RIGHT_STICK_UD_MASK 	
//#define LEFT_TRIGGER_MASK 	
//#define RIGHT_TRIGGER_MASK 	
//#define ABXY_BUMPERS_MASK 	
//#define SELECT_START_STICKS_MASK 	
//#define DPAD_MASK 	

// Representation of location in message package of a particular btn
enum MessageFormat
{
	// Home message package
	kHomeBtnByte,
	kHomeBtnEmpty0,
	kHomeBtnEmpty1,
	kHomeBtnMsgPkgSize,

	// Standard message
	kLeftStickLRByte = 0,
	kLeftStickUDByte,
	kRightStickLRByte,
	kRightStickUDByte,
	kLeftTriggerByte,
	kRightTriggerByte,
	kABXYBumpersByte,
	kSelectStartSticksByte, 		// This byte also contains information about if the left and right triggers are greater than some value but we don't care about that
	kDPadByte,
	kStdMsgEmpty0,
	kStdMsgPkgSize
};

// Representation of index of a particular btn in the gamepad struct
enum ControllerIndices
{
	kHomeBtnIndex,				// Home button must be first as the code takes advantage of this fact
	kLeftStickLRIndex,
	kLeftStickUDIndex,
	kRightStickLRIndex,
	kRightStickUDIndex,
	kLeftTriggerIndex,
	kRightTriggerIndex,
	kAIndex,
	kBIndex,
	kXIndex,
	kYIndex,
	kLeftBumperIndex,
	kRightBumperIndex,
	kSelectIndex,
	kStartIndex,
	kLeftStickIndex,
	kRightStickIndex,
	kDPadIndex,

	kNumBtns
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
static Button remote[kNumBtns] =
{
	{/*kHomeBtnIndex,*/ 				kHomeBtnByte,				/*true,*/ 	0x08,		0	},
	{/*kLeftStickLRIndex,*/ 			kLeftStickLRByte,			/*false,*/ 	0xFF,		128	},
	{/*kLeftStickUDIndex,*/ 			kLeftStickUDByte,			/*false,*/ 	0xFF,		128	},
	{/*kRightStickLRIndex,*/ 			kRightStickLRByte,			/*false,*/ 	0xFF,		128	},
	{/*kRightStickUDIndex,*/ 			kRightStickUDByte,			/*false,*/ 	0xFF,		128	},
	{/*kLeftTriggerIndex,*/ 			kLeftTriggerByte,			/*false,*/ 	0xFF,		0	},
	{/*kRightTriggerIndex,*/ 			kRightTriggerByte,			/*false,*/ 	0xFF,		0	},
	{/*kAIndex,*/			 			kABXYBumpersByte,			/*true,*/ 	0x01,		0	},
	{/*kBIndex,*/			 			kABXYBumpersByte,			/*true,*/ 	0x02,		0	},
	{/*kXIndex,*/			 			kABXYBumpersByte,			/*true,*/ 	0x08,		0	},
	{/*kYIndex,*/			 			kABXYBumpersByte,			/*true,*/ 	0x10,		0	},
	{/*kLeftBumperIndex,*/	 			kABXYBumpersByte,			/*true,*/ 	0x40,		0	},
	{/*kRightBumperIndex,*/ 			kABXYBumpersByte,			/*true,*/ 	0x80,		0	},
	{/*kSelectIndex,*/				 	kSelectStartSticksByte,		/*true,*/ 	0x04,		0	},
	{/*kStartIndex,*/				 	kSelectStartSticksByte,		/*true,*/ 	0x08,		0	},
	{/*kLeftStickIndex,*/			 	kSelectStartSticksByte,		/*true,*/ 	0x20,		0	},
	{/*kRightStickIndex,*/			 	kSelectStartSticksByte,		/*true,*/ 	0x40,		0	},
	{/*kDPadIndex,*/ 					kDPadByte,					/*false,*/ 	0x0F,		0	}
};

// State indicator for message package decoding
enum MessageDecodeState
{
	kIdle,
	kDeterminePkgType,
	kStdPkg,
	kHomeBtnPkg
};

// Current state
static enum MessageDecodeState current_msg_decode_state = kIdle;
static uint8_t current_byte = 0;

// Function to handle new incoming data
void GameSirNewData(uint8_t new_data);

// Function to get a button value
uint8_t game_sir_get_btn_value(enum ControllerIndices button_index);

#endif