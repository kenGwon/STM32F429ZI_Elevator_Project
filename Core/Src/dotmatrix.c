#include "dotmatrix.h"

static GPIO_TypeDef *col_port[] =
{
	COL1_GPIO_Port, COL2_GPIO_Port, COL3_GPIO_Port, COL4_GPIO_Port,
	COL5_GPIO_Port, COL6_GPIO_Port, COL7_GPIO_Port, COL8_GPIO_Port
};

static GPIO_TypeDef *row_port[] =
{
	ROW1_GPIO_Port, ROW2_GPIO_Port, ROW3_GPIO_Port, ROW4_GPIO_Port,
	ROW5_GPIO_Port, ROW6_GPIO_Port, ROW7_GPIO_Port, ROW8_GPIO_Port
};

static uint16_t col_pin[] =
{
	COL1_Pin, COL2_Pin, COL3_Pin, COL4_Pin,
	COL5_Pin, COL6_Pin, COL7_Pin, COL8_Pin
};

static uint16_t row_pin[] =
{
	ROW1_Pin, ROW2_Pin, ROW3_Pin, ROW4_Pin,
	ROW5_Pin, ROW6_Pin, ROW7_Pin, ROW8_Pin
};

static const uint8_t floor_num[10][8] =
{
	{
		0b00000000, // 0
		0b00000000,
		0b01111110,
		0b10000001,
		0b10000001,
		0b01111110,
		0b00000000,
		0b00000000
	},
	{
		0b00000000, // 1
		0b00000000,
		0b00000001,
		0b11111111,
		0b01000001,
		0b00100001,
		0b00000000,
		0b00000000
	},
	{
		0b00000000, // 2
		0b00000001,
		0b01110001,
		0b10001001,
		0b10000101,
		0b01000011,
		0b00100001,
		0b00000000
	},
	{
		0b00000000, // 3
		0b00000000,
		0b01100110,
		0b10011001,
		0b10010001,
		0b10010001,
		0b00000000,
		0b00000000
	},
	{
		0b00000000, // 4
		0b00000100,
		0b11111111,
		0b01000100,
		0b00100100,
		0b00010100,
		0b00001100,
		0b00000000
	}
};

static const uint8_t up_arrow[] =
{
	0b00000000,
	0b00010000,
	0b00110000,
	0b01111110,
	0b01111110,
	0b00110000,
	0b00010000,
	0b00000000
};

static const uint8_t down_arrow[] =
{
	0b00000000,
	0b00001000,
	0b00001100,
	0b01111110,
	0b01111110,
	0b00001100,
	0b00001000,
	0b00000000
};

static const uint8_t all_on[] = // all on 문자 정의
{
	0b11111111,
	0b11111111,
	0b11111111,
	0b11111111,
	0b11111111,
	0b11111111,
	0b11111111,
	0b11111111
};

static const uint8_t all_off[] =
{
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000
};

uint8_t display_scroll_buffer[2][8] = {0};
uint8_t display_data[8] = {0};


/*
 * Description: Dot Matrix의 불을 모두 끕니다.
 */
void Dot_Matrix_Init(void)
{
	for (int i = 0; i < 8; i++)
	{
		write_column_data(i); // i번째 col에 우선 전부 low를 줘놓고
		write_row_data(all_off[i]); // 그 안에서 row값을 각각이 틀어주면서 제어하는 느낌
	}
}


void clear_dotmatrix_buffer(void)
{
	for	(int buffer_idx = 0; buffer_idx < 2; buffer_idx++) // 1부터 시작
	{
		for (int matrix_idx = 0; matrix_idx < 8; matrix_idx++) // scroll_buffer[0] = blank
		{
			display_scroll_buffer[buffer_idx][matrix_idx] = all_off[matrix_idx];
		}
	}
}

