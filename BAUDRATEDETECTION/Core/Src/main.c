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

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
//#include "usbd_cdc_if.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define RESPONSE_BUFFER_SIZE 64
#define PRINT_BUFFER_SIZE 64
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
UART_HandleTypeDef huart1;
UART_HandleTypeDef huart2;

/* USER CODE BEGIN PV */
char rxBuffer[RESPONSE_BUFFER_SIZE];
char received_char;
int baudRate[] = {1200, 2400, 4800, 9600, 19200, 38400, 57600, 115200};
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART2_UART_Init(void);
static void MX_USART1_UART_Init(void);
/* USER CODE BEGIN PFP */
void sendATCommand(const char *command, uint32_t timeOut);
void USART_SendChar(char ch);
char USART_ReceiveChar(void);
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
  MX_USART2_UART_Init();
  MX_USART1_UART_Init();
  /* USER CODE BEGIN 2 */

//	const char *command1 = "AT+UART=115200,1,0\r\n";
//  	const char *command1 = "AT+NAME\r\n";
  	HAL_Delay(1000);
//  	const char command1[] = "AT\r\n";
  	const char command1[] = "AT+NAME=ESP30x";

//    memset(rxBuffer, 0, RESPONSE_BUFFER_SIZE);
//    char buffer[256];

//	HAL_Delay(1000);

    HAL_UART_Transmit(&huart1, (uint8_t *)command1, strlen(command1), 300);
    HAL_UART_Receive(&huart1, (uint8_t *)rxBuffer, strlen(rxBuffer), 300);
//    snprintf(buffer, 256, "Response: %s\r\n", rxBuffer);
//    CDC_Transmit_FS((uint8_t*)buffer, strlen(buffer));

//	for (int i = 0; i < 8; i++) {
//		huart2.Init.BaudRate = baudRate[i];
//		HAL_UART_Init(&huart2);
//		sendATCommand("AT", 800); // HC-06
////		sendATCommand("AT\r\n", 200); // Todos os outros
//      // Para o HC-05, não se deve colocar \r\n ou \r ou \n
//    	// Para o HC-05, a alteração do nome é assim: "AT+NAME=ESP30x";
//		// Para o HC-05, deve-se colocar no modo AT pressionando o botão e soltando depois de alimentá-lo
//		// Para o HC-05, no modo AT, a velocidade é sempre 38400. Quando se muda a velocidade, muda-se a velocidade de operação
//		// Para o HC-05, altera-se a velocidade com: AT+UART=baudrate,0,0
//		// Para o HC-06 - que é só opera em modo slave - não se deve acrescentar \r\n e o timeOut deve ser >= 600
//		// Para o HC-06, a baudrate padrão e 9600
//		// Para o HC-06, altera-se velocidade com: AT+BAUDx (x=1(1200), ..., x=8(115200)
//		// Para o HM-10, altera-se velocidade com: AT+BAUDx (x=1(1200), ..., x=8(115200)
//	}

//	HAL_UART_Transmit(&huart2, "AT+UART=115200,1,0\r\n", strlen("AT+UART=115200,1,0\r\n"), 200);
//	HAL_UART_Receive(&huart2, (uint8_t *)rxBuffer, RESPONSE_BUFFER_SIZE, timeOut);
//	CDC_Transmit_FS((uint8_t*)buffer, strlen(buffer));

	//sendATCommand("AT\r\n", 100);
	//sendATCommand("AT+UART=115200,1,0\r\n", 400);

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
	while (1) {
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
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 12;
  RCC_OscInitStruct.PLL.PLLN = 96;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
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
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_3) != HAL_OK)
  {
    Error_Handler();
  }
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
  huart1.Init.BaudRate = 38400;
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
  * @brief USART2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART2_UART_Init(void)
{

  /* USER CODE BEGIN USART2_Init 0 */

  /* USER CODE END USART2_Init 0 */

  /* USER CODE BEGIN USART2_Init 1 */

  /* USER CODE END USART2_Init 1 */
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 38400;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */

  /* USER CODE END USART2_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
/* USER CODE BEGIN MX_GPIO_Init_1 */
/* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */
// Function to send an AT command and receive the response
void sendATCommand(const char *command, uint32_t timeOut) {
    memset(rxBuffer, 0, RESPONSE_BUFFER_SIZE);
    HAL_UART_Transmit(&huart2, (uint8_t *)command, strlen(command), timeOut);
    HAL_UART_Receive(&huart2, (uint8_t *)rxBuffer, RESPONSE_BUFFER_SIZE, timeOut);
    if (strstr(rxBuffer, "OK") != NULL) {
        char buffer[PRINT_BUFFER_SIZE];
        snprintf(buffer, PRINT_BUFFER_SIZE, "Baudrate: %ld - Response: %s\r\n", huart2.Init.BaudRate, rxBuffer);
        CDC_Transmit_FS((uint8_t*)buffer, strlen(buffer));
    } else {
        char buffer[PRINT_BUFFER_SIZE];
        snprintf(buffer, PRINT_BUFFER_SIZE, "Baudrate: %ld - No response\r\n", huart2.Init.BaudRate);
        CDC_Transmit_FS((uint8_t*)buffer, strlen(buffer));
    }
}

// Função para enviar um caractere via USART
void USART_SendChar(char ch) {
	HAL_UART_Transmit(&huart2, (uint8_t*) &ch, 1, HAL_MAX_DELAY);
}

// Função para receber um caractere via USART
char USART_ReceiveChar(void) {
	uint8_t ch;
	HAL_UART_Receive(&huart2, &ch, 1, HAL_MAX_DELAY);
	return (char) ch;
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
	while (1) {
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
