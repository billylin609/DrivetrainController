/*
 * uart_joy_input.c
 *
 *  Created on: May 30, 2024
 *      Author: linyuchen
 */

#include "uart_joy_input.h"

/*Message Scheme
 *
 * +--------------------+------------------+-------------+--------+
 *  startbit + DEVICE ID   Vertical speed    rotation	    CRC
 */
