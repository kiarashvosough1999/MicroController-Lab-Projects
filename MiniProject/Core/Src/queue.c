/*
 * stack.c
 *
 *  Created on: Dec 5, 2022
 *      Author: kiarashvosough
 */


#include <queue.h>
#include "stdlib.h"
#include "stm32f3xx_hal.h"

void queue_init(Queue* queue) {
	Queue new_queue = {
		-1,
		-1,
		{}
	};
	*queue = new_queue;
}

bool queue_is_queue_full(Queue* queue) {
	return queue->rear == 100 - 1 ? true : false;
}

bool queue_is_queue_empty(Queue* queue) {
	return queue->front == -1 ? true : false;
}

void queue_enQueue(Queue* queue, Floor value) {
  if (queue->rear == 100 - 1) {
	  // full
  }
  else {
    if (queue->front == -1) {
    	queue->front = 0;
    }
    queue->rear++;
    queue->items[queue->rear] = value;

  }
}

Floor queue_deQueue(Queue* queue) {

  if (queue->front == -1) {
	  // empty
	  Floor dummy = {-1, false};
	  return dummy;
  }
  else {
	Floor temp_val = queue->items[queue->front];
	queue->front++;
    if (queue->front > queue->rear)
    	queue->front = queue->rear = -1;

    return temp_val;
  }
}

void queue_empty_queue(Queue* queue) {
	queue->front = -1;
	queue->rear = -1;
}

void queue_change_item_with_floor_index_to_target(Queue* queue, int index) {
	for (int i = queue->front; i <= queue->rear; i++) {
		if(queue->items[i].floor_index == index) {
			queue->items[i].is_target_floor = true;
		}
	}
}

bool queue_has_item_with_floor_index(Queue* queue, int index) {
	for (int i = queue->front; i <= queue->rear; i++) {
		if(queue->items[i].floor_index == index) {
			return true;
		}
	}
	return false;
}

int queue_rear_value(Queue* queue) {
	if (queue->front == -1) {
		// empty
		return -1;
	} else {
		return queue->items[queue->rear].floor_index;
	}
}
