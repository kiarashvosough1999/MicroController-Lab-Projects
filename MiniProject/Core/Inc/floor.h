/*
 * floor.h
 *
 *  Created on: Dec 8, 2022
 *      Author: kiarashvosough
 */

#ifndef INC_FLOOR_H_
#define INC_FLOOR_H_

#include "bool.h"

typedef struct {
	int floor_index;
	bool is_target_floor;
} Floor;

void init_floor(Floor* floor, int floor_index, bool is_target_floor);

#endif /* INC_FLOOR_H_ */
