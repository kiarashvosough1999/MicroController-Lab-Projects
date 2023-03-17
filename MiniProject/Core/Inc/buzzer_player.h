/*
 * buzzer_player.h
 *
 *  Created on: Dec 5, 2022
 *      Author: kiarashvosough
 */

#ifndef INC_BUZZER_PLAYER_H_
#define INC_BUZZER_PLAYER_H_

#include "stm32f3xx_hal.h"
#include "bool.h"

typedef struct {
	TIM_HandleTypeDef *buzzerPwmTimer;
	int buzzerPwmChannel;
	int last_time_played;
	int play_duration;
} Buzzer_Player;

void init_buzzer_player(Buzzer_Player* player, TIM_HandleTypeDef *buzzerPwmTimer, int buzzerPwmChannel);

void buzzer_player_start(Buzzer_Player* player,uint16_t freq, uint16_t volume);

bool should_start_playing(Buzzer_Player* player);

void buzzer_player_stop(Buzzer_Player* player);

#endif /* INC_BUZZER_PLAYER_H_ */
