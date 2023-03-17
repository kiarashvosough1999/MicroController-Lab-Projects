/*
 * elevator_state.h
 *
 *  Created on: Dec 5, 2022
 *      Author: kiarashvosough
 */

#ifndef INC_ELEVATOR_STATE_H_
#define INC_ELEVATOR_STATE_H_

#include "queue.h"
#include "bool.h"
#include "floor_detail.h"

typedef struct {

	int max_floor;
	int current_floor;

	int floor_should_go;

	bool buzzer_enabled;
	bool led_enabled;

	Queue floor_selection_queue;

	Floor_Detail floor_details[100];
	int last_floor_detail_index;

	int time_should_wait_on_floor;
	int time_reach_the_floor;
	bool is_waiting_on_floor;
	int between_floor_duration;

} Elevator_State;


void check_floor_waiting_time_ended(Elevator_State* state);

void go_to_next_floor(Elevator_State* state);

void init_elevator_state(Elevator_State* state);

void set_max_floor(Elevator_State* state, int max_floor);

void set_current_floor(Elevator_State* state, int current_floor);

void set_between_floor_duration(Elevator_State* state, int duration);

void toggle_buzzer(Elevator_State* state);

void toggle_led(Elevator_State* state);

bool is_buzzer_enabled(Elevator_State* state);

void append_floor_detail(Elevator_State* state);

void set_floor_waiting_time(Elevator_State* state, int floor_index, int waiting_time);

bool should_go_to_next_floor(Elevator_State* state);

void check_next_floor(Elevator_State* state);

void add_new_floor_to_queue(Elevator_State* state, bool on_test);


#endif /* INC_ELEVATOR_STATE_H_ */
