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

const uint8_t handshake_message = {0b10000001};

void UartHandshake() {
	while(UART_rxBuffer[0] != 1) {
		HAL_UART_Receive(&huart4, UART_rxBuffer, 1, 200);
	}

	HAL_UART_Transmit(&huart4, &handshake_message, 1, 200);

	HAL_UART_Receive_DMA(&huart4, UART_rxBuffer, 4);
	HAL_GPIO_TogglePin(GPIOA, LL_GPIO_PIN_9);
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {
	//TODO: kick the watchdog if the heartbeat message does not receive properly

	//Implemented the Handshake protocol ground station -> stm -> ground station
	//TODO: Implement the full CRC8
	//Implemented header checker
	//TODO: Implement boundary check
	//TODO: define return message scheme

	/*
	 * Note: LED red == waiting handshake to be complete
	 * 		 LED green == update the watchdog with data input
	 */

	/*--------------------- Note: Debugger does not work with dma use HAL transmit ack ------------------*/
	if(UART_rxBuffer[0] == 0x81) {
		if(UART_rxBuffer[1] == 0x03) {
			//joystick message
			int8_t vertical_speed = UART_rxBuffer[2];
			int8_t rotation = UART_rxBuffer[3];

			arcade_drive(rotation, vertical_speed);

			uint8_t ack_rx_buffer[2] = {vertical_speed, rotation};
			HAL_UART_Transmit(&huart4, ack_rx_buffer, 2, 200);

			/*watchdog heart beat feature*/
			HAL_GPIO_TogglePin(GPIOC, LL_GPIO_PIN_7);
			if (HAL_IWDG_Refresh(&hiwdg) != HAL_OK) {
			  Error_Handler();
			}
			HAL_GPIO_TogglePin(GPIOC, LL_GPIO_PIN_7);
		}
		HAL_UART_Receive_DMA(&huart4, UART_rxBuffer, 4);
	} else {
	}

	HAL_UART_Receive_DMA(&huart4, UART_rxBuffer, 4);
}



