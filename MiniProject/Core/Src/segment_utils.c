/*
 * segment_utils.c
 *
 *  Created on: Dec 5, 2022
 *      Author: kiarashvosough
 */


#include "segment_utils.h"

void init_segment_display(Segment_Display* display) {
	Segment_Display new_display = {
			GPIOD,

			GPIO_PIN_3,
			GPIO_PIN_4,
			GPIO_PIN_5,
			GPIO_PIN_6,

			GPIO_PIN_2,
			GPIO_PIN_8, // not used
			GPIO_PIN_9, // not used
			GPIO_PIN_1
	};
	*display = new_display;
}

void decToBinary(int* array, int n) {
    for (int i = 3; i >= 0; i--) {
        int k = n >> i;
        if (k & 1) array[i] = 1;
        else array[i] = 0;
    }
}

void showNumber(int number, Segment_Display* display) {
	 int arr[4] = {0};
	 decToBinary(arr, number);

	 int bcd_A = arr[0];
	 int bcd_B = arr[1];
	 int bcd_C = arr[2];
	 int bcd_D = arr[3];

	 HAL_GPIO_WritePin(display->GPIOx, display->GPIO_Pin_BCD_D, bcd_D);
	 HAL_GPIO_WritePin(display->GPIOx, display->GPIO_Pin_BCD_C, bcd_C);
	 HAL_GPIO_WritePin(display->GPIOx, display->GPIO_Pin_BCD_B, bcd_B);
	 HAL_GPIO_WritePin(display->GPIOx, display->GPIO_Pin_BCD_A, bcd_A);
}

void resetAndEnableSegment(Segment segment, Segment_Display* display) {
    HAL_GPIO_WritePin(
    		display->GPIOx,
			display->GPIO_Pin_SEG_A | display->GPIO_Pin_SEG_B  | display->GPIO_Pin_SEG_C  | display->GPIO_Pin_SEG_D
			, 1
			);

    switch(segment) {
    case A: HAL_GPIO_WritePin(display->GPIOx, display->GPIO_Pin_SEG_A, 0); break;
    case B: HAL_GPIO_WritePin(display->GPIOx, display->GPIO_Pin_SEG_B, 0); break;
    case C:	HAL_GPIO_WritePin(display->GPIOx, display->GPIO_Pin_SEG_C, 0); break;
    case D:	HAL_GPIO_WritePin(display->GPIOx, display->GPIO_Pin_SEG_D, 0); break;
    case None: break;
    }
}

void turn_on_onboard_leds() {
	HAL_GPIO_WritePin(
			GPIOE,
			GPIO_PIN_8 | GPIO_PIN_9 | GPIO_PIN_10 | GPIO_PIN_11 | GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15,
			1
			);
}

void turn_off_onboard_leds() {
	HAL_GPIO_WritePin(
			GPIOE,
			GPIO_PIN_8 | GPIO_PIN_9 | GPIO_PIN_10 | GPIO_PIN_11 | GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15,
			0
			);
}





