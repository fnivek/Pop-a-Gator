# Pop-a-Gator

## Important notes
* If using one of the programing pins (such as PA13) you must boot into a different memory to flash (boot0 jumper to vdd)
* You must make clean if you only update a header file

## Pinout
* Bluetooth
  * PA2 (UART2 TX) ---> JY-MCU Rx
  * PA3 (UART2 RX) <--- JY-MCU Tx (Don't forget 3.3V pullup resistor)

* Debug LEDs
  * PD12 ---> Green LED
  * PD13 ---> Orange LED
  * PD14 ---> Red LED
  * PD15 ---> Blue LED

* Motors
  * Motor 1
    * PC10 ---> IN1
    * PA15 ---> IN2
    * PA8 ---> PWM
  * Motor 2
    * PE12 ---> IN1
    * PE13 ---> IN2
    * PE11 ---> PWM
  * Motor 3
    * PC11 ---> IN1
    * PC12 ---> IN2
    * PA10 ---> PWM

## Disabled systems
* USB OTG
  * PA9 ?---? TODO
  * PA11 ?---? TODO
  * PA12 ?---? TODO