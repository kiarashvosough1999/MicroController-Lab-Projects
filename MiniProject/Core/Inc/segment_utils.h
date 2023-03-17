/*
 * segment_utils.h
 *
 *  Created on: Dec 5, 2022
 *      Author: kiarashvosough
 */

#ifndef INC_SEGMENT_UTILS_H_
#define INC_SEGMENT_UTILS_H_

#include "stm32f3xx_hal.h"

typedef enum Segment {
	A,
	B,
	C,
	D,
	None
} Segment;

typedef struct {

	GPIO_TypeDef* GPIOx;

	uint16_t GPIO_Pin_BCD_A; // E14
	uint16_t GPIO_Pin_BCD_B; // E13
	uint16_t GPIO_Pin_BCD_C; // E12
	uint16_t GPIO_Pin_BCD_D; // E11

	uint16_t GPIO_Pin_SEG_A; // E7
	uint16_t GPIO_Pin_SEG_B; // E8
	uint16_t GPIO_Pin_SEG_C; // E9
	uint16_t GPIO_Pin_SEG_D; // E10

} Segment_Display;

void init_segment_display(Segment_Display* display);

void decToBinary(int* array, int n);

void showNumber(int number, Segment_Display* display);

void resetAndEnableSegment(Segment segment, Segment_Display* display);

void turn_on_onboard_leds();

void turn_off_onboard_leds();

#endif /* INC_SEGMENT_UTILS_H_ */
