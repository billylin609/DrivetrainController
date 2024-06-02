/*
 * @file: motor_pwm_interface.c
 * @brief: update capture compare register and send the motor pulse for
 *
 *  Created on: May 30, 2024
 *      Author: linyuchen
 */
#include "motor_pwm_interface.h"

/*---------private data structure and methods--------------------*/
typedef struct {
	uint32_t left_side_motor_pulse;
	uint32_t right_side_motor_pulse;
} MotorPwmPulse;

static volatile MotorPwmPulse motor_output;

static uint32_t CalcPulse(int8_t speed) {
	//speed will be set to idle if invalid speed input
	if (speed >= 100 || speed <= -100) {
		speed = 0;
	}

	return speed*SPEED_PWM_CONVERSION_FACTOR+IDLE_PULSE;
}

/*--------------------------callback-----------------------------*/

void HAL_TIM_PWM_PulseFinishedCallback(TIM_HandleTypeDef *htim) {
	if(htim->Instance == htim3.Instance) {
		if(htim->Channel == HAL_TIM_ACTIVE_CHANNEL_1) {
			htim->Instance->CCR1 = GetLeftSideMotorPulse();
		} else if(htim->Channel == HAL_TIM_ACTIVE_CHANNEL_2) {
			htim->Instance->CCR2 = GetLeftSideMotorPulse();
		} else if(htim->Channel == HAL_TIM_ACTIVE_CHANNEL_3) {
			htim->Instance->CCR3= GetLeftSideMotorPulse();
		} else {
			//DO NOTHING
		}
	} else if(htim->Instance == htim4.Instance) {
		if(htim->Channel == HAL_TIM_ACTIVE_CHANNEL_1) {
			htim->Instance->CCR1 = GetRightSideMotorPulse();
		} else if(htim->Channel == HAL_TIM_ACTIVE_CHANNEL_2) {
			htim->Instance->CCR2 = GetRightSideMotorPulse();
		} else if(htim->Channel == HAL_TIM_ACTIVE_CHANNEL_3) {
			htim->Instance->CCR3= GetRightSideMotorPulse();
		} else {
			//DO NOTHING
		}
	}
}

/*---------public methods--------------------*/

std_return_type MotorPwmInterfaceInit() {
	HAL_TIM_PWM_Init(&htim3);
	HAL_TIM_PWM_Start_IT(&htim3, TIM_CHANNEL_1);
	HAL_TIM_PWM_Start_IT(&htim3, TIM_CHANNEL_2);
	HAL_TIM_PWM_Start_IT(&htim3, TIM_CHANNEL_3);
	__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, IDLE_PULSE);
	__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2, IDLE_PULSE);
	__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_3, IDLE_PULSE);

	HAL_TIM_PWM_Init(&htim4);
	HAL_TIM_PWM_Start_IT(&htim4, TIM_CHANNEL_1);
	HAL_TIM_PWM_Start_IT(&htim4, TIM_CHANNEL_2);
	HAL_TIM_PWM_Start_IT(&htim4, TIM_CHANNEL_3);
	__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_1, IDLE_PULSE);
	__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_2, IDLE_PULSE);
	__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_3, IDLE_PULSE);

	motor_output.left_side_motor_pulse = IDLE_PULSE;
	motor_output.right_side_motor_pulse = IDLE_PULSE;

	return E_OK;
}

uint32_t GetLeftSideMotorPulse() {
	return motor_output.left_side_motor_pulse;
}

uint32_t GetRightSideMotorPulse() {
	return motor_output.right_side_motor_pulse;
}

std_return_type SetLeftSideMotorSpeed(int8_t left_side_speed) {
	motor_output.left_side_motor_pulse = CalcPulse(left_side_speed);
	return E_OK;
}

std_return_type SetRightSideMotorSpeed(int8_t right_side_speed) {
	motor_output.right_side_motor_pulse = CalcPulse(right_side_speed);

	return E_OK;
}
