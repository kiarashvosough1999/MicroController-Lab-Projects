/*
 * callback.c
 *
 *  Created on: Dec 6, 2022
 *      Author: kiarashvosough
 */

#include "main.h"
#include "LiquidCrystal.h"
#include "buzzer_player.h"
#include "stdio.h"
#include <string.h>

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{

	if(GPIO_Pin == GPIO_PIN_7) {
		HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_8);
		HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_9);
		extern RTC_HandleTypeDef hrtc;
		extern bool had_movment;
		extern Buzzer_Player player;
		RTC_TimeTypeDef time;
		RTC_DateTypeDef rtcDate;
		char date_string[10];
		char time_string[10];

		  HAL_RTC_GetTime(&hrtc, &time, RTC_FORMAT_BIN);
		  HAL_RTC_GetDate(&hrtc, &rtcDate, RTC_FORMAT_BIN);
		  setCursor(0, 0);
		  sprintf(date_string, "%d/%d/%d", rtcDate.Year, rtcDate.Month, rtcDate.Date);
		  print(date_string);

		  setCursor(0, 1);
		  sprintf(time_string, "%d:%d:%d", time.Hours, time.Minutes, time.Seconds);
		  if (time.Seconds < 10) {
			  strcat(time_string, "    ");
		  }
		  print(time_string);
		if(HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_7) == 1) { // movement
			had_movment = true;
			buzzer_player_start(&player, 1000, 100);
			  setCursor(0, 2);
			  print("Movement Detected");
		} else {
			had_movment = false;
			  setCursor(0, 2);
			  print("No Movement Detected");
		}
	}
}

