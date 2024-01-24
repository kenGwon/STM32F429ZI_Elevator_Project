#ifndef _DOTMATRIX_H_
#define _DOTMATRIX_H_

#include "main.h"
#include "_header.h"
#include "timer_management.h"

void Dot_Matrix_Init(void);
void set_dotmatrix_buffer(uint8_t curr_status, uint8_t target_floor);
void control_dotmatrix(uint8_t curr_status);

void write_column_data(int col);
void write_row_data(unsigned char data);
void clear_dotmatrix_buffer(void);

#endif /* _DOTMATRIX_H_ */
