#include "elevator_os.h"

extern TIM_HandleTypeDef htim11;
extern ADC_HandleTypeDef hadc1;

extern uint8_t display_scroll_buffer[2][8]; // from dotmatrix.c
extern uint8_t display_data[8]; // from dotmatrix.c

static uint8_t curr_status;
static uint8_t curr_floor;
static uint8_t target_floor;


/*
 *
 */
void elevator_init(void)
{
	HAL_TIM_Base_Start_IT(&htim11);  // delay_us() timer 활성화
	HAL_ADC_Start_IT(&hadc1); // 조도센서 external interrupt 활성화

	I2C_LCD_Init();
	Dot_Matrix_Init();

	curr_status = STOP;
	curr_floor = FLOOR_1; // 최초에 엘레베이터는 1층에 있다고 가정
	target_floor = FLOOR_1;

	display_floor_info();
	display_fnd(curr_floor);
}

/*
 *
 */
void elevator_terminate(void)
{
	HAL_TIM_Base_Stop_IT(&htim11);
	HAL_ADC_Stop_IT(&hadc1);
}

/*
 * Description: 가장 바깥의 main.c의 while(1)문에서 무한 호출되는 함수입니다.
 */
void elevator_processing(void)
{
	polling_button();
	run_hw();
}

void polling_button(void)
{
	if (Get_Button(BTN0_GPIO_Port, BTN0_Pin, 0) == BUTTON_PRESS) // 취소버튼
	{
		set_curr_status(STOP);
	}
	else if (Get_Button(BTN1_GPIO_Port, BTN1_Pin, 1) == BUTTON_PRESS) // 하강버튼
	{
		target_floor = curr_floor - 1;

		if (target_floor < 1)
		{
			target_floor = 1;
			set_curr_status(STOP);
		}
		else
		{
			set_curr_status(START_TOP_DOWN);
			set_dotmatrix_buffer(&curr_status, &target_floor);
		}
	}
	else if (Get_Button(BTN2_GPIO_Port, BTN2_Pin, 2) == BUTTON_PRESS) // 상승버튼
	{
		target_floor = curr_floor + 1;

		if (target_floor > 4)
		{
			target_floor = 4;
			set_curr_status(STOP);
		}
		else
		{
			set_curr_status(START_BOTTOM_UP);
			set_dotmatrix_buffer(&curr_status, &target_floor);
		}
	}
}


void run_hw(void)
{
	switch (curr_status)
	{
		case STOP:
			control_stepmotor(&curr_status);
			control_dotmatrix(&curr_status);

//			LCD_Command(CLEAR_DISPLAY);
//			display_floor_info(&curr_floor, &target_floor);

			display_fnd(8);
			break;

		case START_BOTTOM_UP:
			control_stepmotor(&curr_status);
			control_dotmatrix(&curr_status);
			break;

		case START_TOP_DOWN:
			control_stepmotor(&curr_status);
			control_dotmatrix(&curr_status);
			break;

		default:
			break;
	}
}


void set_curr_status(uint8_t status)
{
	curr_status = status;
}

void set_curr_floor(uint8_t floor)
{
	curr_floor = floor;
}

void set_target_floor(uint8_t floor)
{
	target_floor = floor;
}

uint8_t get_curr_status(void)
{
	return curr_status;
}

uint8_t get_curr_floor(void)
{
	return curr_floor;
}


uint8_t get_target_floor(void)
{
	return target_floor;
}



void display_floor_info(void)
{
	uint8_t lcd_buff_1[20], lcd_buff_2[20];

	LCD_Command(CLEAR_DISPLAY);

	sprintf(lcd_buff_1, "  Current Floor: %d", curr_floor);
	Move_Cursor(0, 0);
	LCD_String(lcd_buff_1);

	sprintf(lcd_buff_2, " Target Floor: %d", target_floor);
	Move_Cursor(1, 0);
	LCD_String(lcd_buff_2);
}

void display_alert_info(void)
{
	uint8_t lcd_buff_1[20], lcd_buff_2[20];

	LCD_Command(CLEAR_DISPLAY);

	sprintf(lcd_buff_1, "  Wrong input !!!", curr_floor);
	Move_Cursor(0, 0);
	LCD_String(lcd_buff_1);

	sprintf(lcd_buff_2, "back to IDLE..", target_floor);
	Move_Cursor(1, 0);
	LCD_String(lcd_buff_2);
}


