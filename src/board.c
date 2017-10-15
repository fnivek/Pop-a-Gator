#include "board.h"

void SetupBoard(void) {
	// Setup clock
	rcc_clock_setup_hse_3v3(&rcc_hse_8mhz_3v3[RCC_CLOCK_3V3_168MHZ]);

	// Setup components
	SetupDebugLeds();
	// SetupUsb();
	SetupBluetooth();
	SetupSystick();
	SetupMotors();

	// Setup connections
	BluetoothAddCb(BluetoothToGameSir);
}

void BluetoothToGameSir(void) {
	GameSirNewData(BluetoothRead());
}