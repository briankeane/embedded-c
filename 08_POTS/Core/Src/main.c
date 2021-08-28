/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
TIM_HandleTypeDef htim2;

UART_HandleTypeDef huart1;

/* USER CODE BEGIN PV */

uint8_t U1_RxChar;

// ------------ Utility Timer Variables
uint16_t B1dbTimer;
uint8_t B1Pressed_F;
uint8_t B1ActionTaken_F;
uint16_t B1HoldTime;

uint16_t BGrnDbTimer;
uint8_t BGrnPressed_F;
uint8_t BGrnActionTaken_F;
uint16_t BGrnHoldTime;

uint16_t BRedDbTimer;
uint8_t BRedPressed_F;
uint8_t BRedActionTaken_F;
uint16_t BRedHoldTime;

// msec Timing: Make utility timers 16-bit
uint16_t TestTimer;

// sec Timing
uint16_t SecsCounter;

// LED Direction
uint8_t LedDirection = CLOCKWISE;
uint8_t LedStates[] = { LED_RED, LED_BLU, LED_GRN, LED_ORN };
uint8_t LedCount = 4;
uint8_t LedStatesIndex = 0;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_TIM2_Init(void);
static void MX_USART1_UART_Init(void);
/* USER CODE BEGIN PFP */
void CheckSWs(void);
void UpdateLEDState(void);
void handleBtn1Pressed(void);
void handleBtnGrnPressed(void);
void handleBtnRedPressed(void);
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
  HAL_TIM_Base_Start_IT(&htim2);
  USART1->CR1 |= 1<<5;  //USART1_CR1_RE;  // Enable RXNE interrupt (receiver not empty)
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */

	if (!TestTimer) {
		TestTimer = 500;

	if (U1_RxChar == 'A')
		HAL_UART_Transmit(&huart1, (uint8_t*) "A-Test\r\n", 8, 100);  // Send msg
	else if (U1_RxChar == 'B')
		HAL_UART_Transmit(&huart1, (uint8_t*) "B-Test\r\n", 8, 100);  // Send msg
	else
		HAL_UART_Transmit(&huart1, (uint8_t*) "Enter A or B\r\n", 14, 100);  // Send msg
	}

	CheckSWs();
	UpdateLEDState();

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
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 4;
  RCC_OscInitStruct.PLL.PLLN = 168;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 7;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief TIM2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM2_Init(void)
{

  /* USER CODE BEGIN TIM2_Init 0 */

  /* USER CODE END TIM2_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM2_Init 1 */

  /* USER CODE END TIM2_Init 1 */
  htim2.Instance = TIM2;
  htim2.Init.Prescaler = 42000;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = 1;
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim2) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim2, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM2_Init 2 */

  /* USER CODE END TIM2_Init 2 */

}

/**
  * @brief USART1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART1_UART_Init(void)
{

  /* USER CODE BEGIN USART1_Init 0 */

  /* USER CODE END USART1_Init 0 */

  /* USER CODE BEGIN USART1_Init 1 */

  /* USER CODE END USART1_Init 1 */
  huart1.Instance = USART1;
  huart1.Init.BaudRate = 9600;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART1_Init 2 */

  /* USER CODE END USART1_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOD, GRN_LED_Pin|ORN_LED_Pin|RED_LED_Pin|BLU_LED_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : PC0 */
  GPIO_InitStruct.Pin = GPIO_PIN_0;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pin : PA0 */
  GPIO_InitStruct.Pin = GPIO_PIN_0;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : GRN_LED_Pin ORN_LED_Pin RED_LED_Pin BLU_LED_Pin */
  GPIO_InitStruct.Pin = GRN_LED_Pin|ORN_LED_Pin|RED_LED_Pin|BLU_LED_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

  /*Configure GPIO pins : BTN_GRN_Pin BTN_RED_Pin */
  GPIO_InitStruct.Pin = BTN_GRN_Pin|BTN_RED_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */
