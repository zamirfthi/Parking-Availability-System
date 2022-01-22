/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
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
TIM_HandleTypeDef htim11;

/* USER CODE BEGIN PV */
//initialization of variables

int count = 3; //represents total number of available parking spaces

int Lot1 = GPIO_PIN_SET;              //initial value of parking lot 1 is set to HIGH which means available
int lastLot1State = GPIO_PIN_SET;     //initial value of previous status of parking lot 1 is set to HIGH which means available
int Lot2 = GPIO_PIN_SET;              //initial value of parking lot 2 is set to HIGH which means available
int lastLot2State = GPIO_PIN_SET;     //initial value of previous status of parking lot 2 is set to HIGH which means available
int Lot3 = GPIO_PIN_SET;              //initial value of parking lot 3 is set to HIGH which means available
int lastLot3State = GPIO_PIN_SET;     //initial value of previous status of parking lot 3 is set to HIGH which means available
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_TIM11_Init(void);
/* USER CODE BEGIN PFP */

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
  MX_TIM11_Init();
  /* USER CODE BEGIN 2 */


  HAL_TIM_Base_Start_IT(&htim11);    // Start timer with interrupt

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {

	  Lot1 = HAL_GPIO_ReadPin(GPIOA ,SENSOR1_Pin); //obtain value HIGH or LOW from sensor at parking lot 1
	  if(Lot1 != lastLot1State) //compare value obtained from sensor (current status) with previous status of parking lot
	  {
		  if(Lot1==GPIO_PIN_RESET) //if sensor returns value LOW
		  {
			  count--;                                    //decrease total available parking space
			  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_9, 1);    //turn on RED LED at parking lot 1

		  }
		  else //if sensor returns value HIGH
		  {
			  count++;                                   //increase total available parking space
			  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_9, 0);   //turn off RED LED at parking lot 1
		  }
	  }
	  lastLot1State = Lot1;   //update previous status of parking lot 1 for next iteration


	  Lot2 = HAL_GPIO_ReadPin(GPIOA ,SENSOR2_Pin);  //obtain value HIGH or LOW from sensor at parking lot 2
	  if(Lot2 != lastLot2State)  //compare value obtained from sensor (current status) with previous status of parking lot
	  {
		  if(Lot2==GPIO_PIN_RESET)  //if sensor returns value LOW
		  {
			  count--;                                   //decrease total available parking space
			  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_7, 1);   //turn on RED LED at parking lot 2

		  }
		  else //if sensor returns value HIGH
		  {
			  count++;                                   //increase total available parking space
			  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_7, 0);   //turn off RED LED at parking lot 2
		  }
	  }
	  lastLot2State = Lot2;   //update previous status of parking lot 2 for next iteration


	  Lot3 = HAL_GPIO_ReadPin(GPIOA ,SENSOR3_Pin);  //obtain value HIGH or LOW from sensor at parking lot 3
	  if(Lot3 != lastLot3State)  //compare value obtained from sensor (current status) with previous status of parking lot
	  {
		  if(Lot3==GPIO_PIN_RESET)  //if sensor returns value LOW
		  {
			  count--;                                   //decrease total available parking space
			  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, 1);   //turn on RED LED at parking lot 3

		  }
		  else //if sensor returns value HIGH
		  {
			  count++;                                   //increase total available parking space
			  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, 0);   //turn off RED LED at parking lot 3
		  }
	  }
	  lastLot3State = Lot3;   //update previous status of parking lot 3 for next iteration

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
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE2);
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

/**
  * @brief TIM11 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM11_Init(void)
{

  /* USER CODE BEGIN TIM11_Init 0 */

  /* USER CODE END TIM11_Init 0 */

  /* USER CODE BEGIN TIM11_Init 1 */

  /* USER CODE END TIM11_Init 1 */
  htim11.Instance = TIM11;
  htim11.Init.Prescaler = 1599;                                      // 16MHz/1600 = 10000 Hz
  htim11.Init.CounterMode = TIM_COUNTERMODE_UP;                      // 1/10000 = 0.1ms
  htim11.Init.Period = 19999;                                        // 0.1 ms x 20000 = 2 seconds
  htim11.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim11.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim11) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM11_Init 2 */

  /* USER CODE END TIM11_Init 2 */

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
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_7, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1|GPIO_PIN_4|GPIO_PIN_9|GPIO_PIN_10, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0|GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5
                          |GPIO_PIN_6, GPIO_PIN_RESET);

  /*Configure GPIO pins : PC0 PC1 PC7 */
  GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_7;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : PA1 PA4 PA9 PA10 */
  GPIO_InitStruct.Pin = GPIO_PIN_1|GPIO_PIN_4|GPIO_PIN_9|GPIO_PIN_10;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : SENSOR1_Pin SENSOR2_Pin SENSOR3_Pin */
  GPIO_InitStruct.Pin = SENSOR1_Pin|SENSOR2_Pin|SENSOR3_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : PB0 PB3 PB4 PB5
                           PB6 */
  GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5
                          |GPIO_PIN_6;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)  //timer interrupt callback
{
	if(htim==&htim11)  //every 2 seconds, the comparison is TRUE and the if loop is executed
	{
		  if(count==3)//display 3
		  {
			  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_10, 1); //d1
			  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, 1); //a
			  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, 1); //b
			  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, 1); //c
			  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, 1); //d
			  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, 0); //e
			  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, 0); //f
			  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, 1); //g
		  }
		  if(count==2)//display 2
		  {
			  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_10, 1); //d1
			  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, 1); //a
			  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, 1); //b
			  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, 0); //c
			  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, 1); //d
			  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, 1); //e
			  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, 0); //f
			  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, 1); //g
		  }
		  if(count==1)//display 1
		  {
			  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_10, 1); //d1
			  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, 0); //a
			  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, 1); //b
			  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, 1); //c
			  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, 0); //d
			  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, 0); //e
			  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, 0); //f
			  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, 0); //g
		  }
		  if(count==0)//display 0
		  {
			  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_10, 1); //d1
			  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, 1); //a
			  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, 1); //b
			  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, 1); //c
			  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, 1); //d
			  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, 1); //e
			  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, 1); //f
			  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, 0); //g

		  }
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

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
