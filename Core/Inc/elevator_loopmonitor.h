#if 0

#ifndef _ELEVATOR__LOOPMONITOR_H_
#define _ELEVATOR__LOOPMONITOR_H_

#include "main.h"
#include "_header.h"
#include "button.h"
#include "dotmatrix.h"
#include "stepmotor.h"
#include "fnd.h"
#include "I2C_lcd.h"


void elevator_init(void);
void elevator_terminate(void);
void elevator_processing(void);
void elevator_processing_loop_monitor(void);

void set_curr_status(uint8_t status);
void set_curr_floor(uint8_t floor);
void display_floor_info(void);


#endif /*_ELEVATOR__LOOPMONITOR_H_*/

#endif /* if 0 */
