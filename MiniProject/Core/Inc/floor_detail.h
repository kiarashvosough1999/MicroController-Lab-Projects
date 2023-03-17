/*
 * floor_detail.h
 *
 *  Created on: Dec 7, 2022
 *      Author: kiarashvosough
 */

#ifndef INC_FLOOR_DETAIL_H_
#define INC_FLOOR_DETAIL_H_

typedef struct {
	int floor_index;
	int waiting_time;
} Floor_Detail;

void init_floor_detail(Floor_Detail* floor_detail);

#endif /* INC_FLOOR_DETAIL_H_ */
