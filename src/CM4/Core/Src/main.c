/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "openamp.h"
#include "resmgr_utility.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "stm32h747i_eval.h"

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

#ifndef HSEM_ID_0
#define HSEM_ID_0 (0U) /* HW semaphore 0*/
#endif

#define ADCCONVERTEDVALUES_BUFFER_SIZE ((uint32_t)  128)

#define RPMSG_SERVICE_NAME              "openamp_test"
#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
ADC_HandleTypeDef hadc1;

UART_HandleTypeDef huart1;

/* USER CODE BEGIN PV */

uint32_t index_buffer = 0;

/* Variable containing ADC conversions results */
uint16_t   ADCDualConvertedValues[ADCCONVERTEDVALUES_BUFFER_SIZE];   /* contain result of conversion from adc */

/* Flag for conversion complete (0, 1->completed) */
uint8_t conv_completed = 0;

static volatile int message_received;
volatile char received_data;
static struct rpmsg_endpoint rp_endpoint;

COM_InitTypeDef COM_Init;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
static void MX_GPIO_Init(void);
static void MX_ADC1_Init(void);
/* USER CODE BEGIN PFP */

static int rpmsg_recv_callback(struct rpmsg_endpoint *ept, void *data, size_t len, uint32_t src, void *priv)
{
  received_data = (char *) data;
  message_received=1;

  return 0;
}

unsigned int receive_message(void)
{
  while (message_received == 0)
  {
    OPENAMP_check_for_message();
  }
  message_received = 0;
  HAL_GPIO_WritePin(GPIOK, GPIO_PIN_3, 1);
//  HAL_Delay(2000);

  return received_data;
}

//PUTCHAR_PROTOTYPE {
////	HAL_UART_Transmit(&huart3, (uint8_t*)&ch, 1, 0xFFFF);
//	return ch;
//}

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
	int status = 0;
	int counter = 0;
	ResMgr_Status_t status_mgr;

  /* USER CODE END 1 */

/* USER CODE BEGIN Boot_Mode_Sequence_1 */
	  /*HW semaphore Clock enable*/
	  __HAL_RCC_HSEM_CLK_ENABLE();
	  /* Activate HSEM notification for Cortex-M4*/
	  HAL_HSEM_ActivateNotification(__HAL_HSEM_SEMID_TO_MASK(HSEM_ID_0));
	  /*
	  Domain D2 goes to STOP mode (Cortex-M4 in deep-sleep) waiting for Cortex-M7 to
	  perform system initialization (system clock config, external memory configuration.. )
	  */
	  HAL_PWREx_ClearPendingEvent();
	  HAL_PWREx_EnterSTOPMode(PWR_MAINREGULATOR_ON, PWR_STOPENTRY_WFE, PWR_D2_DOMAIN);
	  /* Clear HSEM flag */
	  __HAL_HSEM_CLEAR_FLAG(__HAL_HSEM_SEMID_TO_MASK(HSEM_ID_0));

/* USER CODE END Boot_Mode_Sequence_1 */
  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Resource Manager Utility initialisation ---------------------------------*/
  MX_RESMGR_UTILITY_Init();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_ADC1_Init();
  /* USER CODE BEGIN 2 */

	/* COM Pre-Initialization*/
	COM_Init.BaudRate = 115200;
	COM_Init.WordLength = COM_WORDLENGTH_8B;
	COM_Init.StopBits = COM_STOPBITS_1;
	COM_Init.Parity = COM_PARITY_NONE;
	COM_Init.HwFlowCtl = COM_HWCONTROL_NONE;

    /* USER CODE BEGIN 3 */

  /* Inilitize the mailbox use notify the other core on new message */
      MAILBOX_Init();

  /* Inilitize OpenAmp and libmetal libraries */
  if (MX_OPENAMP_Init(RPMSG_REMOTE, NULL)!= HAL_OK)
        Error_Handler();

  /* create a endpoint for rmpsg communication */
  status = OPENAMP_create_endpoint(&rp_endpoint, RPMSG_SERVICE_NAME, RPMSG_ADDR_ANY, rpmsg_recv_callback, NULL);
  if (status < 0) {
	  Error_Handler();
  }


  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	  while (index_buffer < ADCCONVERTEDVALUES_BUFFER_SIZE) {
	  		  HAL_ADC_Start(&hadc1);
	  	  	  HAL_ADC_PollForConversion(&hadc1, HAL_MAX_DELAY);
	  	  	  HAL_Delay(10);

	  	  	  // Read ADC data
	  	  	  uint16_t adc_value = HAL_ADC_GetValue(&hadc1);

	  	  	  // Save ADC value to buffer
	  	  	  ADCDualConvertedValues[index_buffer] = adc_value;
	  	  	  HAL_Delay(10);
	  	  	  index_buffer++;
	  	  	  HAL_ADC_Stop(&hadc1);
	    }

	    index_buffer = 0;
	    counter++;
	    receive_message();
	    HAL_GPIO_WritePin(GPIOK, GPIO_PIN_4, 0);
	    HAL_Delay(1000);

	    BSP_COM_Init(COM1, &COM_Init);
	    int seconds = HAL_GetTick()/1000;

		printf("M4 writes to UART at time %d: The clear buffer %d is\n\r", seconds, counter);
		for (int i=0; i< ADCCONVERTEDVALUES_BUFFER_SIZE; i++) {
					printf("%04x  ", ADCDualConvertedValues[i]);
				}
		printf("\n\n");
	    HAL_Delay(3000);
		BSP_COM_DeInit(COM1);


	    // send buffer data to M7
	    status = OPENAMP_send(&rp_endpoint, ADCDualConvertedValues, sizeof(ADCDualConvertedValues));
	    if (status < 0)
	        {
	          Error_Handler();
	        }
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */

  }
  /* USER CODE END 3 */
}

