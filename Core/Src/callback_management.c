#include "callback_management.h"

/*
 * 포토 센서 익스터널 인터럽트 콜백
 * copy from "/root/Drivers/STM32F4xx_HAL_Driver/Src/stm324f4xx_hal_gpio.c"
*/

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	switch (GPIO_Pin)
	{
		// 1층인 경우
		case PhotoSensor_EXIT12_Pin:
			set_curr_floor(FLOOR_1);
			display_floor_info();
			display_fnd(FLOOR_1);
			break;
		// 2층인 경우
		case PhotoSensor_EXIT13_Pin:
			set_curr_floor(FLOOR_2);
			display_floor_info();
			display_fnd(FLOOR_2);
			break;
		// 3층인 경우
		case PhotoSensor_EXIT14_Pin:
			set_curr_floor(FLOOR_3);
			display_floor_info();
			display_fnd(FLOOR_3);
			break;
		// 4층인 경우
		case PhotoSensor_EXIT15_Pin:
			set_curr_floor(FLOOR_4);
			display_floor_info();
			display_fnd(FLOOR_4);
			break;
		default:
			break;
	}

	if (get_curr_floor() == get_target_floor())
	{
		set_curr_status(STOP);
		clear_dotmatrix_buffer();
	}
	else
	{
		clear_dotmatrix_buffer();

		if (get_curr_status() == START_BOTTOM_UP) { set_dotmatrix_buffer(get_curr_status(), get_curr_floor() - 1); }
		if (get_curr_status() == START_TOP_DOWN) { set_dotmatrix_buffer(get_curr_status(), get_curr_floor() + 1); }
	}
}

/*
 * 조도 센서 인터럽트 콜백
 * copy from "/root/Drivers/STM32F4xx_HAL_Driver/Src/stm324f4xx_hal_adc.c"
 */
extern ADC_HandleTypeDef hadc1; // from main.c
extern uint16_t adcValue[4]; // from main.c

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc)
{
	if (hadc->Instance == ADC1)
	{
		adcValue[0] = HAL_ADC_GetValue(&hadc1);
		HAL_ADC_Stop_IT(&hadc1);
	}
}






