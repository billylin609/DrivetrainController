/*
 * motor_pwm_interface.h
 *
 *  Created on: May 30, 2024
 *      Author: linyu
 */

#ifndef INC_MOTOR_PWM_INTERFACE_H_
#define INC_MOTOR_PWM_INTERFACE_H_

#include "stdint.h"

typedef uint8_t std_return_type;
#define E_OK 1
#define E_NOT_OK 0
#define IDLE_PULSE 1500
#define SPEED_PWM_CONVERSION_FACTOR 5

	std_return_type MotorPwmInterfaceInit();

	int32_t GetLeftSideMotorPulse();

	int32_t GetRightSideMotorPulse();

	std_return_type SetLeftSideMotorSpeed(int8_t speed);

	std_return_type SetRigthSideMotorSpeed(int8_t speed);



#endif /* INC_MOTOR_PWM_INTERFACE_H_ */
