/*
 * @file: arcade_controller.c
 * @brief: The file convert the joystick input into [-100, 100] mapping for left side motor and right side motor
 *
 *  Created on: May 30, 2024
 *      Author: linyuchen
 */


#include "arcade_controller.h"

#define max(a,b)             \
({                           \
    __typeof__ (a) _a = (a); \
    __typeof__ (b) _b = (b); \
    _a > _b ? _a : _b;       \
})


std_return_type arcade_drive(int8_t rotate, int8_t vertical_speed){
    /*Drives the robot using arcade drive.
     *Note: the input from UART interface need to be converted to -100 to 100 before function call
     * */
    /* variables to determine the quadrants*/

	if(rotate > 100 || vertical_speed > 100){
		return E_NOT_OK;
	}

    int8_t maximum = max(abs(rotate), abs(vertical_speed));
    int8_t total = vertical_speed + rotate;
    int8_t difference = vertical_speed - rotate;

    /*set speed according to the quadrant that the values are in*/
    if (vertical_speed >= 0){
        if (rotate >= 0){ // I quadrant
        	SetLeftSideMotorSpeed(maximum);
        	SetRigthSideMotorSpeed(difference);
        } else{            // II quadrant
        	SetLeftSideMotorSpeed(total);
        	SetRigthSideMotorSpeed(maximum);
        }
    } else{
        if (rotate >= 0){  // IV quadrant
        	SetLeftSideMotorSpeed(total);
        	SetRigthSideMotorSpeed(-maximum);
        } else{           // III quadrant
        	SetLeftSideMotorSpeed(-maximum);
        	SetRigthSideMotorSpeed(difference);
        }
    }

    return E_OK;
}
