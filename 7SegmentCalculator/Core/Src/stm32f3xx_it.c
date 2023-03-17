/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    stm32f3xx_it.c
  * @brief   Interrupt Service Routines.
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
#include "stm32f3xx_it.h"
#include "string.h"
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN TD */

/* USER CODE END TD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

typedef enum { false, true } bool;

extern int counter;

int segmentStepCounter = 0;
int segmentCounter = 0;
int segmentStepCounterLastPressTime = -1;


int UARTStepCounter = 0;
int UARTCounter = 0;
int UARTStepCounterLastPressTime = -1;


extern UART_HandleTypeDef huart2;
bool isCounting = false;




void decToBinary(int* array, int n) {
    for (int i = 3; i >= 0; i--) {
        int k = n >> i;
        if (k & 1) array[i] = 1;
        else array[i] = 0;
    }
}

void showNumber(int number) {
	 int arr[4] = {0};
	 decToBinary(arr, number);

	 int bcd_A = arr[0];
	 int bcd_B = arr[1];
	 int bcd_C = arr[2];
	 int bcd_D = arr[3];

	 HAL_GPIO_WritePin(GPIOC,GPIO_PIN_0, bcd_D);
	 HAL_GPIO_WritePin(GPIOC,GPIO_PIN_1, bcd_C);
	 HAL_GPIO_WritePin(GPIOC,GPIO_PIN_2, bcd_B);
	 HAL_GPIO_WritePin(GPIOC,GPIO_PIN_3, bcd_A);
}

typedef enum Segment {
	A,B,C,D
} Segment;

void resetAndEnableSegment(Segment segment) {
    HAL_GPIO_WritePin(GPIOD,GPIO_PIN_8 | GPIO_PIN_9 | GPIO_PIN_10 | GPIO_PIN_11, 1);

    switch(segment) {
    case A: HAL_GPIO_WritePin(GPIOD,GPIO_PIN_8, 0); break;
    case B: HAL_GPIO_WritePin(GPIOD,GPIO_PIN_9, 0); break;
    case C:	HAL_GPIO_WritePin(GPIOD,GPIO_PIN_10, 0); break;
    case D:	HAL_GPIO_WritePin(GPIOD,GPIO_PIN_11, 0); break;
    }
}

void turn_on_decimal_point() {
	resetAndEnableSegment(B);
	HAL_GPIO_WritePin(GPIOD,GPIO_PIN_12, 1);
	HAL_Delay(3);
	HAL_GPIO_WritePin(GPIOD,GPIO_PIN_12, 0);
}

void updateSegmentStepCounter() {

    resetAndEnableSegment(A);
	showNumber(segmentStepCounter);
	HAL_Delay(3);
}

void updateSegmentCounter() {

    resetAndEnableSegment(C);
    int tenDigit = segmentCounter/10;
	showNumber(tenDigit);

	HAL_Delay(3);
	int oneDigit = segmentCounter%10;
	resetAndEnableSegment(D);
	showNumber(oneDigit);
}


void updateUARTStepCounter() {

    resetAndEnableSegment(B);
	showNumber(UARTStepCounter);
	HAL_Delay(3);
}




/* USER CODE END 0 */

/* External variables --------------------------------------------------------*/
extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim4;
/* USER CODE BEGIN EV */

/* USER CODE END EV */

/******************************************************************************/
/*           Cortex-M4 Processor Interruption and Exception Handlers          */
/******************************************************************************/
/**
  * @brief This function handles Non maskable interrupt.
  */
void NMI_Handler(void)
{
  /* USER CODE BEGIN NonMaskableInt_IRQn 0 */

  /* USER CODE END NonMaskableInt_IRQn 0 */
  /* USER CODE BEGIN NonMaskableInt_IRQn 1 */
  while (1)
  {
  }
  /* USER CODE END NonMaskableInt_IRQn 1 */
}

/**
  * @brief This function handles Hard fault interrupt.
  */
void HardFault_Handler(void)
{
  /* USER CODE BEGIN HardFault_IRQn 0 */

  /* USER CODE END HardFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_HardFault_IRQn 0 */
    /* USER CODE END W1_HardFault_IRQn 0 */
  }
}

/**
  * @brief This function handles Memory management fault.
  */
void MemManage_Handler(void)
{
  /* USER CODE BEGIN MemoryManagement_IRQn 0 */

  /* USER CODE END MemoryManagement_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_MemoryManagement_IRQn 0 */
    /* USER CODE END W1_MemoryManagement_IRQn 0 */
  }
}

/**
  * @brief This function handles Pre-fetch fault, memory access fault.
  */
void BusFault_Handler(void)
{
  /* USER CODE BEGIN BusFault_IRQn 0 */

  /* USER CODE END BusFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_BusFault_IRQn 0 */
    /* USER CODE END W1_BusFault_IRQn 0 */
  }
}

/**
  * @brief This function handles Undefined instruction or illegal state.
  */
void UsageFault_Handler(void)
{
  /* USER CODE BEGIN UsageFault_IRQn 0 */

  /* USER CODE END UsageFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_UsageFault_IRQn 0 */
    /* USER CODE END W1_UsageFault_IRQn 0 */
  }
}

/**
  * @brief This function handles System service call via SWI instruction.
  */
void SVC_Handler(void)
{
  /* USER CODE BEGIN SVCall_IRQn 0 */

  /* USER CODE END SVCall_IRQn 0 */
  /* USER CODE BEGIN SVCall_IRQn 1 */

  /* USER CODE END SVCall_IRQn 1 */
}

/**
  * @brief This function handles Debug monitor.
  */
