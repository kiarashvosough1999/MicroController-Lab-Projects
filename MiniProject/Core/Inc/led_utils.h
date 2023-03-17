/*
 * led_utils.h
 *
 *  Created on: Dec 13, 2022
 *      Author: kiarashvosough
 */

#ifndef INC_LED_UTILS_H_
#define INC_LED_UTILS_H_

#include "bool.h"

typedef struct {
	bool is_green_led_on;
	bool is_yellow_led_on;
	bool is_red_led_on;
} LED_Util;

typedef enum {
	green,
	yellow,
	red
} LED_Type;

void init_led_util(LED_Util *led_util);

void led_util_change_led_state(LED_Util *led_util, LED_Type type, bool state);

#endif /* INC_LED_UTILS_H_ */
