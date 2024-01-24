#if 0

#include "elevator_loopmonitor.h"

extern TIM_HandleTypeDef htim11;
extern ADC_HandleTypeDef hadc1;

extern uint8_t display_scroll_buffer[2][8]; // from dotmatrix.c
extern uint8_t display_data[8]; // from dotmatrix.c

static uint8_t curr_status;
static uint8_t curr_floor;
static uint8_t target_floor;

static void polling_button(void);
static void run_hw(void);


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
	curr_floor = 1; // 최초에 엘레베이터는 1층에 있다고 가정
	target_floor = 1;

	LCD_Command(CLEAR_DISPLAY);
	display_floor_info();
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


void elevator_processing_loop_monitor(void)
{
	while(1)
	{
		/*
		 * 버튼 폴링
		 */
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
				LCD_Command(CLEAR_DISPLAY);
				display_floor_info();
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
				LCD_Command(CLEAR_DISPLAY);
				display_floor_info();
			}
		}

		/*
		 * 스텝모터 컨트롤 + 닷 매트릭스 컨트롤
		 */
		static int curr_step = 0;

		static uint8_t count = 0; // column count
		static uint8_t index = 0; // scroll buffer의 2차원 index값
		static uint32_t past_time = 0;

		if (curr_status == STOP)
		{
			curr_step = -1;

			count = 0;
			index = 0;
			past_time = 0;
		}
		else if (curr_status == START_BOTTOM_UP)
		{
			curr_step++;
			if (curr_step >= 8) curr_step = 0;
			curr_step %= 8;

			/* 500ms에 한번씩 display data를 업데이트 */
			uint32_t now_time = HAL_GetTick(); // 정식 타이머를 안쓰고 시간 재는방법... 500ms
			if (now_time - past_time >= 500)
			{
				past_time = now_time;

				for (int i = 0; i < 8; i++)
				{
					display_data[i] = (display_scroll_buffer[index][i] >> count) | (display_scroll_buffer[index+1][i] << (8 - count));
				}

				if (++count == 9) // 8 칼럼을 다 처리 했으면 다음 스크롤 버퍼로 이동
				{
					count = 0;
					if (++index == 1) { index = 0; }
				}
			}
			/* 업데이트가 되지 않는 이상 계속 같은 display data를 폴링방식으로 출력 */
			for (int i = 0; i < 8; i++)
			{
				write_column_data(i);
				write_row_data(display_data[i]);
				delay_us(100);
			}
		}
		else if (curr_status == START_TOP_DOWN)
		{
			curr_step--;
			if (curr_step < 0) curr_step = 7;
			curr_step %= 8;

			/* 500ms에 한번씩 display data를 업데이트 */
			uint32_t now_time = HAL_GetTick(); // 정식 타이머를 안쓰고 시간 재는방법... 500ms
			if (now_time - past_time >= 500)
			{
				past_time = now_time;

				for (int i = 0; i < 8; i++)
				{
					display_data[i] = (display_scroll_buffer[index][i] >> count) | (display_scroll_buffer[index+1][i] << (8 - count));
				}

				if (++count == 9) // 8 칼럼을 다 처리 했으면 다음 스크롤 버퍼로 이동
				{
					count = 0;
					if (++index == 1) { index = 0; }
				}
			}
			/* 업데이트가 되지 않는 이상 계속 같은 display data를 폴링방식으로 출력 */
			for (int i = 0; i < 8; i++)
			{
				write_column_data(i);
				write_row_data(display_data[i]);
				delay_us(100);
			}
		}


		switch (curr_step)
		{
		case 0:
			HAL_GPIO_WritePin(StepMotor_IN1_GPIO_Port, StepMotor_IN1_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(StepMotor_IN2_GPIO_Port, StepMotor_IN2_Pin|StepMotor_IN3_Pin|StepMotor_IN4_Pin, GPIO_PIN_RESET);
			break;
		case 1:
			HAL_GPIO_WritePin(StepMotor_IN1_GPIO_Port, StepMotor_IN1_Pin|StepMotor_IN2_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(StepMotor_IN3_GPIO_Port, StepMotor_IN3_Pin|StepMotor_IN4_Pin, GPIO_PIN_RESET);
			break;
		case 2:
			HAL_GPIO_WritePin(StepMotor_IN1_GPIO_Port, StepMotor_IN1_Pin|StepMotor_IN3_Pin|StepMotor_IN4_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(StepMotor_IN2_GPIO_Port, StepMotor_IN2_Pin, GPIO_PIN_SET);
			break;
		case 3:
			HAL_GPIO_WritePin(StepMotor_IN1_GPIO_Port, StepMotor_IN1_Pin|StepMotor_IN4_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(StepMotor_IN2_GPIO_Port, StepMotor_IN2_Pin|StepMotor_IN3_Pin, GPIO_PIN_SET);
			break;
		case 4:
			HAL_GPIO_WritePin(StepMotor_IN1_GPIO_Port, StepMotor_IN1_Pin|StepMotor_IN2_Pin|StepMotor_IN4_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(StepMotor_IN3_GPIO_Port, StepMotor_IN3_Pin, GPIO_PIN_SET);
			break;
		case 5:
			HAL_GPIO_WritePin(StepMotor_IN1_GPIO_Port, StepMotor_IN1_Pin|StepMotor_IN2_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(StepMotor_IN3_GPIO_Port, StepMotor_IN3_Pin|StepMotor_IN4_Pin, GPIO_PIN_SET);
			break;
		case 6:
			HAL_GPIO_WritePin(StepMotor_IN1_GPIO_Port, StepMotor_IN1_Pin|StepMotor_IN2_Pin|StepMotor_IN3_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(StepMotor_IN4_GPIO_Port, StepMotor_IN4_Pin, GPIO_PIN_SET);
			break;
		case 7:
			HAL_GPIO_WritePin(StepMotor_IN1_GPIO_Port, StepMotor_IN1_Pin|StepMotor_IN4_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(StepMotor_IN2_GPIO_Port, StepMotor_IN2_Pin|StepMotor_IN3_Pin, GPIO_PIN_RESET);
			break;
		default:
			HAL_GPIO_WritePin(StepMotor_IN1_GPIO_Port, StepMotor_IN1_Pin|StepMotor_IN2_Pin|StepMotor_IN3_Pin|StepMotor_IN4_Pin, GPIO_PIN_RESET);
			break;
		}

		if (curr_status != STOP) delay_us(1126); // 스텝모터 사이시간 + 닷 매트릭스 잔상시간 ... 1126 + a
	}
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

//			LCD_Command(CLEAR_DISPLAY);
//			display_floor_info(&curr_floor, &target_floor);
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

//			LCD_Command(CLEAR_DISPLAY);
//			display_floor_info(&curr_floor, &target_floor);
		}
	}
}


void run_hw(void)
{
	switch (curr_status)
	{
		case STOP:
			curr_floor = target_floor;
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


void display_floor_info(void)
{
	uint8_t lcd_buff_1[20], lcd_buff_2[20];

	sprintf(lcd_buff_1, "  Current Floor: %d", curr_floor);
	Move_Cursor(0, 0);
	LCD_String(lcd_buff_1);

	sprintf(lcd_buff_2, " Target Floor: %d", target_floor);
	Move_Cursor(1, 0);
	LCD_String(lcd_buff_2);
}


#endif /* if 0 */
