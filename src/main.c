/*
 * This is the main file for Pop-a-Gator
 */
#include "board.h"


// main funciton
int main(void)
{
	setup_board();

	// Infinite loop
	uint16_t result;
	char buf[1] = {0};
	while(true)
	{
		 result = read_bluetooth(1000);
		 if(result != 0xFFFF)
		 {
		 	buf[0] = result;
		 	usb_write(buf, 1);
		 }
	}
}