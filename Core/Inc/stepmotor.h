#ifndef _STEPMOTOR_H_
#define _STEPMOTOR_H_

#include "main.h" // 버튼 조작에 필요한 HAL_Driver나 GPIO 정보가 모두 main.h에 있음
#include "_header.h"
#include "timer_management.h"

void control_stepmotor(uint8_t curr_status);
void drive_stepmotor(int step);
void set_RPM(int rpm);

#endif /*_STEPMOTOR_H_*/
