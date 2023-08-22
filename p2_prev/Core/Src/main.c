/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "i2c.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <string.h>
#include <stdio.h>
#include "rgb_pwm.h"
#include "at24c_xxx.h"
#include "xprintf.h"
#include "edx_xprintf.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */
#define BUZZER_HANDLER 	&htim3
#define F_CPU 			16000000
#define PRESCALER		2
/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
rgb_color_t led_color;
volatile uint32_t tim_counter;
uint8_t kbd, alarm_case;
char tx_buffer[200];
uint8_t kbd_keys[4][4] = {
		{'D', 'C', 'B', 'A'},
		{'#', '9', '6', '3'},
		{'0', '8', '5', '2'},
		{'*', '7', '4', '1'}
};
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */
void write_nibble(uint8_t dato);
void tone(uint32_t freq, uint32_t time);
void kbd_get_print_key(uint8_t *kbd_key);
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USART1_UART_Init();
  MX_TIM2_Init();
  MX_I2C1_Init();
  MX_TIM3_Init();
  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  xprintf_init();

  rgb_pwm_star();
  led_color.colors.red = 100;
  led_color.colors.green = 10;
  led_color.colors.blue = 10;
  rgb_pwm_update(&led_color);


  xprint_clear();
  xprintf("Cerradura electronica\n\r\n\r\n\r");
  xprintf("A. Digitar password\n\r");
  xprintf("B. Agregar password\n\r");
  xprintf("C. Borrar password\n\r");
  xprintf("D. Ver lista de password\n\r");

  while (1)
  {
	  kbd = 0;
	  while(!kbd){
		  kbd_get_print_key(&kbd);
		  HAL_Delay(20);
	  }

	  alarm_case = kbd;
	  switch(alarm_case){
		  case 'A': //Insertar password
			  break;

		  case 'B': //Agregar password
			  break;

		  case 'C': //Borrar password
			  break;

		  case 'D': //Ver password
			  break;

		  default:
			  break;
	  }


    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
void write_nibble(uint8_t dato){
	uint8_t bit0, bit1, bit2, bit3;

	bit0 = dato & 0b0001;  			// 1
	bit1 = (dato & 0b0010) >> 1; 	// 1
	bit2 = (dato & 0b0100) >> 2; 	// 0
	bit3 = (dato & 0b1000) >> 3; 	// 1

	HAL_GPIO_WritePin(KBD_OUT0_GPIO_Port, KBD_OUT0_Pin, (GPIO_PinState)(bit0));
	HAL_GPIO_WritePin(KBD_OUT1_GPIO_Port, KBD_OUT1_Pin, (GPIO_PinState)(bit1));
	HAL_GPIO_WritePin(KBD_OUT2_GPIO_Port, KBD_OUT2_Pin, (GPIO_PinState)(bit2));
	HAL_GPIO_WritePin(KBD_OUT3_GPIO_Port, KBD_OUT3_Pin, (GPIO_PinState)(bit3));

}

void kbd_get_print_key(uint8_t *kbd_key){
	uint8_t kbd_data = 0;

	for(uint8_t i = 0; i < 4; i++){
	  write_nibble(1 << i);
	  if(HAL_GPIO_ReadPin(KBD_IN0_GPIO_Port, KBD_IN0_Pin)){
		  while(HAL_GPIO_ReadPin(KBD_IN0_GPIO_Port, KBD_IN0_Pin));

		  kbd_data = kbd_keys[i][0];
		  xprintf("%c", kbd_data);
		  break;
	  }

	  else if(HAL_GPIO_ReadPin(KBD_IN1_GPIO_Port, KBD_IN1_Pin)){
		  while(HAL_GPIO_ReadPin(KBD_IN1_GPIO_Port, KBD_IN1_Pin));

		  kbd_data = kbd_keys[i][1];
		  xprintf("%c", kbd_data);
		  break;
	  }

	  else if(HAL_GPIO_ReadPin(KBD_IN2_GPIO_Port, KBD_IN2_Pin)){
		  while(HAL_GPIO_ReadPin(KBD_IN2_GPIO_Port, KBD_IN2_Pin));

		  kbd_data = kbd_keys[i][2];
		  xprintf("%c", kbd_data);
		  break;
	  }

	  else if(HAL_GPIO_ReadPin(KBD_IN3_GPIO_Port, KBD_IN3_Pin)){
		  while(HAL_GPIO_ReadPin(KBD_IN3_GPIO_Port, KBD_IN3_Pin));

		  kbd_data = kbd_keys[i][3];
		  xprintf("%c", kbd_data);
		  break;
	  }

	}

	*kbd_key = kbd_data;
}
void tone(uint32_t freq, uint32_t time){
	uint32_t arr_value = 0, aux1, aux2;

	aux1 = 2 * F_CPU;
	aux2 = PRESCALER * freq * 4;
	arr_value = (float) ((aux1) / (aux2));

	HAL_TIM_Base_Stop_IT(BUZZER_HANDLER);

	__HAL_TIM_SET_COUNTER(&htim2, 0);
	__HAL_TIM_SET_AUTORELOAD(&htim2, arr_value);
	HAL_TIM_Base_Start_IT(BUZZER_HANDLER);

	HAL_Delay(time);
	HAL_TIM_Base_Stop_IT(BUZZER_HANDLER);
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim){
	if(htim->Instance == TIM3){
		HAL_GPIO_TogglePin(BUZZER_GPIO_Port, BUZZER_Pin);
	}
}
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
