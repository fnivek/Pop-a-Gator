#Pop-a-Gator

##Pinout
* Bluetooth
  * PA2 (UART2 TX) ---> JY-MCU Rx
  * PA3 (UART2 RX) <--- JY-MCU Tx (Don't forget 3.3V pullup resistor)

* Debug LEDs
  * PD12 ---> Green LED
  * PD13 ---> Orange LED
  * PD14 ---> Red LED
  * PD15 ---> Blue LED

* USB OTG
  * PA9 ?---? TODO
  * PA11 ?---? TODO
  * PA12 ?---? TODO

* Motors
  * Motor 1
    * PC10 ---> IN1
    * PA15 ---> IN2
    * PA8 ---> PWM
  * Motor 2
    * PC11 ---> IN1
    * PC12 ---> IN2
    * PA10 ---> PWM
  * Motor 3
    * TODO
