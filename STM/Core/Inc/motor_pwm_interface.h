/*
 * motor_pwm_interface.h
 *
 *  Created on: May 30, 2024
 *      Author: linyu
 */

#ifndef INC_MOTOR_PWM_INTERFACE_H_
#define INC_MOTOR_PWM_INTERFACE_H_

#include "main.h"
#include "generic_data_type.h"


#define IDLE_PULSE 4500
#define SPEED_PWM_CONVERSION_FACTOR 15

	std_return_type MotorPwmInterfaceInit();

	int32_t GetLeftSideMotorPulse();

	int32_t GetRightSideMotorPulse();

	std_return_type SetLeftSideMotorSpeed(int8_t speed);

	std_return_type SetRigthSideMotorSpeed(int8_t speed);



#endif /* INC_MOTOR_PWM_INTERFACE_H_ */
