#include "board.h"
#include "debug_leds.h"
#include "game_sir.h"

// Test USB debug comms
int8_t test_usb(void)
{
	while(!is_usb_ready());

	UsbWriteString("\n\r\n\rStarting USB test\n\rPlease type pop...\n\r\t");
	UsbWriteString("\n\rTODO: Write a USB read funciton");
	UsbWriteString("\n\rUSB test results: Unkown");
	return 0;
}

// Test the bluetooth module
int8_t test_bluetooth(void)
{
	// Clear read
	FlushBluetoothInput();

	UsbWriteString("\n\r\n\rStart bluetooth test");
	UsbWriteString("\n\rWriting AT to bluetooth chip\n\r");

	char buf[] = "Bluetooth chip replied w/: ##";
	// Write AT
	WriteBluetooth('A');
	WriteBluetooth('T');

	// Read result
	uint16_t data = ReadBluetooth(1000);
	buf[27] = data;
	data = ReadBluetooth(1000);
	buf[28] = data;
	UsbWrite(buf, sizeof(buf));

	if( buf[27] == 'O' && buf[28] == 'K' )
	{
		UsbWriteString("\n\rBluetooth test past!");
		return 0;
	}
	else
	{
		UsbWriteString("\n\rBluetooth test failed!");
		return -1;
	}

}

