/*
 * led_utils.c
 *
 *  Created on: Dec 13, 2022
 *      Author: kiarashvosough
 */

#include "led_utils.h"
#include "stm32f3xx_hal.h"

void init_led_util(LED_Util *led_util) {
	LED_Util new_led_util = {
			false,
			false,
			false
	};
	*led_util = new_led_util;
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_8, 0);
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_9, 0);
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_10, 0);
}

void led_util_change_led_state(LED_Util *led_util, LED_Type type, bool state) {
	switch (type) {
	case green:
		led_util->is_green_led_on = state;
		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_8, state);
		break;
	case yellow:
		led_util->is_yellow_led_on = state;
		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_9, state);
		break;
	case red:
		led_util->is_red_led_on = state;
		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_10, state);
		break;
	}
}
