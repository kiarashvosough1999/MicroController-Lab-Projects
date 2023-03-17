/*
 * admin.c
 *
 *  Created on: Dec 12, 2022
 *      Author: kiarashvosough
 */

#include "admin.h"
#include "bool.h"
#include "stdio.h"
#include "stdlib.h"
#include "led_utils.h"
#include <ctype.h>
#include "utils.h"
#include "message_sender.h"

extern LED_Util led_util;

void init_admin(Admin* admin) {
	Admin new_admin = {
			1234,
			false
	};
	*admin = new_admin;
}

bool is_on_admin_mode(Admin* admin) {
	return admin->on_admin_mode;
}

bool can_switch_to_admin_mode(Elevator_State* state, Admin* admin) {
	if(queue_is_queue_empty(&state->floor_selection_queue) == true && admin->on_admin_mode == false) {
		return true;
	} else {
		return false;
	}
}

void exit_admin(Admin* admin) {
	if (admin->on_admin_mode == false) { return; }
	admin->on_admin_mode = false;
	led_util_change_led_state(&led_util, red, false);
}

void enter_admin(Admin* admin, char data[10]) {
	int password = 0;
	sscanf(data, "ADMIN#%d", &password);
	if (password == admin->password) {
		admin->on_admin_mode = true;
		led_util_change_led_state(&led_util, red, true);
	} else {
		led_util_change_led_state(&led_util, red, false);
	}
}

void admin_set_max_floor(Elevator_State* state, char data[10]) {
	int max_floor = extract_int(data);
	if (max_floor < 1 && max_floor > 9) { return; }
	set_max_floor(state, max_floor);
	queue_empty_queue(&state->floor_selection_queue);
}

void admin_set_floor(Elevator_State* state, char data[10]) {
	int floor = extract_int(data);
	if (floor < 0 && floor >= state->max_floor) { return; }
	set_current_floor(state, floor);
	queue_empty_queue(&state->floor_selection_queue);
}

void admin_set_floor_wait(Elevator_State* state, char data[10]) {
	int wait = extract_int(data);
	if(wait < 500 && wait > 5000) { return; }
	set_between_floor_duration(state, wait);
}

void admin_set_led(Elevator_State* state, char data[10]) {
	int is_led_on = extract_int(data);

	state->led_enabled = is_led_on == 1 ? true : false;
}

void admin_test(Elevator_State* state, char data[10]) {
	int floors[5];
	int input_floor_digits = extract_int(data);

	floors[0] = (input_floor_digits /  10000) % 10;
	floors[1] = (input_floor_digits /   1000) % 10;
	floors[2] = (input_floor_digits /    100) % 10;
	floors[3] = (input_floor_digits /     10) % 10;
	floors[4] = (input_floor_digits /      1) % 10;

	for(int i = 0; i < 5 ; ++i) {
		int floor_number = floors[i];
		if(floor_number == 0) { continue; }
		if(floor_number < state->max_floor && floor_number >= 0) {
			// the floor on the first index is the same at current floor we enqueue because we check this at go_to_floor function
			state->floor_should_go = floor_number;
			add_new_floor_to_queue(state, true);
		}
	}
	state->floor_should_go = -1;
}


void perform_admin_action(Elevator_State* state, Admin* admin, char data[10]) {
	extern Message_Sender message_sender;

	if (can_switch_to_admin_mode(state, admin) == true && data[0] == 'A') {
		enter_admin(admin, data);
		send_admin_status(&message_sender, admin->on_admin_mode);
	} else if (admin->on_admin_mode == true) {
		if (data[0] == 'S' && data[1] == 'E' && data[2] == 'T') { // SET
			if(data[3] == 'M' && data[4] == 'F') { // SETMF == set max floor
				admin_set_max_floor(state, data);
				send_max_floor_status(&message_sender, state);
			} else if(data[3] == 'F') { // SETF == set floor
				admin_set_floor(state, data);
				send_current_floor_status(&message_sender, state);
			} else if(data[3] == 'W') { // SETW == set wait
				admin_set_floor_wait(state, data);
				send_wating_status(&message_sender, state);
			} else if(data[3] == 'L') { // SETL == set led
				admin_set_led(state, data);
				send_led_status(&message_sender, state);
			}
		} else if (data[0] == 'T') { // Test
			send_queue_status(&message_sender, state);
			admin_test(state, data);
			send_queue_status(&message_sender, state);
		}
	}
	if(data[0] == 'S' && data[1] == 'T') { // Start
		exit_admin(admin);
		send_admin_status(&message_sender, admin->on_admin_mode);
	}
}





