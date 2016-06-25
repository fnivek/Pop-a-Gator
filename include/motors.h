#ifndef MOTOR_H
#define MOTOR_H

#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/timer.h>

#include "helpers.h"

// Structure that represents a motor
typedef struct {
	Pin in1;
	Pin in2;
	Pin pwm;
	uint32_t timer;
	enum tim_oc_id	output_compare_channel;
} Motor;

enum Motor {
	kLeftMotor,
	kRightMotor,

	kNumMotors
};

enum MotorDirection {
	kForward,
	kReverse,
	kFreeSpinLow,
	kFreeSpinHigh
};

static const Motor motors[] = {
	//in1,				in2,			pwm,			timmer,		output_compare_channel
	{{GPIOC, GPIO10}, {GPIOA, GPIO15}, {GPIOA, GPIO8}, 	TIM1, 		TIM_OC1},		// Left motor
	{{GPIOC, GPIO11}, {GPIOC, GPIO12}, {GPIOA, GPIO10}, TIM1, 		TIM_OC3}		// Right motor
};
// Max number of pwm ticks 
//		168 MHZ / (2 * 20 KHz) 
static const uint32_t kMaxPwmTicks = 4200;

void SetupMotors(void);
void MotorsSetPWM(Motor motor, uint32_t pwm);
void MotorsSetDirection(Motor motor, enum MotorDirection direction);

#endif