#ifndef _ELEVATOR__OS_H_
#define _ELEVATOR__OS_H_

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

uint8_t get_curr_status(void);
uint8_t get_curr_floor(void);
uint8_t get_target_floor(void);
void set_curr_status(uint8_t status);
void set_curr_floor(uint8_t floor);
void set_target_floor(uint8_t floor);

void display_floor_info(void);
void display_alert_info(void);

void polling_button(void);
void run_hw(void);

#endif /*_ELEVATOR__OS_H_*/
