/*
 * callback.c
 *
 *  Created on: Dec 6, 2022
 *      Author: kiarashvosough
 */

#include "main.h"
#include "elevator_state.h"
#include "stm32f3xx_hal_uart.h"
#include "admin.h"

int last_pressed_time = 0;
extern Elevator_State state;
extern Admin admin;
extern uint8_t data[10];
extern UART_HandleTypeDef huart2;


void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	 int duration = HAL_GetTick() - last_pressed_time;
	 if (duration > 500) {
		 last_pressed_time = HAL_GetTick();
	 } else {
		 return;
	 }

	if(GPIO_Pin == GPIO_PIN_6) {
		if(state.floor_should_go == 9) { return; }
		state.floor_should_go += 1;
	} else if(GPIO_Pin == GPIO_PIN_7) {
		if(state.floor_should_go == 0) { return; }
		state.floor_should_go -= 1;
	} else if(GPIO_Pin == GPIO_PIN_8) { // apply floor
		add_new_floor_to_queue(&state, false);
	} else if(GPIO_Pin == GPIO_PIN_9) { // buzzer
		toggle_buzzer(&state);
	}
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{

	if(huart->Instance == USART2) {
		perform_admin_action(&state, &admin, data);
	}

	HAL_UART_Receive_IT(&huart2, data, 10);
}