// Use TIM2 as 1ms utility timer...
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	// --------------------------------------------
	// Millisecond timers:
	// --------------------------------------------

	// These timers can be disabled... Set the timer to TIMER_DISABLE (Defined as 0xFFFFFF) and then
	if (TestTimer)
		TestTimer--;

	++SecsCounter;
	if ( SecsCounter == 1000)
	{
		SecsCounter = 0;

		// Handle any 1 sec events or counters...
//		BLU_LED_TOGGLE();
	}

	if ( B1 != BUTTON_PRESSED)
	{
		B1dbTimer = 0;
		B1Pressed_F = FALSE;
	}
	else
	{
		if (B1dbTimer < 255)
			++B1dbTimer;
		if ( B1dbTimer > DB_TIME )
			B1Pressed_F = TRUE;

	}

	if ( B_GRN != B_GRN_PRESSED)
	{
		BGrnDbTimer = 0;
		BGrnPressed_F = FALSE;
	}
	else
	{
		if (BGrnDbTimer < 255)
			++BGrnDbTimer;
		if ( BGrnDbTimer > DB_TIME )
			BGrnPressed_F = TRUE;
	}

	if ( B_RED != B_RED_PRESSED)
	{
		BRedDbTimer = 0;
		BRedPressed_F = FALSE;
	}
	else
	{
		if (BRedDbTimer < 255)
			++BRedDbTimer;
		if ( BRedDbTimer > DB_TIME )
			BRedPressed_F = TRUE;
	}


	if (LED_Timer)
	{
		LED_Timer--;
	}
}

void CheckSWs(void)
{
	if (B1Pressed_F && !B1ActionTaken_F)
	{
		handleBtn1Pressed();
		B1ActionTaken_F = TRUE;
	}
	else if ( !B1Pressed_F && (B1ActionTaken_F))
	{
		B1ActionTaken_F = FALSE;
	}

	if (BGrnPressed_F && !BGrnActionTaken_F)
	{
		handleBtnGrnPressed();
		BGrnActionTaken_F = TRUE;
	}
	else if ( !BGrnPressed_F && (BGrnActionTaken_F))
	{
		BGrnActionTaken_F = FALSE;
	}

	if (BRedPressed_F && !BRedActionTaken_F)
	{
		handleBtnRedPressed();
		BRedActionTaken_F = TRUE;
	}
	else if ( !BRedPressed_F && (BRedActionTaken_F))
	{

		BRedActionTaken_F = FALSE;
	}
}

void handleBtnRedPressed(void)
{
	if (LedDirection == CLOCKWISE)
	{
		LedDirection = COUNTERCLOCKWISE;
	}
	else
	{
		LedDirection = CLOCKWISE;
	}
}

void handleBtnGrnPressed(void)
{
	if (LED_State == LED_IDLE)
	{
		LED_Start = TRUE;
		LED_Timer = LED_WAIT_TIME_MS;
	}
	else
	{
		GRN_LED_OFF();
		ORN_LED_OFF();
		RED_LED_OFF();
		BLU_LED_OFF();

		LED_Start = FALSE;
		LED_State = LED_IDLE;
	}

}

void handleBtn1Pressed(void)
{
	LED_Start = TRUE;
	LED_Timer = LED_WAIT_TIME_MS;
}

void UpdateLEDState(void)
{
	// Place "always" code here then check each state
	if (LED_State == LED_IDLE)
	{
		if (LED_Start)
		{
			LED_Start = FALSE;
			RED_LED_ON();
			LED_State = LED_RED;
			LED_Timer = LED_WAIT_TIME_MS;
		}
	}
	else if (!LED_Timer)
	{
		if (LedDirection == CLOCKWISE)
		{
			LedStatesIndex++;

			// IF it's at the end of the array, start over
			if (LedStatesIndex >= LedCount)
			{
				LedStatesIndex = 0;
			}
		}
		// ELSE LedDirection == COUNTERCLOCKWISE
		else
		{
			if (LedStatesIndex == 0)
			{
				LedStatesIndex = LedCount - 1;
			}
			else
			{
				LedStatesIndex--;
			}
		}
		SwitchLED(LED_State, LedStates[LedStatesIndex]);
		LED_Timer = LED_WAIT_TIME_MS;
	}

}

void SwitchLED(uint8_t oldState, uint8_t newState)
{
	switch (oldState) {
	case LED_RED:
		RED_LED_OFF();
		break;
	case LED_BLU:
		BLU_LED_OFF();
		break;
	case LED_GRN:
		GRN_LED_OFF();
		break;
	case LED_ORN:
		ORN_LED_OFF();
		break;
	}

	switch (newState) {
	case LED_RED:
		RED_LED_ON();
		break;
	case LED_BLU:
		BLU_LED_ON();
		break;
	case LED_GRN:
		GRN_LED_ON();
		break;
	case LED_ORN:
		ORN_LED_ON();
		break;
	}
	LED_State = newState;
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
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
