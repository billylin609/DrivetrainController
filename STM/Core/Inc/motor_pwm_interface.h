/*
 * motor_pwm_interface.h
 *
 *  Created on: May 30, 2024
 *      Author: linyu
 */

#ifndef INC_MOTOR_PWM_INTERFACE_H_
#define INC_MOTOR_PWM_INTERFACE_H_

#include "stdint.h"

	MotorPwmInterfaceInit();

	uint16_t GetLeftSideMotorSpeed();

	uint16_t GetRightSideMotorSpeed();

	uint8_t SetLeftSideMotorSpeed(uint8_t speed);

	uint8_t SetRigthSideMotorSpeed(uint8_t speed);

	typedef struct {
		uint16_t right_side_motor_pulse;
		uint16_t left_side_motor_pulse;
	} MotorPwmPulse;

	uint16_t CalcPulse(uint8_t speed);

#endif /* INC_MOTOR_PWM_INTERFACE_H_ */
