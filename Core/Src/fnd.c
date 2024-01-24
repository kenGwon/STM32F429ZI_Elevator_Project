#include "fnd.h"

static const uint32_t FND_font[10] =
{
	FND_A_Pin|FND_B_Pin|FND_C_Pin|FND_D_Pin|FND_E_Pin|FND_F_Pin,	// 0
	FND_B_Pin|FND_C_Pin,                           // 1
	FND_A_Pin|FND_B_Pin|FND_D_Pin|FND_E_Pin|FND_G_Pin,         // 2
	FND_A_Pin|FND_B_Pin|FND_C_Pin|FND_D_Pin|FND_G_Pin,         // 3
	FND_B_Pin|FND_C_Pin|FND_F_Pin|FND_G_Pin,  			 // 4
	FND_A_Pin|FND_C_Pin|FND_D_Pin|FND_F_Pin|FND_G_Pin, 		 // 5
	FND_A_Pin|FND_C_Pin|FND_D_Pin|FND_E_Pin|FND_F_Pin|FND_G_Pin,   // 6
	FND_A_Pin|FND_B_Pin|FND_C_Pin,     				 // 7
	FND_A_Pin|FND_B_Pin|FND_C_Pin|FND_D_Pin|FND_E_Pin|FND_F_Pin|FND_G_Pin, // 8
	FND_A_Pin|FND_B_Pin|FND_C_Pin|FND_D_Pin|FND_F_Pin|FND_G_Pin    // 9
};


void clear_fnd(void)
{
	HAL_GPIO_WritePin(GPIOF, FND_font[8]|FND_DP_Pin, GPIO_PIN_RESET);
}


void display_fnd(uint8_t curr_floor)
{
	clear_fnd();
	HAL_GPIO_WritePin(GPIOF, FND_font[curr_floor], GPIO_PIN_SET);
}

