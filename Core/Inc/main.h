/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define COL1_Pin GPIO_PIN_2
#define COL1_GPIO_Port GPIOE
#define COL2_Pin GPIO_PIN_3
#define COL2_GPIO_Port GPIOE
#define COL3_Pin GPIO_PIN_4
#define COL3_GPIO_Port GPIOE
#define COL4_Pin GPIO_PIN_5
#define COL4_GPIO_Port GPIOE
#define COL5_Pin GPIO_PIN_6
#define COL5_GPIO_Port GPIOE
#define FND_A_Pin GPIO_PIN_0
#define FND_A_GPIO_Port GPIOF
#define FND_B_Pin GPIO_PIN_1
#define FND_B_GPIO_Port GPIOF
#define FND_C_Pin GPIO_PIN_2
#define FND_C_GPIO_Port GPIOF
#define FND_D_Pin GPIO_PIN_3
#define FND_D_GPIO_Port GPIOF
#define FND_E_Pin GPIO_PIN_4
#define FND_E_GPIO_Port GPIOF
#define FND_F_Pin GPIO_PIN_5
#define FND_F_GPIO_Port GPIOF
#define FND_G_Pin GPIO_PIN_7
#define FND_G_GPIO_Port GPIOF
#define FND_DP_Pin GPIO_PIN_8
#define FND_DP_GPIO_Port GPIOF
#define MCO_Pin GPIO_PIN_0
#define MCO_GPIO_Port GPIOH
#define RMII_MDC_Pin GPIO_PIN_1
#define RMII_MDC_GPIO_Port GPIOC
#define RMII_REF_CLK_Pin GPIO_PIN_1
#define RMII_REF_CLK_GPIO_Port GPIOA
#define RMII_MDIO_Pin GPIO_PIN_2
#define RMII_MDIO_GPIO_Port GPIOA
#define RMII_CRS_DV_Pin GPIO_PIN_7
#define RMII_CRS_DV_GPIO_Port GPIOA
#define RMII_RXD0_Pin GPIO_PIN_4
#define RMII_RXD0_GPIO_Port GPIOC
#define RMII_RXD1_Pin GPIO_PIN_5
#define RMII_RXD1_GPIO_Port GPIOC
#define LD1_Pin GPIO_PIN_0
#define LD1_GPIO_Port GPIOB
#define PhotoSensor_EXIT12_Pin GPIO_PIN_12
#define PhotoSensor_EXIT12_GPIO_Port GPIOF
#define PhotoSensor_EXIT12_EXTI_IRQn EXTI15_10_IRQn
#define PhotoSensor_EXIT13_Pin GPIO_PIN_13
#define PhotoSensor_EXIT13_GPIO_Port GPIOF
#define PhotoSensor_EXIT13_EXTI_IRQn EXTI15_10_IRQn
#define PhotoSensor_EXIT14_Pin GPIO_PIN_14
#define PhotoSensor_EXIT14_GPIO_Port GPIOF
#define PhotoSensor_EXIT14_EXTI_IRQn EXTI15_10_IRQn
#define PhotoSensor_EXIT15_Pin GPIO_PIN_15
#define PhotoSensor_EXIT15_GPIO_Port GPIOF
#define PhotoSensor_EXIT15_EXTI_IRQn EXTI15_10_IRQn
#define COL6_Pin GPIO_PIN_7
#define COL6_GPIO_Port GPIOE
#define COL7_Pin GPIO_PIN_8
#define COL7_GPIO_Port GPIOE
#define COL8_Pin GPIO_PIN_9
#define COL8_GPIO_Port GPIOE
#define BTN2_Pin GPIO_PIN_12
#define BTN2_GPIO_Port GPIOE
#define BTN1_Pin GPIO_PIN_14
#define BTN1_GPIO_Port GPIOE
#define BTN0_Pin GPIO_PIN_15
#define BTN0_GPIO_Port GPIOE
#define RMII_TXD1_Pin GPIO_PIN_13
#define RMII_TXD1_GPIO_Port GPIOB
#define LD3_Pin GPIO_PIN_14
#define LD3_GPIO_Port GPIOB
#define STLK_RX_Pin GPIO_PIN_8
#define STLK_RX_GPIO_Port GPIOD
#define STLK_TX_Pin GPIO_PIN_9
#define STLK_TX_GPIO_Port GPIOD
#define StepMotor_IN1_Pin GPIO_PIN_11
#define StepMotor_IN1_GPIO_Port GPIOD
#define StepMotor_IN2_Pin GPIO_PIN_12
#define StepMotor_IN2_GPIO_Port GPIOD
#define StepMotor_IN3_Pin GPIO_PIN_13
#define StepMotor_IN3_GPIO_Port GPIOD
#define StepMotor_IN4_Pin GPIO_PIN_14
#define StepMotor_IN4_GPIO_Port GPIOD
#define USB_PowerSwitchOn_Pin GPIO_PIN_6
#define USB_PowerSwitchOn_GPIO_Port GPIOG
#define USB_OverCurrent_Pin GPIO_PIN_7
#define USB_OverCurrent_GPIO_Port GPIOG
#define BTN3_Pin GPIO_PIN_8
#define BTN3_GPIO_Port GPIOC
#define BTN4_Pin GPIO_PIN_9
#define BTN4_GPIO_Port GPIOC
#define USB_SOF_Pin GPIO_PIN_8
#define USB_SOF_GPIO_Port GPIOA
#define USB_VBUS_Pin GPIO_PIN_9
#define USB_VBUS_GPIO_Port GPIOA
#define USB_ID_Pin GPIO_PIN_10
#define USB_ID_GPIO_Port GPIOA
#define USB_DM_Pin GPIO_PIN_11
#define USB_DM_GPIO_Port GPIOA
#define USB_DP_Pin GPIO_PIN_12
#define USB_DP_GPIO_Port GPIOA
#define TMS_Pin GPIO_PIN_13
#define TMS_GPIO_Port GPIOA
#define TCK_Pin GPIO_PIN_14
#define TCK_GPIO_Port GPIOA
#define BTN5_Pin GPIO_PIN_10
#define BTN5_GPIO_Port GPIOC
#define BTN6_Pin GPIO_PIN_11
#define BTN6_GPIO_Port GPIOC
#define ROW1_Pin GPIO_PIN_0
#define ROW1_GPIO_Port GPIOD
#define ROW2_Pin GPIO_PIN_1
#define ROW2_GPIO_Port GPIOD
#define ROW3_Pin GPIO_PIN_2
#define ROW3_GPIO_Port GPIOD
#define ROW4_Pin GPIO_PIN_3
#define ROW4_GPIO_Port GPIOD
#define ROW5_Pin GPIO_PIN_4
#define ROW5_GPIO_Port GPIOD
#define ROW6_Pin GPIO_PIN_5
#define ROW6_GPIO_Port GPIOD
#define ROW7_Pin GPIO_PIN_6
#define ROW7_GPIO_Port GPIOD
#define ROW8_Pin GPIO_PIN_7
#define ROW8_GPIO_Port GPIOD
#define RMII_TX_EN_Pin GPIO_PIN_11
#define RMII_TX_EN_GPIO_Port GPIOG
#define RMII_TXD0_Pin GPIO_PIN_13
#define RMII_TXD0_GPIO_Port GPIOG
#define LD2_Pin GPIO_PIN_7
#define LD2_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
