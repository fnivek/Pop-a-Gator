#include "motors.h"

void SetupMotors(void) {
	// Enable peripherials clocks
	rcc_periph_clock_enable(RCC_TIM1);
	rcc_periph_clock_enable(RCC_GPIOA);
	rcc_periph_clock_enable(RCC_GPIOC);

	// Timer
	// Step 1 reset peripherial:
	timer_reset(TIM1);
	// Step 2 set mode
	timer_set_mode(TIM1, TIM_CR1_CKD_CK_INT, TIM_CR1_CMS_CENTER_1,
               TIM_CR1_DIR_UP);
	// Step 3 set output compare to PWM for both channels
	timer_set_oc_mode(TIM1, TIM_OC1, TIM_OCM_PWM1);
	timer_set_oc_mode(TIM1, TIM_OC3, TIM_OCM_PWM1);
	// Step 4 enable output compare for both channels
	timer_enable_oc_output(TIM1, TIM_OC1);
	timer_enable_oc_output(TIM1, TIM_OC3);
	// Step 5 set the compare value
	timer_set_oc_value(TIM1, TIM_OC1, 0);
	timer_set_oc_value(TIM1, TIM_OC3, 0);
	// Step 6 set the period
	timer_set_period(TIM1, kMaxPwmTicks);
	// Step 7 enable break
	timer_enable_break_main_output(TIM1);
	// Step 8 enable done last

	// GPIO
	int current_motor_index;
	for(current_motor_index = 0; current_motor_index < kNumMotors; ++current_motor_index)
	{
		const Motor* motor = &motors[current_motor_index];

		// Step 1 set output options (push pull) output, no pull up or pull down
		gpio_set_output_options(motor->in1_pin.port, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, motor->in1_pin.number);
		gpio_set_output_options(motor->in2_pin.port, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, motor->in2_pin.number);
		gpio_set_output_options(motor->pwm_pin.port, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, motor->pwm_pin.number);

		// Step 2 setup mode
		gpio_mode_setup(motor->in1_pin.port, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, motor->in1_pin.number);
		gpio_mode_setup(motor->in2_pin.port, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, motor->in2_pin.number);
		gpio_mode_setup(motor->pwm_pin.port, GPIO_MODE_AF, GPIO_PUPD_NONE, motor->pwm_pin.number);
		gpio_set_af(motor->pwm_pin.port, GPIO_AF1, motor->pwm_pin.number);
	}

	// Just to be safe set motors into free spin and zero pwm
	MotorsStop();

	// Timer
	// Step 8 enable the timer
	timer_enable_counter(TIM1);

}

void MotorsSetPWM(enum MotorIndex index, uint32_t pwm) {
	const Motor* motor = &motors[index];

	if (pwm > kMaxPwmTicks) {
		pwm = kMaxPwmTicks;
	}

	timer_set_oc_value(motor->timer, motor->output_compare_channel, pwm);
}

void MotorsSetDirection(enum MotorIndex index, enum MotorDirection direction) {
	const Motor* motor = &motors[index];

	switch(direction) {
		case kForward:
			gpio_set(motor->in1_pin.port, motor->in1_pin.number);
			gpio_clear(motor->in2_pin.port, motor->in2_pin.number);
			break;
		case kReverse:
			gpio_clear(motor->in1_pin.port, motor->in1_pin.number);
			gpio_set(motor->in2_pin.port, motor->in2_pin.number);
			break;
		case kFreeSpinLow:
			gpio_clear(motor->in1_pin.port, motor->in1_pin.number);
			gpio_clear(motor->in2_pin.port, motor->in2_pin.number);
			break;
		case kFreeSpinHigh:
			gpio_set(motor->in1_pin.port, motor->in1_pin.number);
			gpio_set(motor->in2_pin.port, motor->in2_pin.number);
			break;
		default:
			// Error!!!!
			break;
	}
}

void MotorsStop(void) {
	uint8_t index;
	for(index = 0; index < kNumMotors; ++index) {
		MotorsSetDirection(index, kFreeSpinLow);
		MotorsSetPWM(index, 0);
	}
}