// Test game sir message decoder
uint8_t raw_game_sir_input[] =
{
161, 196, 128, 128, 128, 128, 0, 0, 1, 0, 0, 0, 161, 196, 128, 128, 128, 128, 0, 0, 0, 0, 0, 0, 161, 196, 128, 128, 128, 128, 0, 0, 1, 0, 0, 0, 161, 196, 128, 128, 128, 128, 0, 0, 0, 0, 0, 0, 161, 196, 128, 128, 128, 128, 0, 0, 2, 0, 0, 0, 161, 196, 128, 128, 128, 128, 0, 0, 0, 0, 0, 0, 161, 196, 128, 128, 128, 128, 0, 0, 2, 0, 0, 0, 161, 196, 128, 128, 128, 128, 0, 0, 3, 0, 0, 0, 161, 196, 128, 128, 128, 128, 0, 0, 2, 0, 0, 0, 161, 196, 128, 128, 128, 128, 0, 0, 0, 0, 0, 0, 161, 196, 128, 128, 128, 128, 0, 0, 8, 0, 0, 0, 161, 196, 128, 128, 128, 128, 0, 0, 0, 0, 0, 0, 161, 196, 128, 128, 128, 128, 0, 0, 16, 0, 0, 0, 161, 196, 128, 128, 128, 128, 0, 0, 0, 0, 0, 0, 161, 196, 128, 128, 128, 128, 0, 0, 128, 0, 0, 0, 161, 196, 128, 128, 128, 128, 0, 0, 192, 0, 0, 0, 161, 196, 128, 128, 128, 128, 0, 0, 193, 0, 0, 0, 161, 196, 128, 128, 128, 128, 0, 0, 192, 0, 0, 0, 161, 196, 128, 128, 128, 128, 0, 0, 64, 0, 0, 0, 161, 196, 128, 128, 128, 128, 0, 0, 0, 0, 0, 0, 161, 196, 125, 128, 128, 128, 0, 0, 0, 0, 0, 0, 161, 196, 125, 132, 128, 128, 0, 0, 0, 0, 0, 0, 161, 196, 125, 140, 128, 128, 0, 0, 0, 0, 0, 0, 161, 196, 125, 146, 128, 128, 0, 0, 0, 0, 0, 0, 161, 196, 128, 150, 128, 128, 0, 0, 0, 0, 0, 0, 161, 196, 128, 157, 128, 128, 0, 0, 0, 0, 0, 0, 161, 196, 128, 167, 128, 128, 0, 0, 0, 0, 0, 0, 161, 196, 128, 172, 128, 128, 0, 0, 0, 0, 0, 0, 161, 196, 128, 177, 128, 128, 0, 0, 0, 0, 0, 0, 161, 196, 128, 183, 128, 128, 0, 0, 0, 0, 0, 0, 161, 196, 128, 186, 128, 128, 0, 0, 0, 0, 0, 0, 161, 196, 128, 181, 128, 128, 0, 0, 0, 0, 0, 0, 161, 196, 128, 172, 128, 128, 0, 0, 0, 0, 0, 0, 161, 196, 128, 148, 128, 128, 0, 0, 0, 0, 0, 0, 161, 196, 128, 128, 128, 128, 0, 0, 0, 0, 0, 0, 161, 196, 128, 128, 128, 74, 0, 0, 0, 0, 0, 0, 161, 196, 128, 128, 128, 43, 0, 0, 0, 0, 0, 0, 161, 196, 128, 128, 128, 23, 0, 0, 0, 0, 0, 0, 161, 196, 128, 128, 128, 0, 0, 0, 0, 0, 0, 0, 161, 196, 128, 128, 128, 8, 0, 0, 0, 0, 0, 0, 161, 196, 128, 128, 128, 17, 0, 0, 0, 0, 0, 0, 161, 196, 128, 128, 128, 27, 0, 0, 0, 0, 0, 0, 161, 196, 128, 128, 128, 46, 0, 0, 0, 0, 0, 0, 161, 196, 128, 128, 128, 75, 0, 0, 0, 0, 0, 0, 161, 196, 128, 128, 128, 128, 0, 0, 0, 0, 0, 0, 161, 196, 128, 128, 128, 128, 0, 0, 0, 0, 1, 0, 161, 196, 128, 128, 128, 128, 0, 0, 0, 0, 2, 0, 161, 196, 128, 128, 128, 128, 0, 0, 0, 0, 3, 0, 161, 196, 128, 128, 128, 128, 0, 0, 0, 0, 4, 0, 161, 196, 128, 128, 128, 128, 0, 0, 0, 0, 5, 0, 161, 196, 128, 128, 128, 128, 0, 0, 0, 0, 6, 0, 161, 196, 128, 128, 128, 128, 0, 0, 0, 0, 7, 0, 161, 196, 128, 128, 128, 128, 0, 0, 0, 0, 8, 0, 161, 196, 128, 128, 128, 128, 0, 0, 0, 0, 1, 0, 161, 196, 128, 128, 128, 128, 0, 0, 0, 0, 0, 0, 161, 196, 128, 128, 128, 128, 0, 66, 0, 0, 0, 0, 161, 196, 128, 128, 128, 128, 0, 104, 0, 2, 0, 0, 161, 196, 128, 128, 128, 128, 0, 132, 0, 2, 0, 0, 161, 196, 128, 128, 128, 128, 0, 147, 0, 2, 0, 0, 161, 196, 128, 128, 128, 128, 0, 150, 0, 2, 0, 0, 161, 196, 128, 128, 128, 128, 0, 135, 0, 2, 0, 0, 161, 196, 128, 128, 128, 128, 0, 104, 0, 2, 0, 0, 161, 196, 128, 128, 128, 128, 0, 46, 0, 0, 0, 0, 161, 196, 128, 128, 128, 128, 0, 0, 0, 0, 0, 0, 161, 196, 128, 128, 128, 128, 23, 0, 0, 0, 0, 0, 161, 196, 128, 128, 128, 128, 127, 0, 0, 1, 0, 0, 161, 196, 128, 128, 128, 128, 177, 0, 0, 1, 0, 0, 161, 196, 128, 128, 128, 128, 204, 0, 0, 1, 0, 0, 161, 196, 128, 128, 128, 128, 226, 0, 0, 1, 0, 0, 161, 196, 128, 128, 128, 128, 238, 0, 0, 1, 0, 0, 161, 196, 128, 128, 128, 128, 245, 0, 0, 1, 0, 0, 161, 196, 128, 128, 128, 128, 253, 0, 0, 1, 0, 0, 161, 196, 128, 128, 128, 128, 249, 0, 0, 1, 0, 0, 161, 196, 128, 128, 128, 128, 238, 0, 0, 1, 0, 0, 161, 196, 128, 128, 128, 128, 230, 0, 0, 1, 0, 0, 161, 196, 128, 128, 128, 128, 215, 0, 0, 1, 0, 0, 161, 196, 128, 128, 128, 128, 192, 0, 0, 1, 0, 0, 161, 196, 128, 128, 128, 128, 162, 0, 0, 1, 0, 0, 161, 196, 128, 128, 128, 128, 108, 0, 0, 1, 0, 0, 161, 196, 128, 128, 128, 128, 50, 0, 0, 0, 0, 0, 161, 196, 128, 128, 128, 128, 0, 0, 0, 0, 0, 0, 161, 196, 128, 128, 128, 128, 0, 69, 0, 0, 0, 0, 161, 196, 128, 128, 128, 128, 0, 104, 0, 2, 0, 0, 161, 196, 128, 128, 128, 128, 0, 135, 0, 2, 0, 0, 161, 196, 128, 128, 128, 128, 0, 150, 0, 2, 0, 0, 161, 196, 128, 128, 128, 128, 0, 162, 0, 2, 0, 0, 161, 196, 128, 128, 128, 128, 0, 169, 0, 2, 0, 0, 161, 196, 128, 128, 128, 128, 0, 173, 0, 2, 0, 0, 161, 196, 128, 128, 128, 128, 0, 165, 0, 2, 0, 0, 161, 196, 128, 128, 128, 128, 0, 150, 0, 2, 0, 0, 161, 196, 128, 128, 128, 128, 0, 101, 0, 2, 0, 0, 161, 196, 128, 128, 128, 128, 88, 16, 0, 1, 0, 0, 161, 196, 128, 128, 128, 128, 132, 0, 0, 1, 0, 0, 161, 196, 128, 128, 128, 128, 165, 0, 0, 1, 0, 0, 161, 196, 128, 128, 128, 128, 184, 0, 0, 1, 0, 0, 161, 196, 128, 128, 128, 128, 200, 0, 0, 1, 0, 0, 161, 196, 128, 128, 128, 128, 208, 0, 0, 1, 0, 0, 161, 196, 128, 128, 128, 128, 211, 0, 0, 1, 0, 0, 161, 196, 128, 128, 128, 128, 200, 0, 0, 1, 0, 0, 161, 196, 128, 128, 128, 128, 184, 0, 0, 1, 0, 0, 161, 196, 128, 128, 128, 128, 158, 0, 0, 1, 0, 0, 161, 196, 128, 128, 128, 128, 116, 0, 0, 1, 0, 0, 161, 196, 128, 128, 128, 128, 66, 0, 0, 0, 0, 0, 161, 196, 128, 128, 128, 128, 0, 0, 0, 0, 0, 0, 161, 196, 128, 128, 128, 128, 0, 0, 0, 8, 0, 0, 161, 196, 128, 128, 128, 128, 0, 0, 0, 0, 0, 0, 161, 196, 128, 128, 128, 128, 0, 0, 0, 4, 0, 0, 161, 196, 128, 128, 128, 128, 0, 0, 0, 0, 0, 0, 161, 196, 128, 150, 128, 128, 0, 0, 0, 0, 0, 0, 161, 196, 128, 197, 128, 128, 0, 0, 0, 0, 0, 0, 161, 196, 128, 229, 128, 128, 0, 0, 0, 0, 0, 0, 161, 196, 128, 238, 128, 128, 0, 0, 0, 0, 0, 0, 161, 196, 128, 236, 128, 128, 0, 0, 0, 0, 0, 0, 161, 196, 128, 221, 128, 128, 0, 0, 0, 0, 0, 0, 161, 196, 128, 165, 128, 128, 0, 0, 0, 0, 0, 0, 161, 196, 128, 128, 128, 128, 0, 0, 0, 0, 0, 0, 161, 196, 128, 128, 128, 111, 0, 0, 0, 0, 0, 0, 161, 196, 128, 128, 128, 116, 0, 0, 0, 0, 0, 0, 161, 196, 128, 128, 128, 128, 0, 0, 0, 0, 0, 0, 161, 196, 128, 128, 137, 128, 0, 0, 0, 0, 0, 0, 161, 196, 128, 128, 159, 128, 0, 0, 0, 0, 0, 0, 161, 196, 128, 128, 173, 128, 0, 0, 0, 0, 0, 0, 161, 196, 128, 128, 182, 128, 0, 0, 0, 0, 0, 0, 161, 196, 128, 128, 186, 128, 0, 0, 0, 0, 0, 0, 161, 196, 128, 128, 182, 128, 0, 0, 0, 0, 0, 0, 161, 196, 128, 128, 160, 128, 0, 0, 0, 0, 0, 0, 161, 196, 128, 128, 128, 128, 0, 0, 0, 0, 0, 0, 161, 196, 128, 128, 128, 128, 0, 0, 1, 0, 0, 0, 161, 196, 128, 128, 128, 128, 0, 0, 1, 0, 5, 0, 161, 196, 128, 128, 128, 128, 0, 0, 1, 0, 7, 0, 161, 196, 128, 128, 128, 128, 0, 0, 19, 0, 7, 0, 161, 196, 128, 128, 128, 128, 0, 0, 18, 0, 8, 0, 161, 196, 128, 128, 128, 128, 0, 0, 18, 0, 7, 0, 161, 196, 128, 128, 128, 128, 0, 0, 2, 0, 6, 0, 161, 196, 128, 128, 128, 128, 0, 0, 2, 0, 5, 0, 161, 196, 128, 128, 128, 128, 0, 0, 3, 0, 0, 0, 161, 196, 128, 128, 128, 128, 0, 0, 0, 0, 0, 0, 161, 196, 128, 128, 128, 128, 0, 0, 128, 0, 0, 0, 161, 196, 128, 128, 128, 128, 88, 0, 128, 1, 0, 0, 161, 196, 128, 128, 128, 128, 150, 31, 128, 1, 0, 0, 161, 196, 128, 128, 128, 128, 184, 69, 128, 1, 0, 0, 161, 196, 128, 128, 128, 128, 192, 77, 128, 1, 0, 0, 161, 196, 128, 128, 128, 128, 208, 69, 128, 1, 0, 0, 161, 196, 128, 128, 128, 128, 211, 38, 128, 1, 0, 0, 161, 196, 128, 128, 128, 128, 215, 0, 128, 1, 0, 0, 161, 196, 128, 128, 128, 128, 200, 0, 0, 1, 0, 0, 161, 196, 128, 128, 128, 128, 169, 0, 0, 1, 0, 0, 161, 196, 128, 128, 128, 128, 84, 0, 0, 1, 0, 0, 161, 196, 128, 128, 128, 128, 0, 0, 0, 0, 0, 0
};

