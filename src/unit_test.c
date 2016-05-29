#include "board.h"

// Test USB debug comms
int8_t test_usb(void)
{
	while(!is_usb_ready());

	usb_write_string("\n\r\n\rStarting USB test\n\rPlease type pop...\n\r\t");
	usb_write_string("\n\rTODO: Write a USB read funciton");
	usb_write_string("\n\rUSB test results: Unkown");
	return -1;
}

// Test the bluetooth module
int8_t test_bluetooth(void)
{
	// Clear read
	flush_bluetooth_input();

	usb_write_string("\n\r\n\rStart bluetooth test");
	usb_write_string("\n\rWriting AT to bluetooth chip\n\r");

	char buf[] = "Bluetooth chip replied w/: ##";
	// Write AT
	write_bluetooth('A');
	write_bluetooth('T');

	// Read result
	uint16_t data = read_bluetooth(1000);
	buf[27] = data;
	data = read_bluetooth(1000);
	buf[28] = data;
	usb_write(buf, sizeof(buf));

	if( buf[27] == 'O' && buf[28] == 'K' )
	{
		usb_write_string("\n\rBluetooth test past!");
		return 0;
	}
	else
	{
		usb_write_string("\n\rBluetooth test failed!");
		return -1;
	}

}

// main funciton
int main(void)
{
	setup_board();

	// Begin tests
	int8_t result = 
		test_usb() | 
		test_bluetooth();

	if(!result)
	{
		usb_write_string("\n\r\n\rAll test complete succesfully!");
		gpio_set(GPIOD, GPIO12);
	}
	else
	{
		 usb_write_string("\n\r\n\rSome test failed!");
		 gpio_set(GPIOD, GPIO14);
	}

	usb_write_string("\n\rFinished");

	
	// Infinite loop
	while(true)
	{
		if(!(system_millis % 5000))
		{
		}
	}
}