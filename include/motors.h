#ifndef MOTOR_H
#define MOTOR_H

#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/timer.h>

#include "helpers.h"

// Structure that represents a motor
typedef struct {
  Pin in1_pin;
  Pin in2_pin;
  Pin pwm_pin;
  uint32_t timer;
  enum tim_oc_id  output_compare_channel;
} Motor;

enum MotorIndex {
  kMotorOne,
  kMotorTwo,

  kNumMotors
};

enum MotorDirection {
  kForward,
  kReverse,
  kFreeSpinLow,
  kFreeSpinHigh
};

static const Motor motors[] = {
  // in1,            in2,             pwm,            timmer,   output_compare_channel
  {{GPIOC, GPIO10}, {GPIOA, GPIO15}, {GPIOA, GPIO8},  TIM1,     TIM_OC1},   // Motor 1
  {{GPIOC, GPIO11}, {GPIOC, GPIO12}, {GPIOA, GPIO10}, TIM1,     TIM_OC3}    // Motor 2
  // TODO(Kevin French): Motor 3
};
// Max number of pwm ticks
//    168 MHZ / (2 * 20 KHz)
static const uint32_t kMaxPwmTicks = 4200;

void SetupMotors(void);
void MotorsSetPWM(enum MotorIndex index, uint32_t pwm);
void MotorsSetDirection(enum MotorIndex index, enum MotorDirection direction);
void MotorsStop(void);

#endif