void DebugMon_Handler(void)
{
  /* USER CODE BEGIN DebugMonitor_IRQn 0 */

  /* USER CODE END DebugMonitor_IRQn 0 */
  /* USER CODE BEGIN DebugMonitor_IRQn 1 */

  /* USER CODE END DebugMonitor_IRQn 1 */
}

/**
  * @brief This function handles Pendable request for system service.
  */
void PendSV_Handler(void)
{
  /* USER CODE BEGIN PendSV_IRQn 0 */

  /* USER CODE END PendSV_IRQn 0 */
  /* USER CODE BEGIN PendSV_IRQn 1 */

  /* USER CODE END PendSV_IRQn 1 */
}

/**
  * @brief This function handles System tick timer.
  */
void SysTick_Handler(void)
{
  /* USER CODE BEGIN SysTick_IRQn 0 */

  /* USER CODE END SysTick_IRQn 0 */
  HAL_IncTick();
  /* USER CODE BEGIN SysTick_IRQn 1 */

  /* USER CODE END SysTick_IRQn 1 */
}

/******************************************************************************/
/* STM32F3xx Peripheral Interrupt Handlers                                    */
/* Add here the Interrupt Handlers for the used peripherals.                  */
/* For the available peripheral interrupt handler names,                      */
/* please refer to the startup file (startup_stm32f3xx.s).                    */
/******************************************************************************/

/**
  * @brief This function handles EXTI line0 interrupt.
  */
void EXTI0_IRQHandler(void)
{
  /* USER CODE BEGIN EXTI0_IRQn 0 */

  /* USER CODE END EXTI0_IRQn 0 */
  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_0);
  /* USER CODE BEGIN EXTI0_IRQn 1 */

	if(isCounting == true) { return; }

	if (segmentStepCounterLastPressTime == -1) {
		segmentStepCounterLastPressTime = HAL_GetTick();
		return;
	} else {
		if (segmentStepCounterLastPressTime - HAL_GetTick() > 1000) {
			segmentStepCounterLastPressTime = -1;
		} else {
			return;
		}
	}

	if(segmentStepCounter == 9){
		segmentStepCounter = 0;
	} else {
		segmentStepCounter += 1;
	}

  /* USER CODE END EXTI0_IRQn 1 */
}

/**
  * @brief This function handles EXTI line1 interrupt.
  */
void EXTI1_IRQHandler(void)
{
  /* USER CODE BEGIN EXTI1_IRQn 0 */

	if(isCounting == true) { return; }


	if (UARTStepCounterLastPressTime == -1) {
		UARTStepCounterLastPressTime = HAL_GetTick();
		return;
	} else {
		if (UARTStepCounterLastPressTime - HAL_GetTick() > 1000) {
			UARTStepCounterLastPressTime = -1;
		} else {
			return;
		}
	}

	if(UARTStepCounter == 9){
		UARTStepCounter = 0;
	} else {
		UARTStepCounter += 1;
	}

  /* USER CODE END EXTI1_IRQn 0 */
  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_1);
  /* USER CODE BEGIN EXTI1_IRQn 1 */

  /* USER CODE END EXTI1_IRQn 1 */
}

/**
  * @brief This function handles EXTI line2 and Touch Sense controller.
  */
void EXTI2_TSC_IRQHandler(void)
{
  /* USER CODE BEGIN EXTI2_TSC_IRQn 0 */

	if(isCounting == false) { // start counting
		isCounting = true;
	} else { // stop counting
		isCounting = false;
//		segmentCounter = 0;
//		segmentStepCounter = 0;
//		UARTStepCounter = 0;
//		UARTCounter = 0;
	}
	HAL_Delay(3);
  /* USER CODE END EXTI2_TSC_IRQn 0 */
  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_2);
  /* USER CODE BEGIN EXTI2_TSC_IRQn 1 */

  /* USER CODE END EXTI2_TSC_IRQn 1 */
}

/**
  * @brief This function handles TIM2 global interrupt.
  */
void TIM2_IRQHandler(void)
{
  /* USER CODE BEGIN TIM2_IRQn 0 */

	if(isCounting == false) { return; }

	if((segmentCounter + segmentStepCounter) >= 99) {
		segmentCounter = 0;
	} else {
		segmentCounter += segmentStepCounter;
	}

	if((UARTCounter + UARTStepCounter) >= 99) {
		UARTCounter = 0;
	} else {
		UARTCounter += UARTStepCounter;
	}

  /* USER CODE END TIM2_IRQn 0 */
  HAL_TIM_IRQHandler(&htim2);
  /* USER CODE BEGIN TIM2_IRQn 1 */

	unsigned char buffer[8];
	itoa(UARTCounter, buffer, 10);

	strcat(buffer, "\n");

	HAL_UART_Transmit(&huart2, buffer, sizeof(unsigned char) * strlen(buffer), 1000);
  /* USER CODE END TIM2_IRQn 1 */
}

/**
  * @brief This function handles TIM4 global interrupt.
  */
void TIM4_IRQHandler(void)
{
  /* USER CODE BEGIN TIM4_IRQn 0 */

	updateSegmentStepCounter();

	HAL_Delay(3);

	updateSegmentCounter();

	HAL_Delay(3);

	updateUARTStepCounter();

	HAL_Delay(3);

  /* USER CODE END TIM4_IRQn 0 */
  HAL_TIM_IRQHandler(&htim4);
  /* USER CODE BEGIN TIM4_IRQn 1 */

  /* USER CODE END TIM4_IRQn 1 */
}

/* USER CODE BEGIN 1 */

/* USER CODE END 1 */
