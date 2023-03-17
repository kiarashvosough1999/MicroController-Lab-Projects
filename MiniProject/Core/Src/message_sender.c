/*
 * message_sender.c
 *
 *  Created on: Dec 16, 2022
 *      Author: kiarashvosough
 */

#include "message_sender.h"
#include <string.h>
#include <stdlib.h>

void init_message_sender(Message_Sender* sender) {
	Message_Sender new_sender = {
			"",
			0
	};
	*sender = new_sender;
}

void send_admin_status(Message_Sender* sender, bool on_admin) {
	strcat(sender->message, on_admin == true ? "Entered Admin\n" : "Exited Admin\n");
}

void send_led_status(Message_Sender* sender, Elevator_State* state) {
	strcat(sender->message, state->led_enabled == true ? "LEDs is On\n" : "LEDs is Off\n");
}

void send_max_floor_status(Message_Sender* sender, Elevator_State* state) {
	strcat(sender->message, "max floor is: ");
	char snum[1];

	itoa(state->max_floor, snum, 10);
	strcat(sender->message, snum);
	strcat(sender->message, "\n");
}

void send_current_floor_status(Message_Sender* sender, Elevator_State* state) {
	strcat(sender->message, "current floor is: ");
	char snum[1];

	itoa(state->current_floor, snum, 10);
	strcat(sender->message, snum);
	strcat(sender->message, "\n");
}

void send_wating_status(Message_Sender* sender, Elevator_State* state) {
	strcat(sender->message, "waiting time is: ");
	char snum[1];

	itoa(state->between_floor_duration, snum, 10);
	strcat(sender->message, snum);
	strcat(sender->message, "\n");
}

void send_queue_status(Message_Sender* sender, Elevator_State* state) {
	if(queue_is_queue_empty(&state->floor_selection_queue) == true) {
		strcat(sender->message, "queue is empty\n");
	} else {
		int rear = state->floor_selection_queue.rear;
		int front = state->floor_selection_queue.front;
		char snum[rear - front];
		for (int i = front; i <= rear; i++) {
			char number[1];
			itoa(state->floor_selection_queue.items[i].floor_index, number, 10);
			strcat(snum, number);
		}
		strcat(sender->message, snum);
		strcat(sender->message, "\n");
	}
}


