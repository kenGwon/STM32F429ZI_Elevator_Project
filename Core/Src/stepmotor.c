#include "stepmotor.h"

/*
 * RPM(Revolution Per Minutes): 분당 회전수
 * 1분: 60sec: 1,000,000us(1초) x 60 = 60,000,000us
 *
 * 1,000,000us(초)
 * ==> 1초(1000ms) ==> 1ms(1000us) x 1000ms ==> 1,000,000us
 *
 * 4096 step = 1바퀴
 * 스텝모터에 자력을 줘서 8번 자력의 형상이 바뀌는 것을 sequence 라고 한다.
 * 1 sequence = 8 step : 0.70312도
 * 4096 / 8 ==> 512 sequence : 360도(= 0.70312 x 512)
 */


/*
 * desc: direction에 들어올 수 정수값은 elevator.h에 선언된 enum Curr_Status을 참조합니다.
 *       - 0: STOP
 *       		스텝모터가 정지한 상태입니다. (엘레베이터가 멈춰있는 상태입니다.)
 *       - 1: START_BOTTOM_UP
 *       		스텝모터가 오른쪽으로 회전하는 상태입니다. (엘레베이터가 위로 올라가는 상태입니다.)
 *       - 2: START_TOP_DOWN
 *       		스텝모터가 왼쪽으로 회전하는 상태입니다. (엘레베이터가 아래로 내려가는 상태입니다.)
 */
void control_stepmotor(uint8_t curr_status)
{
	static int curr_step = 0;

	if (curr_status == STOP)
	{
		curr_step = -1;
	}
	else if (curr_status == START_BOTTOM_UP)
	{
		curr_step++;
		if (curr_step >= 8) curr_step = 0;
		curr_step %= 8;
	}
	else if (curr_status == START_TOP_DOWN)
	{
		curr_step--;
		if (curr_step < 0) curr_step = 7;
		curr_step %= 8;
	}

	drive_stepmotor(curr_step);
//	delay_us(100);
	if (curr_status == START_BOTTOM_UP) set_RPM(13);
	else if (curr_status == START_TOP_DOWN) set_RPM(13);
}


void drive_stepmotor(int step)
{
	switch (step)
	{
		case 0:
			HAL_GPIO_WritePin(StepMotor_IN1_GPIO_Port, StepMotor_IN1_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(StepMotor_IN2_GPIO_Port, StepMotor_IN2_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(StepMotor_IN3_GPIO_Port, StepMotor_IN3_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(StepMotor_IN4_GPIO_Port, StepMotor_IN4_Pin, GPIO_PIN_RESET);
			break;
		case 1:
			HAL_GPIO_WritePin(StepMotor_IN1_GPIO_Port, StepMotor_IN1_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(StepMotor_IN2_GPIO_Port, StepMotor_IN2_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(StepMotor_IN3_GPIO_Port, StepMotor_IN3_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(StepMotor_IN4_GPIO_Port, StepMotor_IN4_Pin, GPIO_PIN_RESET);
			break;
		case 2:
			HAL_GPIO_WritePin(StepMotor_IN1_GPIO_Port, StepMotor_IN1_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(StepMotor_IN2_GPIO_Port, StepMotor_IN2_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(StepMotor_IN3_GPIO_Port, StepMotor_IN3_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(StepMotor_IN4_GPIO_Port, StepMotor_IN4_Pin, GPIO_PIN_RESET);
			break;
		case 3:
			HAL_GPIO_WritePin(StepMotor_IN1_GPIO_Port, StepMotor_IN1_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(StepMotor_IN2_GPIO_Port, StepMotor_IN2_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(StepMotor_IN3_GPIO_Port, StepMotor_IN3_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(StepMotor_IN4_GPIO_Port, StepMotor_IN4_Pin, GPIO_PIN_RESET);
			break;
		case 4:
			HAL_GPIO_WritePin(StepMotor_IN1_GPIO_Port, StepMotor_IN1_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(StepMotor_IN2_GPIO_Port, StepMotor_IN2_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(StepMotor_IN3_GPIO_Port, StepMotor_IN3_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(StepMotor_IN4_GPIO_Port, StepMotor_IN4_Pin, GPIO_PIN_RESET);
			break;
		case 5:
			HAL_GPIO_WritePin(StepMotor_IN1_GPIO_Port, StepMotor_IN1_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(StepMotor_IN2_GPIO_Port, StepMotor_IN2_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(StepMotor_IN3_GPIO_Port, StepMotor_IN3_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(StepMotor_IN4_GPIO_Port, StepMotor_IN4_Pin, GPIO_PIN_SET);
			break;
		case 6:
			HAL_GPIO_WritePin(StepMotor_IN1_GPIO_Port, StepMotor_IN1_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(StepMotor_IN2_GPIO_Port, StepMotor_IN2_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(StepMotor_IN3_GPIO_Port, StepMotor_IN3_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(StepMotor_IN4_GPIO_Port, StepMotor_IN4_Pin, GPIO_PIN_SET);
			break;
		case 7:
			HAL_GPIO_WritePin(StepMotor_IN1_GPIO_Port, StepMotor_IN1_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(StepMotor_IN2_GPIO_Port, StepMotor_IN2_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(StepMotor_IN3_GPIO_Port, StepMotor_IN3_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(StepMotor_IN4_GPIO_Port, StepMotor_IN4_Pin, GPIO_PIN_SET);
			break;
		default:
			HAL_GPIO_WritePin(StepMotor_IN1_GPIO_Port, StepMotor_IN1_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(StepMotor_IN2_GPIO_Port, StepMotor_IN2_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(StepMotor_IN3_GPIO_Port, StepMotor_IN3_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(StepMotor_IN4_GPIO_Port, StepMotor_IN4_Pin, GPIO_PIN_RESET);
			break;
	}
}

/*
 * -------- set_RPM(13)으로 지정 시 동작상황 --------
 * 60,000,000us(1분) / 4096step / RPM
 * 1126us(1step IDLE time) x 4096 = 4,612,096us : : 한바퀴 도는데 걸리는 시간
 *                                = 4612ms
 *                                = 4.6초
 * 60초 / 4.6 = 13회전 : 1분동안 돌 수 있는 회전 수
 */
void set_RPM(int rpm) // 가능한 RPM 범위: 1~13
{
	delay_us(60000000/4096/rpm);
	// 최대 speed 기준(분당 13회전): delay_us(1126);
}











#if 0


void do_demo(void)
{
	int current_direction = 0;

	while (1)
	{
		if (Get_Button(BTN0_GPIO_Port, BTN0_Pin, 0) == BUTTON_PRESS)
		{
			if (current_direction == 1) current_direction = 2;
			else if (current_direction == 2) current_direction = 1;
			else current_direction = 1;
		}
		else if (Get_Button(BTN1_GPIO_Port, BTN1_Pin, 1) == BUTTON_PRESS)
		{
			current_direction = 0;
		}

		control_stepmotor(current_direction);
	}
}







// 시계방향으로 1회전 <---무한반복---> 반시계 방향으로 1회전
void stepmotor_main_test(void)
{
	while(1)
	{
		// 정회전
		for (int sequence = 0; sequence < 512; sequence++)
		{
			for (int step = 0; step < 8; step++)
			{
				stepmotor_drive(step);
				set_RPM(9);
			}
		}

		// 역회전
		for (int sequence = 0; sequence < 512; sequence++)
		{
			for (int step = 7; step >= 0; step--)
			{
				stepmotor_drive(step);
				set_RPM(9);
			}
		}
	}
}

#endif
