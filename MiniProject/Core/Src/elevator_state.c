/*
 * elevator_state.c
 *
 *  Created on: Dec 6, 2022
 *      Author: kiarashvosough
 */

#include "elevator_state.h"
#include "stm32f3xx_hal.h"
#include "floor.h"

void init_elevator_state(Elevator_State* state) {

	Queue floor_selection_queue;

	queue_init(&floor_selection_queue);

	Elevator_State new_detail = {
			9, // max_floor
			0, // current_floor
			-1, // floor_should_go
			false, // buzzer_enabled
			true, // led_enabled
			floor_selection_queue,
			{}, // floor_details
			0, // last_floor_detail_index
			0, // time_should_wait_on_floor
			0, // time_reach_the_floor
			false, //is_waiting_on_floor
			1000, // between_floor_duration
	};
	*state = new_detail;
}

void set_max_floor(Elevator_State* state, int max_floor) {
	if (max_floor < 0 || max_floor > 9) { return; }
	state->max_floor = max_floor;
	state->floor_should_go = -1;
	if (state->current_floor >= max_floor) { // in case that new max is less than current set floor
		state->current_floor = 0;
	}
}

void set_current_floor(Elevator_State* state, int current_floor) {
	if (current_floor < 0 || current_floor >= state->max_floor) { return; }
	state->current_floor = current_floor;
}

void set_between_floor_duration(Elevator_State* state, int duration) {
	if(duration < 500 && duration > 5000) { return; }
	state->between_floor_duration = duration;
}

void toggle_buzzer(Elevator_State* state) {
	state->buzzer_enabled = state->buzzer_enabled == true ? false : true;
}

void toggle_led(Elevator_State* state) {
	state->led_enabled = state->led_enabled == true ? false : true;
}

bool is_buzzer_enabled(Elevator_State* state) {
	return state->buzzer_enabled;
}

void append_floor_detail(Elevator_State* state) {
	Floor_Detail new_floor_detail = {
			state->last_floor_detail_index,
			4000 // 4s to wait on each floor
	};
	state->floor_details[state->last_floor_detail_index] = new_floor_detail;

	state->last_floor_detail_index += 1;
}

void set_floor_waiting_time(Elevator_State* state, int floor_index, int waiting_time) {
	state->floor_details[floor_index].waiting_time = waiting_time;
}

bool should_go_to_next_floor(Elevator_State* state) {
	return state->is_waiting_on_floor == true ? false : true;
}

void check_next_floor(Elevator_State* state) {

	// is queue is empty nothing should be done and if we are still waiting on one floor
	if (queue_is_queue_empty(&state->floor_selection_queue) == false && state->is_waiting_on_floor == false) {
		go_to_next_floor(state);
	} else if (state->is_waiting_on_floor == true) {
		// if we are waiting on a floor, we should check if the time of waiting has reached the end
		check_floor_waiting_time_ended(state);
	}

}

void check_floor_waiting_time_ended(Elevator_State* state) {
	int duration_until_now = HAL_GetTick() - state->time_reach_the_floor;
	if (duration_until_now >= state->time_should_wait_on_floor) {
		state->time_should_wait_on_floor = -1;
		state->time_reach_the_floor = -1;
		state->is_waiting_on_floor = false;
	}
}

bool is_floor_valid(Elevator_State* state, int floor) {
	return state->max_floor > floor && floor >= 0 && state->current_floor != floor ? true : false;
}

bool is_floor_valid_test(Elevator_State* state, int current_floor, int floor) {
	return state->max_floor > floor && floor >= 0 && current_floor != floor ? true : false;
}

void go_to_next_floor(Elevator_State* state) {
	Floor floor = queue_deQueue(&state->floor_selection_queue);

	if(floor.floor_index == -1) { return; } // queue is empty

	if (is_floor_valid(state, floor.floor_index) == true) { // check if the floor is valid

		int time_should_wait_on_floor = state->between_floor_duration;
		if(floor.is_target_floor == true) { // for target floor which elevator door open and wait
			time_should_wait_on_floor += state->floor_details[floor.floor_index].waiting_time;
		}

		state->time_should_wait_on_floor = time_should_wait_on_floor; // set the time need to be waited
		state->time_reach_the_floor = HAL_GetTick(); // set the current time floor is reached.
		state->current_floor = floor.floor_index;
		state->is_waiting_on_floor = true;
	}
}

void add_new_floor_to_queue(Elevator_State* state, bool on_test) {

	// in case that user inputed invalid floor
	if (is_floor_valid(state, state->floor_should_go) == false && on_test == false) { return; }


	int current_floor = -1;
	int last_on_queue = queue_rear_value(&state->floor_selection_queue);
	if(on_test == true && last_on_queue != -1) {
		current_floor = last_on_queue;
	} else {
		current_floor = state->current_floor;
	}

	if (is_floor_valid_test(state, current_floor, state->floor_should_go) == false && on_test == true)  { return; }

	if(on_test == true && queue_has_item_with_floor_index(&state->floor_selection_queue, state->floor_should_go) == true) {
		queue_change_item_with_floor_index_to_target(&state->floor_selection_queue, state->floor_should_go);
		return;
	}

	if(current_floor > state->floor_should_go) { // elevator goes down
		// ex: current_floor = 9, floor_should_go = 5
		// start from 8, end when reach 5
		for (int i = current_floor - 1; i >= state->floor_should_go; --i) {

			// means that the floor is currently on queue while elevator is going down.
			if(queue_has_item_with_floor_index(&state->floor_selection_queue, i) == true && i == state->floor_should_go) {
				queue_change_item_with_floor_index_to_target(&state->floor_selection_queue, i);
			} else {
				Floor floor;
				init_floor(&floor, i, i == state->floor_should_go ? true : false);
				queue_enQueue(&state->floor_selection_queue, floor);
			}
		}
	} else { // elevator goes up
		// ex: current_floor = 5, floor_should_go = 9
		// start from 6, end when reach 9
		for (int i = current_floor + 1; i <= state->floor_should_go; ++i) {
			if(queue_has_item_with_floor_index(&state->floor_selection_queue, i) == true && i == state->floor_should_go) {
				queue_change_item_with_floor_index_to_target(&state->floor_selection_queue, i);
			} else {
				Floor floor;
				init_floor(&floor, i, i == state->floor_should_go ? true : false);
				queue_enQueue(&state->floor_selection_queue, floor);
			}
		}
	}
	state->floor_should_go = -1;
}





