/*
 * mutex_lock.h
 *
 *  Created on: Dec 8, 2022
 *      Author: kiarashvosough
 */

#ifndef INC_MUTEX_LOCK_H_
#define INC_MUTEX_LOCK_H_

#include "bool.h"

typedef struct {
	bool is_locked;
} mutex_lock;

void init_lock(mutex_lock* _lock) {
	mutex_lock new_lock = {
			false
	};
	*_lock = new_lock;
}

void aquire(mutex_lock* _lock) {
	while(_lock->is_locked == true) {}
	_lock->is_locked = true;
}

void release(mutex_lock* _lock) {
	_lock->is_locked = false;
}

#endif /* INC_MUTEX_LOCK_H_ */
