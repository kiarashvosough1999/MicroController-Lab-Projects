/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
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

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */


static void enable_blue_button() {
	  __HAL_RCC_GPIOA_CLK_ENABLE();
	  GPIO_InitTypeDef GPIO_InitStruct = {0};
	  GPIO_InitStruct.Pin = GPIO_PIN_0;
	  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
	  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
}


static void enable_on_board_led() {
	  __HAL_RCC_GPIOE_CLK_ENABLE();
	  GPIO_InitTypeDef GPIO_InitStruct = {0};
	  GPIO_InitStruct.Pin = GPIO_PIN_8 | GPIO_PIN_9 | GPIO_PIN_10 | GPIO_PIN_11 | GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15;
	  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
	  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);
}

static void enable_ou_led() {
	  __HAL_RCC_GPIOC_CLK_ENABLE();
	  GPIO_InitTypeDef GPIO_InitStruct = {0};
	  GPIO_InitStruct.Pin = GPIO_PIN_0 | GPIO_PIN_1;
	  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
	  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);
}

static void enable_seven_segment() {
	  __HAL_RCC_GPIOD_CLK_ENABLE();
	  GPIO_InitTypeDef GPIO_InitStruct = {0};
	  GPIO_InitStruct.Pin = GPIO_PIN_8 | GPIO_PIN_9 | GPIO_PIN_10 | GPIO_PIN_11 | GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14;
	  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
	  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);
}



typedef struct {
    uint16_t A;
    uint16_t B;
    uint16_t C;
    uint16_t D;
    uint16_t E;
    uint16_t F;
    uint16_t G;
} SevenSegemnt;

SevenSegemnt initSevenSegment(
        uint16_t A,
        uint16_t B,
        uint16_t C,
        uint16_t D,
        uint16_t E,
        uint16_t F,
        uint16_t G
) {
    SevenSegemnt sevenSegemnt;
    sevenSegemnt.A = A;
    sevenSegemnt.B = B;
    sevenSegemnt.C = C;
    sevenSegemnt.D = D;
    sevenSegemnt.E = E;
    sevenSegemnt.F = F;
    sevenSegemnt.G = G;
    return sevenSegemnt;
}

static SevenSegemnt ZeroNumberSevenSegment = {1,1,1,1,1,1,0};
static SevenSegemnt OneNumberSevenSegment = {0,1,1,0,0,0,0};
static SevenSegemnt TwoNumberSevenSegment = {1,1,0,1,1,0,1};
static SevenSegemnt ThreeNumberSevenSegment = {1,1,1,1,0,0,1};
static SevenSegemnt FourNumberSevenSegment = {0,1,1,0,0,1,1};
static SevenSegemnt FiveNumberSevenSegment = {1,0,1,1,0,1,1};
static SevenSegemnt SixNumberSevenSegment = {1,0,1,1,1,1,1};
static SevenSegemnt SevenNumberSevenSegment = {1,1,1,0,0,0,0};
static SevenSegemnt EightNumberSevenSegment = {1,1,1,1,1,1,1};
static SevenSegemnt NineNumberSevenSegment = {1,1,1,0,0,1,1};

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
//I2C_HandleTypeDef hi2c1;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
//void SystemClock_Config(void);
//static void MX_GPIO_Init(void);
//static void MX_I2C1_Init(void);
//static void MX_SPI1_Init(void);
//static void MX_USB_PCD_Init(void);
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

  enable_blue_button();
  enable_on_board_led();
  enable_ou_led();
  enable_seven_segment();
