#ifndef _GPIO__CALLBACK__MANAGEMENT_H_
#define _GPIO__CALLBACK__MANAGEMENT_H_

#include "main.h"
#include "elevator_os.h"

extern uint16_t adcValue[4]; // 헤더파일로 이동

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin);
void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc);


#endif /*_GPIO__CALLBACK__MANAGEMENT_H_*/
