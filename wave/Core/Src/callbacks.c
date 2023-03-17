/*
 * callbacks.c
 *
 *  Created on: Dec 30, 2022
 *      Author: kiarashvosough
 */

#include "main.h"
#include <math.h>

void find_button(uint16_t GPIO_Pin);
typedef enum {
	zero, one, two, three, four, five, six, seven, eight, nine, A, B, C, D, hashtag, star
} Buttons;

double sin_counter = 0;
double cos_counter = 0;
int square_counter = 0;

double sin_value = 0;
double cos_value = 0;
double square_value = 0;
int last_key_pressed = -1;

int last_time;

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
	if (htim->Instance == TIM4) {
		int duration = HAL_GetTick() - last_time;
		if (duration >= 50) {
			HAL_GPIO_TogglePin(GPIOE, GPIO_PIN_8);
			sin_value = sin(sin_counter);
			cos_value = cos(cos_counter);
			square_value = sqrt(square_counter);

			sin_counter += 0.1;
			cos_counter += 0.1;
			square_counter += 10;
			last_time = HAL_GetTick();
		}
	}
}

////////////////////////////////////////////////////////////////
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {

    if (GPIO_Pin == GPIO_PIN_0) {
    	find_button(GPIO_Pin);
    } else if (GPIO_Pin == GPIO_PIN_1) {
    	find_button(GPIO_Pin);
    } else if (GPIO_Pin == GPIO_PIN_2) {
    	find_button(GPIO_Pin);
    } else if (GPIO_Pin == GPIO_PIN_3) {
    	find_button(GPIO_Pin);
    }
}

void find_button(uint16_t GPIO_Pin) {
	for (int i = 0; i < 4; i++) {
		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_4, 0);
		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_5, 0);
		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_6, 0);
		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_7, 0);

		if (i == 0) { // checking row 0
			HAL_GPIO_WritePin(GPIOD, GPIO_PIN_7, 1);
			if (HAL_GPIO_ReadPin(GPIOD, GPIO_Pin) == 1) { // column 0
				if (GPIO_Pin == GPIO_PIN_0) { // A
					last_key_pressed = 100;
				} else if (GPIO_Pin == GPIO_PIN_1) { // 3
					last_key_pressed = 3;
				} else if (GPIO_Pin == GPIO_PIN_2) { // 2
					last_key_pressed = 2;
				} else if (GPIO_Pin == GPIO_PIN_3) { // 1
					last_key_pressed = 1;
				}
			}
		} else if (i == 1) { // checking row 1
			HAL_GPIO_WritePin(GPIOD, GPIO_PIN_6, 1);
			if (HAL_GPIO_ReadPin(GPIOD, GPIO_Pin) == 1) { // column 1
				if (GPIO_Pin == GPIO_PIN_0) { // A
					last_key_pressed = 150;
				} else if (GPIO_Pin == GPIO_PIN_1) { // 3
					last_key_pressed = 6;
			    } else if (GPIO_Pin == GPIO_PIN_2) { // 2
			    	last_key_pressed = 5;
				} else if (GPIO_Pin == GPIO_PIN_3) { // 1
					last_key_pressed = 4;
				}
			}
		} else if (i == 2) { // checking row 2
			HAL_GPIO_WritePin(GPIOD, GPIO_PIN_5, 1);
			if (HAL_GPIO_ReadPin(GPIOD, GPIO_Pin) == 1) { // column 2
				if (GPIO_Pin == GPIO_PIN_0) { // A
					last_key_pressed = 160;
				} else if (GPIO_Pin == GPIO_PIN_1) { // 3
					last_key_pressed = 9;
			    } else if (GPIO_Pin == GPIO_PIN_2) { // 2
			    	last_key_pressed = 8;
				} else if (GPIO_Pin == GPIO_PIN_3) { // 1
					last_key_pressed = 7;
				}
			}
		} else if (i == 3) { // checking row 3
			HAL_GPIO_WritePin(GPIOD, GPIO_PIN_4, 1);
			if (HAL_GPIO_ReadPin(GPIOD, GPIO_Pin) == 1) { // column 3
				if (GPIO_Pin == GPIO_PIN_0) { // A
					last_key_pressed = 170;
				} else if (GPIO_Pin == GPIO_PIN_1) { // 3
					last_key_pressed = 180;
			    } else if (GPIO_Pin == GPIO_PIN_2) { // 2
			    	last_key_pressed = 0;
				} else if (GPIO_Pin == GPIO_PIN_3) { // 1
					last_key_pressed = 190;
				}
			}
		}
	}
	  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_4, 1);
	  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_5, 1);
	  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_6, 1);
	  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_7, 1);
	  while(HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_0));
}



