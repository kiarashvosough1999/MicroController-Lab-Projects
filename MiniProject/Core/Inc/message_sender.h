/*
 * message_sender.h
 *
 *  Created on: Dec 16, 2022
 *      Author: kiarashvosough
 */

#ifndef INC_MESSAGE_SENDER_H_
#define INC_MESSAGE_SENDER_H_

#include "elevator_state.h"
#include "bool.h"

typedef struct {
	char message[50];
	int last_time_sent;
} Message_Sender;

void init_message_sender(Message_Sender* sender);

void send_admin_status(Message_Sender* sender, bool on_admin);
void send_led_status(Message_Sender* sender, Elevator_State* state);
void send_max_floor_status(Message_Sender* sender, Elevator_State* state);
void send_current_floor_status(Message_Sender* sender, Elevator_State* state);
void send_wating_status(Message_Sender* sender, Elevator_State* state);
void send_queue_status(Message_Sender* sender, Elevator_State* state);

#endif /* INC_MESSAGE_SENDER_H_ */