void set_dotmatrix_buffer(uint8_t curr_status, uint8_t target_floor)
{
	clear_dotmatrix_buffer();

	if (curr_status == STOP)
	{
	}
	else if (curr_status == START_TOP_DOWN)
	{
		for	(int buffer_idx = 0; buffer_idx < 2; buffer_idx++)
		{
			for (int matrix_idx = 0; matrix_idx < 8; matrix_idx++) // scroll_buffer[0] = blank
			{
				if (buffer_idx == 0) { display_scroll_buffer[buffer_idx][matrix_idx] = up_arrow[matrix_idx]; }
				else if (buffer_idx == 1) { display_scroll_buffer[buffer_idx][matrix_idx] = floor_num[target_floor][matrix_idx]; }
			}
		}
	}
	else if (curr_status == START_BOTTOM_UP)
	{
		for	(int buffer_idx = 0; buffer_idx < 2; buffer_idx++)
		{
			for (int matrix_idx = 0; matrix_idx < 8; matrix_idx++) // scroll_buffer[0] = blank
			{
				if (buffer_idx == 1) { display_scroll_buffer[buffer_idx][matrix_idx] = floor_num[target_floor][matrix_idx]; }
				else if (buffer_idx == 0) { display_scroll_buffer[buffer_idx][matrix_idx] = down_arrow[matrix_idx]; }
			}
		}
	}
}


void control_dotmatrix(uint8_t curr_status)
{
	static uint8_t count = 0; // column count
	static uint8_t index = 0; // scroll buffer의 2차원 index값
	static uint32_t past_time = 0;

	if (curr_status == STOP)
	{
		count = 0;
		index = 0;
		past_time = 0;
		clear_dotmatrix_buffer();
	}
	else if (curr_status == START_BOTTOM_UP)
	{
		// 정방향 for문


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
				index++;
				if (index == 1)
				{
					index = 0;
				}
			}
		}

		/* 업데이트가 되지 않는 이상 계속 같은 display data를 폴링방식으로 출력 */
		for (int i = 0; i < 8; i++)
		{
			write_column_data(i);
			write_row_data(display_data[i]);
			delay_us(1000);
		}

	}
	else if (curr_status == START_TOP_DOWN)
	{
		// 역방향 for믄


		/* 500ms에 한번씩 display data를 업데이트 */
		uint32_t now_time = HAL_GetTick(); // 정식 타이머를 안쓰고 시간 재는방법... 500ms
		if (now_time - past_time >= 500)
		{
			past_time = now_time;

			for (int i = 0; i < 8; i++)
			{
				display_data[i] = (display_scroll_buffer[index][i] << count) | (display_scroll_buffer[index+1][i] >> (8 - count));
			}

			if (++count == 9) // 8 칼럼을 다 처리 했으면 다음 스크롤 버퍼로 이동
			{
				count = 0;
				index++;
				if (index == 1)
				{
					index = 0;
				}
			}
		}

		/* 업데이트가 되지 않는 이상 계속 같은 display data를 폴링방식으로 출력 */
		for (int i = 0; i < 8; i++)
		{
			write_column_data(i);
			write_row_data(display_data[i]);
			delay_us(1000);
		}
	}
}

// common-anode 방식 기준의 코드
void write_column_data(int col)
{
	for (int i = 0; i < 8; i++)
	{
		if (i == col) {HAL_GPIO_WritePin(col_port[i], col_pin[i], GPIO_PIN_RESET);} // on 상황!! common-anode이기 때문에 0일 때 켜짐
		else {HAL_GPIO_WritePin(col_port[i], col_pin[i], GPIO_PIN_SET);} // off 상황!! common-anode이기 때문에 1일 때 꺼짐
	}
}

// data = ob00111100 켜보자. 핵심은 and(&) 비트연산을 사용하는 것이다.
void write_row_data(unsigned char data) // 8bit 한줄 들어오는거다.
{
	unsigned char temp_data;
	temp_data = data;

	for (int i = 0; i < 8; i++)
	{
		if (temp_data & (0b00000001 << i)) {HAL_GPIO_WritePin(row_port[i], row_pin[i], GPIO_PIN_SET);}
		else {HAL_GPIO_WritePin(row_port[i], row_pin[i], GPIO_PIN_RESET);}
	}
}




#if 0


int dotmatrix_main_test(void) // common anode 방식이기 때문에 row에는 high를 주고 col에는 low를 줘야 잔상효과로 불이 들어오는것처럼 보임
{
	while (1)
	{
		for (int i = 0; i < 8; i++)
		{
			write_column_data(i); // i번째 col에 우선 전부 low를 줘놓고
			write_row_data(all_on[i]); // 그 안에서 row값을 각각이 틀어주면서 제어하는 느낌
			HAL_Delay(1); // LED가 꺼져서 잔상이 남을 시간
		}
	}
	return 0;
}







