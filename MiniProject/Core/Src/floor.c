/*
 * floor.c
 *
 *  Created on: Dec 8, 2022
 *      Author: kiarashvosough
 */


#include "floor.h"

void init_floor(Floor* floor, int floor_index, bool is_target_floor) {
	Floor new_floor = {
			floor_index,
			is_target_floor
	};
	*floor = new_floor;
}

