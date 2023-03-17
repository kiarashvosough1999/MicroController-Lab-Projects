/*
 * utils.h
 *
 *  Created on: Dec 7, 2022
 *      Author: kiarashvosough
 */

#ifndef INC_UTILS_H_
#define INC_UTILS_H_

#include "stm32f3xx_hal.h"
#include <string.h>
#include <stdlib.h>
#include <ctype.h>


#define Array_Size(x)  (sizeof(x) / sizeof((x)[0]))

int extract_int(char data[10]) {
    char *p = data;
    while (*p) { // While there are more characters to process...
        if (isdigit(*p)) {
            // Found a number
            long val = strtol(p, &p, 10); // Read number
            extern Elevator_State state;
            return (int)val;
        } else { // Otherwise, move on to the next character.
            p++;
        }
    }
    return -1;
}

#endif /* INC_UTILS_H_ */