uint8_t display_data[8]; // 최종 8*8 출력할 데이터
uint8_t scroll_buffer[50][8] = {0}; // 스크롤할 데이터가 들어가 있을 버퍼
int64_t number_of_character = 11; // 출력할 문자 갯수: 0~9 + 하트

// dot-matrix 초기화 작업
// 1. display_data에 number_data[0]에 있는 내용을 복사
// 2. number_data를 scroll_buffer에다가 복사
// 3. dot_matrix의 LED를 전부 끈다.
void init_dotmatrix(void)
{
	// 1. display_data에 number_data[0]에 있는 내용을 복사
	for	(int i = 0; i < 8; i++)
	{
		display_data[i] = number_data[0][i];
	}

	// 2. number_data를 scroll_buffer에다가 복사
	for	(int i = 1; i < number_of_character + 1; i++) // 1부터 시작
	{
		for (int j = 0; j < 8; j++) // scroll_buffer[0] = blank
		{
			scroll_buffer[i][j] = number_data[i-1][j];
		}
	}

	// 3. dot_matrix의 LED를 전부 끈다.
	for (int i = 0; i < 8; i++)
	{
		HAL_GPIO_WritePin(col_port[i], col_pin[i], GPIO_PIN_SET); // common-anode이기 때문에 열에 high가 들어가면 LED가 꺼지는거다.
	}
}



int scroll_num_test(void)
{
	static int count = 0; // column count
	static int index = 0; // scroll buffer의 2차원 index값
	static uint32_t past_time = 0;

	init_dotmatrix();
	while (1)
	{
		/* 500ms에 한번씩 display data를 업데이트 */
		uint32_t now_time = HAL_GetTick(); // 정식 타이머를 안쓰고 시간 재는방법... 500ms
		if (now_time - past_time >= 500)
		{
			past_time = now_time;

			for (int i = 0; i < 8; i++)
			{
				display_data[i] = (scroll_buffer[index][i] >> count) | (scroll_buffer[index+1][i] << (8 - count));
			}

			if (++count == 8) // 8 칼럼을 다 처리 했으면 다음 스크롤 버퍼로 이동
			{
				count = 0;
				index++;
				if (index == number_of_character)
				{
					index = 0;
				}
			}
		}

		/* 업데이트가 되지 않는 이상 계속 같은 display data를 폴링방식으로 출력 */
		for (int i = 0; i < 8; i++)
		{
			write_column_data(i);
			write_row_data(display_data[i]);
			HAL_Delay(1);
		}
	}

	return 0;
}






void upper_elevator(int src_floor, int dest_floor)
{
	int count = 0; // column count
//	int index = 0; // target_arr의 2차원 index값
	uint32_t past_time = 0;

	int offset = dest_floor - src_floor;
	uint8_t target_arr[offset * 2 + 1][8];

	for (int i = 0; i < offset * 2 + 1; i++)
	{
		if (i % 2 == 1)
		{
			for (int j = 0; j < 8; j++)
			{
				target_arr[i][j] = scroll_buffer[i / 2 + 1][j];
			}
		}
		else
		{
			for (int j = 0; j < 8; j++)
			{
				target_arr[i][j] = upper_arrow[j];
			}
		}
	}

	init_dotmatrix();

	int length = offset * 2 + 1;

	do
	{
		/* 500ms에 한번씩 display data를 업데이트 */
		uint32_t now_time = HAL_GetTick(); // 정식 타이머를 안쓰고 시간 재는방법... 500ms
		if (now_time - past_time >= 500)
		{
			past_time = now_time;

			for (int i = 0; i < 8; i++)
			{
				display_data[i] = target_arr[length][i];
			}

			if (++offset == 8)
			{
				offset = 0;
			}

			if (++count == 8) // 8 칼럼을 다 처리 했으면 다음 스크롤 버퍼로 이동
			{
				count = 0;
				length--;
			}
		}
		/* 업데이트가 되지 않는 이상 계속 같은 display data를 폴링방식으로 출력 */
		for (int i = 0; i < 8; i++)
		{
			write_column_data(i);
			write_row_data(display_data[i]);
			HAL_Delay(1);
		}
	} while (length >= 0);

}




#endif
