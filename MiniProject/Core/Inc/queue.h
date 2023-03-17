/*
 * Queue.h
 *
 *  Created on: Dec 5, 2022
 *      Author: kiarashvosough
 */

#ifndef INC_QUEUE_H_
#define INC_QUEUE_H_

#include "bool.h"
#include "floor.h"

typedef struct {
	int front;
	int rear;
	Floor items[100];
} Queue;

void queue_init(Queue* queue);

void queue_enQueue(Queue* queue, Floor item);

Floor queue_deQueue(Queue* queue);

bool queue_is_queue_full(Queue* queue);

bool queue_is_queue_empty(Queue* queue);

void queue_empty_queue(Queue* queue);

bool queue_has_item_with_floor_index(Queue* queue, int index);

void queue_change_item_with_floor_index_to_target(Queue* queue, int index);

int queue_rear_value(Queue* queue);

#endif /* INC_QUEUE_H_ */
