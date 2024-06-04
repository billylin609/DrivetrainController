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
 *  startbit + DEVICE ID   Vertical speed    rotation	    CRC 8
 */

uint8_t UART_rxBuffer[4];

void UartHandshake() {
	HAL_UART_Receive_DMA(&huart4, UART_rxBuffer, 4);
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {
	//TODO: Implement the Handshake protocol stm -> ground station -> stm
	//TODO: Implement the full CRC8
	//TODO: Implement header checker
	//TODO: Implement boundary check
	//TODO: define return message scheme

	/*--------------------- Note: Debugger does not work with dma use HAL transmit ack ------------------*/
	int8_t vertical_speed = UART_rxBuffer[1];
	int8_t rotation = UART_rxBuffer[2];

	arcade_drive(rotation, vertical_speed);

	uint8_t ack_rx_buffer[2] = {vertical_speed, rotation};
	HAL_UART_Transmit(&huart4, ack_rx_buffer, 2, 200);

	HAL_UART_Receive_DMA(&huart4, UART_rxBuffer, 4);
}



