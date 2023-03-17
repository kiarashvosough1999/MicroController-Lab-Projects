/*
 * buzzer_player.c
 *
 *  Created on: Dec 5, 2022
 *      Author: kiarashvosough
 */


#include "buzzer_player.h"

void init_buzzer_player(Buzzer_Player* player, TIM_HandleTypeDef *buzzerPwmTimer, int buzzerPwmChannel) {
	Buzzer_Player _player = {
			buzzerPwmTimer,
			buzzerPwmChannel,
			250
	};
	*player = _player;
}

void buzzer_player_start(Buzzer_Player* player,uint16_t freq, uint16_t volume) {

	if (freq == 0 || freq > 20000) {
		__HAL_TIM_SET_COMPARE(player->buzzerPwmTimer, player->buzzerPwmChannel, 0);
	} else {
		const uint32_t internalClockFreq = HAL_RCC_GetSysClockFreq();
		const uint32_t prescaler = 1 + internalClockFreq / freq / 60000;
		const uint32_t timerClock = internalClockFreq / prescaler;
		const uint32_t periodCycles = timerClock / freq;
		const uint32_t pulseWidth = volume * periodCycles / 1000 / 2;

		player->buzzerPwmTimer->Instance->PSC = prescaler - 1;
		player->buzzerPwmTimer->Instance->ARR = periodCycles - 1;
		player->buzzerPwmTimer->Instance->EGR = TIM_EGR_UG;

		__HAL_TIM_SET_COMPARE(player->buzzerPwmTimer, player->buzzerPwmChannel, pulseWidth);
	}
}

void buzzer_player_stop(Buzzer_Player* player) {
	__HAL_TIM_SET_COMPARE(player->buzzerPwmTimer, player->buzzerPwmChannel, 0);
}

bool should_start_playing(Buzzer_Player* player) {
	int duration = HAL_GetTick() - player->last_time_played;
	if (duration > 250) {
		player->last_time_played = HAL_GetTick();
		return true;
	} else {
		return false;
	}
}










