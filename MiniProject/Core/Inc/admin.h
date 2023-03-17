/*
 * admin.h
 *
 *  Created on: Dec 5, 2022
 *      Author: kiarashvosough
 */

#ifndef SRC_ADMIN_H_
#define SRC_ADMIN_H_

#include "elevator_state.h"
//“ADMIN#{Pass}

typedef struct {
	int password;
	bool on_admin_mode;
} Admin;

void init_admin(Admin* admin);

bool can_switch_to_admin_mode(Elevator_State* state, Admin* admin);

void admin_set_max_floor(Elevator_State* state, char data[10]);

void admin_set_floor(Elevator_State* state, char data[10]);

void admin_set_floor_wait(Elevator_State* state, char data[10]);

void admin_set_led(Elevator_State* state, char data[10]);

bool is_on_admin_mode(Admin* admin);

void perform_admin_action(Elevator_State* state, Admin* admin, char data[10]);

#endif /* SRC_ADMIN_H_ */
