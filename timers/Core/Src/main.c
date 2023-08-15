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
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define F_CPU 16000000
#define PRESCALER 2
#define DO 1046
#define RE 1175
#define MI 1318
#define FA 1397
#define SOL 1568
#define LA 1760
#define SI 1975
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
uint8_t tx_buff;
uint8_t rx_buff;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */
void Tapion();
void tone(uint32_t freq, uint32_t time);
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
  MX_TIM2_Init();
  MX_USART1_UART_Init();
  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  // HAL_TIM_Base_Start_IT(&htim2);

  tx_buff = 48;
  HAL_UART_Transmit(&huart1, &tx_buff, 1, 200);

  HAL_UART_Receive_IT(&huart1, &rx_buff, 1);

  Tapion();

  HAL_TIM_Base_Stop_IT(&htim2);

  // tone(4000, 1000);

  while (1)
  {
	  while(rx_buff == 0);
	  switch (rx_buff) {
		case 'a':
			tone(DO, 100);
			rx_buff = 0;
			break;
		case 's':
			tone(RE, 100);
			rx_buff = 0;
			break;
		case 'd':
			tone(MI, 100);
			rx_buff = 0;
			break;
		case 'f':
			tone(FA, 100);
			rx_buff = 0;
			break;
		case 'g':
			tone(SOL, 100);
			rx_buff = 0;
			break;
		case 'h':
			tone(LA, 100);
			rx_buff = 0;
			break;
		case 'j':
			tone(SI, 100);
			rx_buff = 0;
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
void tone(uint32_t freq, uint32_t time) {
	uint32_t arr_value;

	arr_value = (float)((2*F_CPU) / (PRESCALER*freq*4));

	HAL_TIM_Base_Stop_IT(&htim2);
	__HAL_TIM_SET_COUNTER(&htim2, 0);
	__HAL_TIM_SET_AUTORELOAD(&htim2, arr_value);
	HAL_TIM_Base_Start_IT(&htim2);

//	HAL_Delay(time);
//
//	HAL_TIM_Base_Stop_IT(&htim2);
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
	HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {
	if (huart->Instance == USART1) {
		HAL_UART_Transmit(&huart1, &rx_buff, 1, 200);
		HAL_UART_Receive_IT(&huart1, &rx_buff, 1);
	}
}

void Tapion() {
  tone(1046, 203);
  HAL_Delay(226);
  HAL_Delay(9);
  HAL_Delay(380);
  tone(1046, 611);
  HAL_Delay(679);
  HAL_Delay(45);
  tone(1046, 57);
  HAL_Delay(63);
  HAL_Delay(18);
  tone(1046, 65);
  HAL_Delay(72);
  HAL_Delay(706);
  HAL_Delay(289);
  tone(2093, 73);
  HAL_Delay(81);
  HAL_Delay(9);
  tone(1396, 105);
  HAL_Delay(117);
  HAL_Delay(27);
  HAL_Delay(63);
  tone(1396, 24);
  HAL_Delay(27);
  HAL_Delay(45);
  tone(2093, 40);
  HAL_Delay(45);
  tone(1396, 16);
  HAL_Delay(18);
  HAL_Delay(18);
  HAL_Delay(27);
  tone(1396, 65);
  HAL_Delay(72);
  tone(2093, 40);
  HAL_Delay(45);
  HAL_Delay(18);
  tone(1396, 32);
  HAL_Delay(36);
  HAL_Delay(72);
  tone(2093, 40);
  HAL_Delay(45);
  tone(1661, 285);
  HAL_Delay(317);
  HAL_Delay(45);
  tone(1760, 24);
  HAL_Delay(27);
  HAL_Delay(27);
  tone(1661, 40);
  HAL_Delay(45);
  tone(1864, 847);
  HAL_Delay(942);
  HAL_Delay(9);
  tone(1864, 187);
  HAL_Delay(208);
  HAL_Delay(9);
  HAL_Delay(72);
  tone(1864, 16);
  HAL_Delay(18);
  HAL_Delay(9);
  tone(1864, 48);
  HAL_Delay(54);
  HAL_Delay(226);
  tone(1396, 114);
  HAL_Delay(126);
  HAL_Delay(9);
  HAL_Delay(172);
  tone(1396, 57);
  HAL_Delay(63);
  HAL_Delay(9);
  tone(1396, 203);
  HAL_Delay(226);
  HAL_Delay(45);
  tone(1396, 65);
  HAL_Delay(72);
  tone(1567, 163);
  HAL_Delay(181);
  HAL_Delay(36);
  tone(1567, 57);
  HAL_Delay(63);
  HAL_Delay(18);
  tone(1567, 40);
  HAL_Delay(45);
  HAL_Delay(1114);
  HAL_Delay(606);
  tone(1864, 40);
  HAL_Delay(45);
  HAL_Delay(9);
  tone(1864, 24);
  HAL_Delay(27);
  HAL_Delay(9);
  tone(1864, 114);
  HAL_Delay(126);
  tone(1661, 8);
  HAL_Delay(9);
  HAL_Delay(18);
  tone(1661, 130);
  HAL_Delay(144);
  HAL_Delay(9);
  tone(1661, 65);
  HAL_Delay(72);
  HAL_Delay(18);
  tone(1661, 57);
  HAL_Delay(63);
  HAL_Delay(63);
  tone(1661, 32);
  HAL_Delay(36);
  HAL_Delay(561);
  tone(1396, 24);
  HAL_Delay(27);
  tone(1567, 285);
  HAL_Delay(317);
  HAL_Delay(18);
  tone(1567, 130);
  HAL_Delay(144);
  HAL_Delay(9);
  tone(1567, 114);
  HAL_Delay(126);
  HAL_Delay(18);
  tone(1046, 73);
  HAL_Delay(81);
  HAL_Delay(9);
  tone(1567, 8);
  HAL_Delay(9);
  HAL_Delay(36);
  tone(1567, 24);
  HAL_Delay(27);
  HAL_Delay(307);
  tone(1046, 611);
  HAL_Delay(679);
  HAL_Delay(45);
  tone(1046, 57);
  HAL_Delay(63);
  HAL_Delay(18);
  tone(1046, 73);
  HAL_Delay(81);
  HAL_Delay(697);
  HAL_Delay(289);
  tone(1396, 179);
  HAL_Delay(199);
  HAL_Delay(27);
  HAL_Delay(72);
  tone(1396, 24);
  HAL_Delay(27);
  HAL_Delay(45);
  tone(2093, 40);
  HAL_Delay(45);
  tone(1396, 24);
  HAL_Delay(27);
  HAL_Delay(9);
  HAL_Delay(27);
  tone(1396, 65);
  HAL_Delay(72);
  HAL_Delay(63);
  tone(2093, 16);
  HAL_Delay(18);
  tone(1396, 16);
  HAL_Delay(18);
  HAL_Delay(81);
  tone(2093, 32);
  HAL_Delay(36);
  tone(1661, 220);
  HAL_Delay(244);
  HAL_Delay(18);
  tone(1661, 40);
  HAL_Delay(45);
  HAL_Delay(126);
  tone(1661, 24);
  HAL_Delay(27);
  tone(1864, 1043);
  HAL_Delay(1159);
  HAL_Delay(9);
  HAL_Delay(72);
  tone(1864, 8);
  HAL_Delay(9);
  HAL_Delay(18);
  tone(1864, 57);
  HAL_Delay(63);
  HAL_Delay(217);
  tone(1396, 179);
  HAL_Delay(199);
  HAL_Delay(9);
  HAL_Delay(99);
  tone(1567, 211);
  HAL_Delay(235);
  HAL_Delay(9);
  tone(1396, 48);
  HAL_Delay(54);
  tone(1567, 8);
  HAL_Delay(9);
  HAL_Delay(9);
  HAL_Delay(27);
  tone(1396, 57);
  HAL_Delay(63);
  tone(1567, 57);
  HAL_Delay(63);
  HAL_Delay(45);
  tone(1567, 40);
  HAL_Delay(45);
  HAL_Delay(9);
  tone(1567, 32);
  HAL_Delay(36);
  HAL_Delay(45);
  tone(1567, 32);
  HAL_Delay(36);
  HAL_Delay(36);
  tone(1567, 40);
  HAL_Delay(45);
  HAL_Delay(425);
  tone(1661, 260);
  HAL_Delay(289);
  HAL_Delay(18);
  tone(1661, 40);
  HAL_Delay(45);
  HAL_Delay(126);
  HAL_Delay(72);
  tone(1661, 24);
  HAL_Delay(27);
  HAL_Delay(27);
  tone(1661, 40);
  HAL_Delay(45);
  tone(1567, 171);
  HAL_Delay(190);
  HAL_Delay(18);
  tone(1396, 48);
  HAL_Delay(54);
  HAL_Delay(18);
  HAL_Delay(18);
  HAL_Delay(9);
  tone(1567, 65);
  HAL_Delay(72);
  tone(1396, 16);
  HAL_Delay(18);
  HAL_Delay(18);
  tone(1396, 40);
  HAL_Delay(45);
  HAL_Delay(18);
  HAL_Delay(45);
  tone(1318, 24);
  HAL_Delay(27);
  tone(1244, 57);
  HAL_Delay(63);
  HAL_Delay(9);
  tone(1244, 195);
  HAL_Delay(217);
  HAL_Delay(9);
  tone(1244, 122);
  HAL_Delay(135);
  HAL_Delay(18);
  tone(1244, 211);
  HAL_Delay(235);
  HAL_Delay(36);
  tone(1244, 24);
  HAL_Delay(27);
  tone(1396, 57);
  HAL_Delay(63);
  HAL_Delay(9);
  tone(1396, 774);
  HAL_Delay(860);
  HAL_Delay(45);
  tone(1396, 40);
  HAL_Delay(45);
  HAL_Delay(9);
  tone(1046, 383);
  HAL_Delay(425);
  HAL_Delay(9);
  tone(1046, 73);
  HAL_Delay(81);
  HAL_Delay(9);
  HAL_Delay(99);
  tone(1046, 611);
  HAL_Delay(679);
  HAL_Delay(36);
  tone(1046, 57);
  HAL_Delay(63);
  HAL_Delay(18);
  tone(1046, 73);
  HAL_Delay(81);
  HAL_Delay(697);
  HAL_Delay(289);
  tone(1396, 187);
  HAL_Delay(208);
  HAL_Delay(27);
  HAL_Delay(72);
  tone(1396, 16);
  HAL_Delay(18);
  HAL_Delay(45);
  tone(2093, 40);
  HAL_Delay(45);
  tone(1396, 16);
  HAL_Delay(18);
  HAL_Delay(18);
  HAL_Delay(36);
  tone(1396, 65);
  HAL_Delay(72);
  tone(2093, 8);
  HAL_Delay(9);
  HAL_Delay(45);
  tone(1396, 40);
  HAL_Delay(45);
  HAL_Delay(81);
  tone(2093, 32);
  HAL_Delay(36);
  tone(1661, 301);
  HAL_Delay(335);
  HAL_Delay(90);
  tone(1661, 32);
  HAL_Delay(36);
  tone(1864, 1035);
  HAL_Delay(1150);
  HAL_Delay(18);
  HAL_Delay(72);
  tone(1864, 8);
  HAL_Delay(9);
  HAL_Delay(18);
  tone(1864, 48);
  HAL_Delay(54);
  HAL_Delay(217);
  tone(1396, 187);
  HAL_Delay(208);
  HAL_Delay(9);
  HAL_Delay(90);
  tone(1567, 220);
  HAL_Delay(244);
  HAL_Delay(18);
  tone(1396, 40);
  HAL_Delay(45);
  HAL_Delay(45);
  tone(1396, 48);
  HAL_Delay(54);
  tone(1567, 32);
  HAL_Delay(36);
  HAL_Delay(72);
  tone(1567, 40);
  HAL_Delay(45);
  HAL_Delay(72);
  tone(1567, 57);
  HAL_Delay(63);
  HAL_Delay(27);
  tone(1567, 40);
  HAL_Delay(45);
  HAL_Delay(1114);
  tone(1864, 277);
  HAL_Delay(307);
  HAL_Delay(27);
  HAL_Delay(262);
  tone(1864, 16);
  HAL_Delay(18);
  HAL_Delay(81);
  tone(1661, 57);
  HAL_Delay(63);
  HAL_Delay(45);
  tone(1864, 16);
  HAL_Delay(18);
  HAL_Delay(18);
  tone(1661, 24);
  HAL_Delay(27);
  HAL_Delay(18);
  tone(1661, 81);
  HAL_Delay(90);
  HAL_Delay(18);
  tone(1661, 154);
  HAL_Delay(172);
  HAL_Delay(45);
  tone(1661, 32);
  HAL_Delay(36);
  HAL_Delay(570);
  tone(1661, 16);
  HAL_Delay(18);
  tone(1567, 293);
  HAL_Delay(326);
  HAL_Delay(9);
  HAL_Delay(153);
  tone(1567, 114);
  HAL_Delay(126);
  HAL_Delay(18);
  tone(1567, 89);
  HAL_Delay(99);
  HAL_Delay(153);
  tone(1046, 24);
  HAL_Delay(27);
  HAL_Delay(9);
  tone(1046, 73);
  HAL_Delay(81);
  HAL_Delay(9);
  HAL_Delay(99);
  tone(1046, 611);
  HAL_Delay(679);
  HAL_Delay(36);
  tone(1046, 65);
  HAL_Delay(72);
  HAL_Delay(18);
  tone(1046, 65);
  HAL_Delay(72);
  HAL_Delay(697);
  HAL_Delay(289);
  tone(1396, 179);
  HAL_Delay(199);
  HAL_Delay(36);
  HAL_Delay(72);
  tone(1396, 24);
  HAL_Delay(27);
  HAL_Delay(36);
  tone(2093, 48);
  HAL_Delay(54);
  tone(1396, 8);
  HAL_Delay(9);
  HAL_Delay(18);
  HAL_Delay(27);
  tone(1396, 73);
  HAL_Delay(81);
  tone(2093, 8);
  HAL_Delay(9);
  HAL_Delay(54);
  tone(1396, 32);
  HAL_Delay(36);
  HAL_Delay(72);
  tone(2093, 32);
  HAL_Delay(36);
  tone(1661, 301);
  HAL_Delay(335);
  HAL_Delay(99);
  tone(1661, 32);
  HAL_Delay(36);
  HAL_Delay(1231);
  tone(1864, 16);
  HAL_Delay(18);
  HAL_Delay(18);
  tone(1864, 48);
  HAL_Delay(54);
  HAL_Delay(217);
  HAL_Delay(307);
  tone(1396, 57);
  HAL_Delay(63);
  HAL_Delay(18);
  tone(1396, 195);
  HAL_Delay(217);
  tone(1567, 8);
  HAL_Delay(9);
  HAL_Delay(9);
  HAL_Delay(36);
  tone(1396, 48);
  HAL_Delay(54);
  tone(1567, 81);
  HAL_Delay(90);
  HAL_Delay(27);
  tone(1567, 32);
  HAL_Delay(36);
  HAL_Delay(18);
  tone(1567, 24);
  HAL_Delay(27);
  HAL_Delay(45);
  tone(1567, 32);
  HAL_Delay(36);
  HAL_Delay(9);
  tone(1567, 65);
  HAL_Delay(72);
  HAL_Delay(434);
  tone(1661, 122);
  HAL_Delay(135);
  HAL_Delay(18);
  tone(1661, 105);
  HAL_Delay(117);
  HAL_Delay(36);
  tone(1661, 65);
  HAL_Delay(72);
  HAL_Delay(99);
  tone(1661, 32);
  HAL_Delay(36);
  HAL_Delay(18);
  HAL_Delay(18);
  tone(1661, 8);
  HAL_Delay(9);
  HAL_Delay(36);
  tone(1661, 40);
  HAL_Delay(45);
  HAL_Delay(208);
  tone(1567, 48);
  HAL_Delay(54);
  tone(1396, 8);
  HAL_Delay(9);
  HAL_Delay(36);
  tone(1567, 65);
  HAL_Delay(72);
  tone(1396, 24);
  HAL_Delay(27);
  HAL_Delay(9);
  tone(1396, 40);
  HAL_Delay(45);
  HAL_Delay(27);
  tone(1244, 122);
  HAL_Delay(135);
  HAL_Delay(9);
  HAL_Delay(27);
  tone(1479, 24);
  HAL_Delay(27);
  tone(1244, 138);
  HAL_Delay(153);
  HAL_Delay(9);
  tone(1244, 122);
  HAL_Delay(135);
  HAL_Delay(27);
  tone(1244, 105);
  HAL_Delay(117);
  HAL_Delay(27);
  tone(1244, 73);
  HAL_Delay(81);
  HAL_Delay(36);
  tone(1244, 24);
  HAL_Delay(27);
  tone(1396, 847);
  HAL_Delay(942);
  HAL_Delay(1847);
  tone(1046, 383);
  HAL_Delay(425);
  HAL_Delay(9);
  tone(1046, 73);
  HAL_Delay(81);
  HAL_Delay(9);
  HAL_Delay(99);
  tone(1046, 611);
  HAL_Delay(679);
  HAL_Delay(36);
  tone(1046, 65);
  HAL_Delay(72);
  HAL_Delay(9);
  tone(1046, 73);
  HAL_Delay(81);
  HAL_Delay(697);
  HAL_Delay(298);
  tone(1396, 179);
  HAL_Delay(199);
  HAL_Delay(27);
  HAL_Delay(72);
  tone(1396, 24);
  HAL_Delay(27);
  HAL_Delay(36);
  tone(2093, 48);
  HAL_Delay(54);
  tone(1396, 8);
  HAL_Delay(9);
  HAL_Delay(18);
  HAL_Delay(27);
  tone(1396, 73);
  HAL_Delay(81);
  tone(2093, 40);
  HAL_Delay(45);
  HAL_Delay(9);
  tone(1396, 40);
  HAL_Delay(45);
  HAL_Delay(63);
  tone(2093, 48);
  HAL_Delay(54);
  tone(1661, 285);
  HAL_Delay(317);
  HAL_Delay(45);
  tone(1760, 24);
  HAL_Delay(27);
  HAL_Delay(18);
  tone(1661, 48);
  HAL_Delay(54);
  HAL_Delay(1240);
  tone(1864, 8);
  HAL_Delay(9);
  HAL_Delay(18);
  tone(1864, 48);
  HAL_Delay(54);
  HAL_Delay(54);
  tone(1864, 24);
  HAL_Delay(27);
  HAL_Delay(135);
  tone(1396, 122);
  HAL_Delay(135);
  HAL_Delay(9);
  HAL_Delay(163);
  tone(1567, 16);
  HAL_Delay(18);
  HAL_Delay(9);
  tone(1396, 244);
  HAL_Delay(271);
  HAL_Delay(54);
  tone(1396, 57);
  HAL_Delay(63);
  tone(1567, 171);
  HAL_Delay(190);
  HAL_Delay(27);
  tone(1567, 57);
  HAL_Delay(63);
  HAL_Delay(27);
  tone(1567, 40);
  HAL_Delay(45);
  HAL_Delay(1105);
  tone(1864, 285);
  HAL_Delay(317);
  HAL_Delay(27);
  HAL_Delay(262);
  tone(1864, 40);
  HAL_Delay(45);
  HAL_Delay(18);
  tone(1661, 81);
  HAL_Delay(90);
  HAL_Delay(18);
  tone(1661, 24);
  HAL_Delay(27);
  HAL_Delay(18);
  tone(1864, 8);
  HAL_Delay(9);
  tone(1661, 16);
  HAL_Delay(18);
  HAL_Delay(9);
  tone(1661, 163);
  HAL_Delay(181);
  HAL_Delay(9);
  tone(1661, 32);
  HAL_Delay(36);
  HAL_Delay(18);
  tone(1661, 24);
  HAL_Delay(27);
  HAL_Delay(90);
  tone(1661, 40);
  HAL_Delay(45);
  HAL_Delay(81);
  tone(1661, 24);
  HAL_Delay(27);
  tone(1567, 717);
  HAL_Delay(797);
  HAL_Delay(9);
  HAL_Delay(153);
  tone(1567, 114);
  HAL_Delay(126);
  HAL_Delay(18);
  tone(1567, 89);
  HAL_Delay(99);
  tone(1046, 163);
  HAL_Delay(181);
  HAL_Delay(9);
  HAL_Delay(45);
  tone(1567, 24);
  HAL_Delay(27);
  tone(1046, 8);
  HAL_Delay(9);
  HAL_Delay(9);
  HAL_Delay(99);
  tone(1046, 611);
  HAL_Delay(679);
  HAL_Delay(36);
  tone(1046, 65);
  HAL_Delay(72);
  HAL_Delay(9);
  tone(1046, 73);
  HAL_Delay(81);
  HAL_Delay(697);
  HAL_Delay(298);
  tone(1396, 179);
  HAL_Delay(199);
  HAL_Delay(27);
  HAL_Delay(72);
  tone(1396, 16);
  HAL_Delay(18);
  HAL_Delay(45);
  tone(1661, 32);
  HAL_Delay(36);
  HAL_Delay(9);
  tone(2093, 8);
  HAL_Delay(9);
  tone(1396, 16);
  HAL_Delay(18);
  HAL_Delay(9);
  HAL_Delay(27);
  tone(1396, 73);
  HAL_Delay(81);
  HAL_Delay(54);
  tone(2093, 16);
  HAL_Delay(18);
  tone(1396, 24);
  HAL_Delay(27);
  HAL_Delay(72);
  tone(2093, 40);
  HAL_Delay(45);
  tone(1661, 220);
  HAL_Delay(244);
  HAL_Delay(9);
  tone(1661, 40);
  HAL_Delay(45);
  HAL_Delay(108);
  tone(1661, 40);
  HAL_Delay(45);
  HAL_Delay(1250);
  tone(1864, 8);
  HAL_Delay(9);
  HAL_Delay(18);
  tone(1864, 57);
  HAL_Delay(63);
  HAL_Delay(45);
  tone(1864, 24);
  HAL_Delay(27);
  HAL_Delay(135);
  HAL_Delay(317);
  tone(1396, 269);
  HAL_Delay(298);
  HAL_Delay(9);
  HAL_Delay(27);
  tone(1396, 65);
  HAL_Delay(72);
  tone(1567, 57);
  HAL_Delay(63);
  HAL_Delay(36);
  tone(1567, 89);
  HAL_Delay(99);
  HAL_Delay(27);
  tone(1567, 40);
  HAL_Delay(45);
  HAL_Delay(36);
  tone(1567, 40);
  HAL_Delay(45);
  HAL_Delay(434);
  tone(1661, 138);
  HAL_Delay(153);
  HAL_Delay(9);
  tone(1661, 105);
  HAL_Delay(117);
  HAL_Delay(27);
  tone(1661, 32);
  HAL_Delay(36);
  HAL_Delay(135);
  HAL_Delay(72);
  tone(1661, 8);
  HAL_Delay(9);
  HAL_Delay(36);
  tone(1661, 48);
  HAL_Delay(54);
  tone(1567, 171);
  HAL_Delay(190);
  HAL_Delay(9);
  tone(1396, 65);
  HAL_Delay(72);
  tone(1567, 8);
  HAL_Delay(9);
  HAL_Delay(18);
  HAL_Delay(9);
  tone(1567, 65);
  HAL_Delay(72);
  tone(1396, 16);
  HAL_Delay(18);
  HAL_Delay(9);
  tone(1396, 40);
  HAL_Delay(45);
  HAL_Delay(18);
  tone(1479, 8);
  HAL_Delay(9);
  HAL_Delay(126);
  tone(1244, 8);
  HAL_Delay(9);
  tone(1174, 8);
  HAL_Delay(9);
  tone(1244, 187);
  HAL_Delay(208);
  HAL_Delay(9);
  tone(1244, 57);
  HAL_Delay(63);
  HAL_Delay(9);
  tone(1244, 65);
  HAL_Delay(72);
  HAL_Delay(18);
  tone(1244, 211);
  HAL_Delay(235);
  HAL_Delay(27);
  tone(1244, 24);
  HAL_Delay(27);
  HAL_Delay(117);
  tone(1244, 40);
  HAL_Delay(45);
  tone(1396, 701);
  HAL_Delay(778);
  HAL_Delay(36);
  tone(1396, 48);
  HAL_Delay(54);
  HAL_Delay(9);
  HAL_Delay(72);
  tone(1396, 24);
  HAL_Delay(27);
  tone(1046, 114);
  HAL_Delay(126);
  HAL_Delay(9);
  HAL_Delay(380);
  tone(1046, 611);
  HAL_Delay(679);
  HAL_Delay(36);
  tone(1046, 65);
  HAL_Delay(72);
  HAL_Delay(18);
  tone(1046, 65);
  HAL_Delay(72);
  HAL_Delay(697);
  HAL_Delay(298);
  tone(1396, 187);
  HAL_Delay(208);
  HAL_Delay(18);
  HAL_Delay(72);
  tone(1396, 24);
  HAL_Delay(27);
  HAL_Delay(36);
  tone(2093, 48);
  HAL_Delay(54);
  tone(1396, 16);
  HAL_Delay(18);
  HAL_Delay(9);
  HAL_Delay(36);
  tone(1396, 65);
  HAL_Delay(72);
  tone(2093, 40);
  HAL_Delay(45);
  HAL_Delay(9);
  tone(1396, 48);
  HAL_Delay(54);
  HAL_Delay(9);
  tone(2093, 89);
  HAL_Delay(99);
  tone(1661, 301);
  HAL_Delay(335);
  HAL_Delay(81);
  tone(1661, 40);
  HAL_Delay(45);
  tone(1864, 1043);
  HAL_Delay(1159);
  HAL_Delay(9);
  HAL_Delay(72);
  tone(1864, 8);
  HAL_Delay(9);
  HAL_Delay(18);
  tone(1864, 48);
  HAL_Delay(54);
  HAL_Delay(54);
  tone(1864, 24);
  HAL_Delay(27);
  HAL_Delay(135);
  HAL_Delay(307);
  tone(1396, 285);
  HAL_Delay(317);
  HAL_Delay(36);
  tone(1396, 57);
  HAL_Delay(63);
  tone(1567, 81);
  HAL_Delay(90);
  HAL_Delay(9);
  tone(1567, 81);
  HAL_Delay(90);
  HAL_Delay(27);
  tone(1567, 73);
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