uint8_t state[][kNumBtns] =
{
{0, 128, 128, 128, 128, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
{0, 128, 128, 128, 128, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
{0, 128, 128, 128, 128, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
{0, 128, 128, 128, 128, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
{0, 128, 128, 128, 128, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
{0, 128, 128, 128, 128, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
{0, 128, 128, 128, 128, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
{0, 128, 128, 128, 128, 0, 0, 1, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
{0, 128, 128, 128, 128, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
{0, 128, 128, 128, 128, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
{0, 128, 128, 128, 128, 0, 0, 0, 0, 8, 0, 0, 0, 0, 0, 0, 0, 0, },
{0, 128, 128, 128, 128, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
{0, 128, 128, 128, 128, 0, 0, 0, 0, 0, 16, 0, 0, 0, 0, 0, 0, 0, },
{0, 128, 128, 128, 128, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
{0, 128, 128, 128, 128, 0, 0, 0, 0, 0, 0, 0, 128, 0, 0, 0, 0, 0, },
{0, 128, 128, 128, 128, 0, 0, 0, 0, 0, 0, 64, 128, 0, 0, 0, 0, 0, },
{0, 128, 128, 128, 128, 0, 0, 1, 0, 0, 0, 64, 128, 0, 0, 0, 0, 0, },
{0, 128, 128, 128, 128, 0, 0, 0, 0, 0, 0, 64, 128, 0, 0, 0, 0, 0, },
{0, 128, 128, 128, 128, 0, 0, 0, 0, 0, 0, 64, 0, 0, 0, 0, 0, 0, },
{0, 128, 128, 128, 128, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
{0, 125, 128, 128, 128, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
{0, 125, 132, 128, 128, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
{0, 125, 140, 128, 128, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
{0, 125, 146, 128, 128, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
{0, 128, 150, 128, 128, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
{0, 128, 157, 128, 128, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
{0, 128, 167, 128, 128, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
{0, 128, 172, 128, 128, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
{0, 128, 177, 128, 128, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
{0, 128, 183, 128, 128, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
{0, 128, 186, 128, 128, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
{0, 128, 181, 128, 128, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
{0, 128, 172, 128, 128, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
{0, 128, 148, 128, 128, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
{0, 128, 128, 128, 128, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
{0, 128, 128, 128, 74, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
{0, 128, 128, 128, 43, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
{0, 128, 128, 128, 23, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
{0, 128, 128, 128, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
{0, 128, 128, 128, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
{0, 128, 128, 128, 17, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
{0, 128, 128, 128, 27, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
{0, 128, 128, 128, 46, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
{0, 128, 128, 128, 75, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
{0, 128, 128, 128, 128, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
{0, 128, 128, 128, 128, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, },
{0, 128, 128, 128, 128, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, },
{0, 128, 128, 128, 128, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, },
{0, 128, 128, 128, 128, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, },
{0, 128, 128, 128, 128, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5, },
{0, 128, 128, 128, 128, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, },
{0, 128, 128, 128, 128, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, },
{0, 128, 128, 128, 128, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8, },
{0, 128, 128, 128, 128, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, },
{0, 128, 128, 128, 128, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
{0, 128, 128, 128, 128, 0, 66, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
{0, 128, 128, 128, 128, 0, 104, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
{0, 128, 128, 128, 128, 0, 132, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
{0, 128, 128, 128, 128, 0, 147, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
{0, 128, 128, 128, 128, 0, 150, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
{0, 128, 128, 128, 128, 0, 135, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
{0, 128, 128, 128, 128, 0, 104, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
{0, 128, 128, 128, 128, 0, 46, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
{0, 128, 128, 128, 128, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
{0, 128, 128, 128, 128, 23, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
{0, 128, 128, 128, 128, 127, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
{0, 128, 128, 128, 128, 177, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
{0, 128, 128, 128, 128, 204, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
{0, 128, 128, 128, 128, 226, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
{0, 128, 128, 128, 128, 238, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
{0, 128, 128, 128, 128, 245, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
{0, 128, 128, 128, 128, 253, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
{0, 128, 128, 128, 128, 249, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
{0, 128, 128, 128, 128, 238, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
{0, 128, 128, 128, 128, 230, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
{0, 128, 128, 128, 128, 215, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
{0, 128, 128, 128, 128, 192, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
{0, 128, 128, 128, 128, 162, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
{0, 128, 128, 128, 128, 108, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
{0, 128, 128, 128, 128, 50, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
{0, 128, 128, 128, 128, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
{0, 128, 128, 128, 128, 0, 69, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
{0, 128, 128, 128, 128, 0, 104, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
{0, 128, 128, 128, 128, 0, 135, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
{0, 128, 128, 128, 128, 0, 150, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
{0, 128, 128, 128, 128, 0, 162, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
{0, 128, 128, 128, 128, 0, 169, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
{0, 128, 128, 128, 128, 0, 173, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
{0, 128, 128, 128, 128, 0, 165, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
{0, 128, 128, 128, 128, 0, 150, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
{0, 128, 128, 128, 128, 0, 101, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
{0, 128, 128, 128, 128, 88, 16, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
{0, 128, 128, 128, 128, 132, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
{0, 128, 128, 128, 128, 165, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
{0, 128, 128, 128, 128, 184, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
{0, 128, 128, 128, 128, 200, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
{0, 128, 128, 128, 128, 208, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
{0, 128, 128, 128, 128, 211, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
{0, 128, 128, 128, 128, 200, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
{0, 128, 128, 128, 128, 184, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
{0, 128, 128, 128, 128, 158, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
{0, 128, 128, 128, 128, 116, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
{0, 128, 128, 128, 128, 66, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
{0, 128, 128, 128, 128, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
{0, 128, 128, 128, 128, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8, 0, 0, 0, },
{0, 128, 128, 128, 128, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
{0, 128, 128, 128, 128, 0, 0, 0, 0, 0, 0, 0, 0, 4, 0, 0, 0, 0, },
{0, 128, 128, 128, 128, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
{0, 128, 150, 128, 128, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
{0, 128, 197, 128, 128, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
{0, 128, 229, 128, 128, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
{0, 128, 238, 128, 128, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
{0, 128, 236, 128, 128, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
{0, 128, 221, 128, 128, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
{0, 128, 165, 128, 128, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
{0, 128, 128, 128, 128, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
{0, 128, 128, 128, 111, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
{0, 128, 128, 128, 116, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
{0, 128, 128, 128, 128, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
{0, 128, 128, 137, 128, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
{0, 128, 128, 159, 128, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
{0, 128, 128, 173, 128, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
{0, 128, 128, 182, 128, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
{0, 128, 128, 186, 128, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
{0, 128, 128, 182, 128, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
{0, 128, 128, 160, 128, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
{0, 128, 128, 128, 128, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
{0, 128, 128, 128, 128, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
{0, 128, 128, 128, 128, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5, },
{0, 128, 128, 128, 128, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, },
{0, 128, 128, 128, 128, 0, 0, 1, 2, 0, 16, 0, 0, 0, 0, 0, 0, 7, },
{0, 128, 128, 128, 128, 0, 0, 0, 2, 0, 16, 0, 0, 0, 0, 0, 0, 8, },
{0, 128, 128, 128, 128, 0, 0, 0, 2, 0, 16, 0, 0, 0, 0, 0, 0, 7, },
{0, 128, 128, 128, 128, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 6, },
{0, 128, 128, 128, 128, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 5, },
{0, 128, 128, 128, 128, 0, 0, 1, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
{0, 128, 128, 128, 128, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
{0, 128, 128, 128, 128, 0, 0, 0, 0, 0, 0, 0, 128, 0, 0, 0, 0, 0, },
{0, 128, 128, 128, 128, 88, 0, 0, 0, 0, 0, 0, 128, 0, 0, 0, 0, 0, },
{0, 128, 128, 128, 128, 150, 31, 0, 0, 0, 0, 0, 128, 0, 0, 0, 0, 0, },
{0, 128, 128, 128, 128, 184, 69, 0, 0, 0, 0, 0, 128, 0, 0, 0, 0, 0, },
{0, 128, 128, 128, 128, 192, 77, 0, 0, 0, 0, 0, 128, 0, 0, 0, 0, 0, },
{0, 128, 128, 128, 128, 208, 69, 0, 0, 0, 0, 0, 128, 0, 0, 0, 0, 0, },
{0, 128, 128, 128, 128, 211, 38, 0, 0, 0, 0, 0, 128, 0, 0, 0, 0, 0, },
{0, 128, 128, 128, 128, 215, 0, 0, 0, 0, 0, 0, 128, 0, 0, 0, 0, 0, },
{0, 128, 128, 128, 128, 200, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
{0, 128, 128, 128, 128, 169, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
{0, 128, 128, 128, 128, 84, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
{0, 128, 128, 128, 128, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, }
};
int8_t test_game_sir_message_decoder()
{
	UsbWriteString("\n\r\n\rStarting game sir message decoder test");
	uint32_t num_btn_presses = sizeof(raw_game_sir_input);
	uint32_t press_index;
	uint8_t button_index;
	uint32_t current_state_index = 0;
	for(press_index = 0; press_index < num_btn_presses; ++press_index)
	{
		GameSirNewData(raw_game_sir_input[press_index]);
		if(!press_index | press_index % (kStdMsgPkgSize + 2))
		{
			continue;
		}

		// Check the current state after a complete std msg
		for(button_index = 0; button_index < kNumBtns; ++button_index)
		{
			if(state[current_state_index][button_index] != game_sir_get_btn_value(button_index))
			{
				char buf[] = "\n\rWas X should be Y";
				buf[6] = game_sir_get_btn_value(button_index) + '0';
				buf[18] = state[current_state_index][button_index] + '0';
				UsbWriteString(buf);
				UsbWriteString("\n\rGame sir message decoder test failed!");
				return -1;
			}
		}
		current_state_index++;
	}
	
	UsbWriteString("\n\rGame sir message decoder test past!");
	return 0;
}

// main funciton
int main(void)
{
	SetupBoard();
	SetHeartbeatLed(kDebugBlueLed);
	ClearDebugLed(kDebugAllLeds);

	// Begin tests
	int8_t result = 
		test_usb() | 
		test_bluetooth() |
		test_game_sir_message_decoder();

	if(!result)
	{
		UsbWriteString("\n\r\n\rAll test complete succesfully!");
		gpio_set(GPIOD, GPIO12);
	}
	else
	{
		 UsbWriteString("\n\r\n\rSome test failed!");
		 gpio_set(GPIOD, GPIO14);
	}

	UsbWriteString("\n\rFinished");

	
	// Infinite loop
	while(true)
	{
		if(!(system_millis % 5000))
		{
		}
	}
}