//  MX_I2C1_Init();
//  MX_SPI1_Init();
//  MX_USB_PCD_Init();
  /* USER CODE BEGIN 2 */

  int counter = 0;
  int onBoardLEDNumber = 0;

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */



	  if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0) == 1) {

		  counter++;
		  if (counter == 10) {
			  onBoardLEDNumber++;
			  counter = 0;

			  if (onBoardLEDNumber > 6) {
				  onBoardLEDNumber = 0;
			  }

			  if (onBoardLEDNumber == 0) {
				  HAL_GPIO_WritePin(GPIOE,GPIO_PIN_8, 0);
				  HAL_GPIO_WritePin(GPIOE,GPIO_PIN_9, 1);
			  } else if (onBoardLEDNumber == 1) {
				  HAL_GPIO_WritePin(GPIOE,GPIO_PIN_9, 0);
				  HAL_GPIO_WritePin(GPIOE,GPIO_PIN_10, 1);
			  }
			  else if (onBoardLEDNumber == 2) {
			  				  HAL_GPIO_WritePin(GPIOE,GPIO_PIN_10, 0);
			  				  HAL_GPIO_WritePin(GPIOE,GPIO_PIN_11, 1);
			  			  }
			  else if (onBoardLEDNumber == 3) {
			  			  				  HAL_GPIO_WritePin(GPIOE,GPIO_PIN_11, 0);
			  			  				  HAL_GPIO_WritePin(GPIOE,GPIO_PIN_12, 1);
			  			  			  }
			  else if (onBoardLEDNumber == 4) {
			  			  HAL_GPIO_WritePin(GPIOE,GPIO_PIN_12, 0);
			  			 HAL_GPIO_WritePin(GPIOE,GPIO_PIN_13, 1);
			  			  			  			  }
			  else if (onBoardLEDNumber == 5) {
			  			  			  HAL_GPIO_WritePin(GPIOE,GPIO_PIN_13, 0);
			  			  			 HAL_GPIO_WritePin(GPIOE,GPIO_PIN_14, 1);
			  			  			  			  			  }
			  else if (onBoardLEDNumber == 6) {
			  			  			  HAL_GPIO_WritePin(GPIOE,GPIO_PIN_14, 0);
			  			  			 HAL_GPIO_WritePin(GPIOE,GPIO_PIN_15, 1);
			  			  			  			  			  }


		  }

		  HAL_GPIO_WritePin(GPIOD,GPIO_PIN_8, 0);
		  HAL_GPIO_WritePin(GPIOD,GPIO_PIN_9, 0);
		  HAL_GPIO_WritePin(GPIOD,GPIO_PIN_10, 0);
		  HAL_GPIO_WritePin(GPIOD,GPIO_PIN_11, 0);
		  HAL_GPIO_WritePin(GPIOD,GPIO_PIN_12, 0);
		  HAL_GPIO_WritePin(GPIOD,GPIO_PIN_13, 0);
		  HAL_GPIO_WritePin(GPIOD,GPIO_PIN_14, 0);

		  HAL_Delay(300);
		  SevenSegemnt sev = ZeroNumberSevenSegment;

		  HAL_GPIO_WritePin(GPIOC,GPIO_PIN_0, 0);
		  HAL_GPIO_WritePin(GPIOC,GPIO_PIN_1, 0);

		  if (counter == 0) {
			  sev = ZeroNumberSevenSegment;
			  HAL_GPIO_WritePin(GPIOC,GPIO_PIN_0, 1);
		  }
		  else if (counter == 1) {
			  sev = OneNumberSevenSegment;
			  HAL_GPIO_WritePin(GPIOC,GPIO_PIN_1, 1);
		  }
		  else if (counter == 2) {
		  	  sev = TwoNumberSevenSegment;
		  	HAL_GPIO_WritePin(GPIOC,GPIO_PIN_0, 1);
		  }
		  else if (counter == 3) {
		  	  sev = ThreeNumberSevenSegment;
		  	HAL_GPIO_WritePin(GPIOC,GPIO_PIN_1, 1);
		  }
		  else if (counter == 4) {
		  		  	  sev = FourNumberSevenSegment;
		  		  	HAL_GPIO_WritePin(GPIOC,GPIO_PIN_0, 1);
		  		  }
		  else if (counter == 5) {
		  		  	  sev = FiveNumberSevenSegment;
		  		  	HAL_GPIO_WritePin(GPIOC,GPIO_PIN_1, 1);
		  		  }
		  else if (counter == 6) {
		  		  	  sev = SixNumberSevenSegment;
		  		  	HAL_GPIO_WritePin(GPIOC,GPIO_PIN_0, 1);
		  		  }
		  else if (counter == 7) {
		  		  	  sev = SevenNumberSevenSegment;
		  		  	HAL_GPIO_WritePin(GPIOC,GPIO_PIN_1, 1);
		  		  }
		  else if (counter == 8) {
		  		  	  sev = EightNumberSevenSegment;
		  		  	HAL_GPIO_WritePin(GPIOC,GPIO_PIN_0, 1);
		  		  }
		  else if (counter == 9) {
		  		  	  sev = NineNumberSevenSegment;
		  		  	HAL_GPIO_WritePin(GPIOC,GPIO_PIN_1, 1);
		  		  }


		  HAL_GPIO_WritePin(GPIOD,GPIO_PIN_8, sev.A);
		  HAL_GPIO_WritePin(GPIOD,GPIO_PIN_9, sev.B);
		  HAL_GPIO_WritePin(GPIOD,GPIO_PIN_10, sev.C);
		  HAL_GPIO_WritePin(GPIOD,GPIO_PIN_11, sev.D);
		  HAL_GPIO_WritePin(GPIOD,GPIO_PIN_12, sev.E);
		  HAL_GPIO_WritePin(GPIOD,GPIO_PIN_13, sev.F);
		  HAL_GPIO_WritePin(GPIOD,GPIO_PIN_14, sev.G);

	  }


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
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI|RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_BYPASS;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL6;
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

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USB|RCC_PERIPHCLK_I2C1;
  PeriphClkInit.I2c1ClockSelection = RCC_I2C1CLKSOURCE_HSI;
  PeriphClkInit.USBClockSelection = RCC_USBCLKSOURCE_PLL;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
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
