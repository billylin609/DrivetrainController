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

uint8_t UART_rxBuffer[8];

int8_t ack_message = 0b11111111;

int8_t ack_message_check = -127;

std_return_type ack_confirmed = 0;


void UartHandshake() {
//	HAL_UART_Receive_DMA(&huart1, UART1_rxBuffer, 1);
//	while(ack_confirmed == 0) {
//		HAL_UART_Transmit(&huart1, &ack_message, 1, 200);
//	}
	HAL_UART_Receive(&huart4, UART_rxBuffer, 4, 200);
	int vertical_speed = 0;
//	if (UART_rxBuffer[1] > 100) {
//		vertical_speed = UART_rxBuffer[1]-255;
//	} else {
		vertical_speed = UART_rxBuffer[1];
//	}
	int rotation = 0;
//	if (UART_rxBuffer[2] > 100) {
//			rotation = UART_rxBuffer[2]-255;
//		} else {
			rotation = UART_rxBuffer[2];
//		}
	HAL_UART_Transmit(&huart4, &vertical_speed, 1, 200);

	arcade_drive(rotation, vertical_speed);
}

//void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {
////	if (UART1_rxBuffer[0] == ack_message_check) {
////		HAL_UART_Transmit(&huart1, &ack_message, 1, 200);
////		ack_confirmed = 1;
////	} else {
//	int8_t vertical_speed = UART1_rxBuffer[1];
//	int8_t rotation = UART1_rxBuffer[2];
//
//	arcade_drive(rotation, vertical_speed);
//	int8_t check = UART1_rxBuffer[3];
//	HAL_UART_Transmit(&huart4, &vertical_speed, 1, 200);
////	}
//	HAL_UART_Receive_DMA(&huart4, UART1_rxBuffer, 4);
//}

//Note: code barely worked -> need to look into why the negative value does not work  -> value is there not cannot be recongnized
// Code need clean up
// ping do not use dma because use timeout is more easy and efficient and after ping need to support dma
// advantage of DMA low frequency of sending the uart message
// 		suggestion: start with a new project and to get dma working
// Look into the math: assumption the negative value works but the calc pulse function does not work