/**
  * @brief ADC1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_ADC1_Init(void)
{

  if (ResMgr_Request(RESMGR_ID_ADC1, RESMGR_FLAGS_ACCESS_NORMAL | \
                  RESMGR_FLAGS_CPU2 , 0, NULL) != RESMGR_OK)
  {
    /* USER CODE BEGIN RESMGR_UTILITY_ADC1 */
//    Error_Handler();
    /* USER CODE END RESMGR_UTILITY_ADC1 */
  }
  /* USER CODE BEGIN ADC1_Init 0 */

  /* USER CODE END ADC1_Init 0 */

  ADC_MultiModeTypeDef multimode = {0};
  ADC_ChannelConfTypeDef sConfig = {0};

  /* USER CODE BEGIN ADC1_Init 1 */

  /* USER CODE END ADC1_Init 1 */

  /** Common config
  */
  hadc1.Instance = ADC1;
  hadc1.Init.ClockPrescaler = ADC_CLOCK_ASYNC_DIV2;
  hadc1.Init.Resolution = ADC_RESOLUTION_16B;
  hadc1.Init.ScanConvMode = ADC_SCAN_DISABLE;
  hadc1.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
  hadc1.Init.LowPowerAutoWait = DISABLE;
  hadc1.Init.ContinuousConvMode = ENABLE;
  hadc1.Init.NbrOfConversion = 1;
  hadc1.Init.DiscontinuousConvMode = DISABLE;
  hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START;
  hadc1.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
  hadc1.Init.ConversionDataManagement = ADC_CONVERSIONDATA_DR;
  hadc1.Init.Overrun = ADC_OVR_DATA_PRESERVED;
  hadc1.Init.LeftBitShift = ADC_LEFTBITSHIFT_NONE;
  hadc1.Init.OversamplingMode = DISABLE;
  if (HAL_ADC_Init(&hadc1) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure the ADC multi-mode
  */
  multimode.Mode = ADC_MODE_INDEPENDENT;
  if (HAL_ADCEx_MultiModeConfigChannel(&hadc1, &multimode) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Regular Channel
  */
  sConfig.Channel = ADC_CHANNEL_0;
  sConfig.Rank = ADC_REGULAR_RANK_1;
  sConfig.SamplingTime = ADC_SAMPLETIME_1CYCLE_5;
  sConfig.SingleDiff = ADC_SINGLE_ENDED;
  sConfig.OffsetNumber = ADC_OFFSET_NONE;
  sConfig.Offset = 0;
  sConfig.OffsetSignedSaturation = DISABLE;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN ADC1_Init 2 */

  /* USER CODE END ADC1_Init 2 */

}

/**
  * @brief USART1 Initialization Function
  * @param None
  * @retval None
  */
void MX_USART1_UART_Init(void)
{

  if (ResMgr_Request(RESMGR_ID_USART1, RESMGR_FLAGS_ACCESS_NORMAL | \
                  RESMGR_FLAGS_CPU1 , 0, NULL) != RESMGR_OK)
  {
    /* USER CODE BEGIN RESMGR_UTILITY_USART1 */
    Error_Handler();
    /* USER CODE END RESMGR_UTILITY_USART1 */
  }
  /* USER CODE BEGIN USART1_Init 0 */

  /* USER CODE END USART1_Init 0 */

  /* USER CODE BEGIN USART1_Init 1 */

  /* USER CODE END USART1_Init 1 */
  huart1.Instance = USART1;
  huart1.Init.BaudRate = 115200;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_8;
  huart1.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart1.Init.ClockPrescaler = UART_PRESCALER_DIV1;
  huart1.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_SetTxFifoThreshold(&huart1, UART_TXFIFO_THRESHOLD_1_8) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_SetRxFifoThreshold(&huart1, UART_RXFIFO_THRESHOLD_1_8) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_DisableFifoMode(&huart1) != HAL_OK)
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
/* USER CODE BEGIN MX_GPIO_Init_1 */
/* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOK_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOK, GPIO_PIN_4, GPIO_PIN_RESET);

  /*Configure GPIO pin : PK4 */
  GPIO_InitStruct.Pin = GPIO_PIN_4;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOK, &GPIO_InitStruct);

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */

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
