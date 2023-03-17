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
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "LiquidCrystal.h"
#include "stdlib.h"
#include "string.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN TD */


#define MAXSIZE 1000

int volume_stack[MAXSIZE];
int volume_top = -1;

void clear_stack(int* top) {
	*top = -1;
}

bool isempty(int top) {

   if(top == -1)
      return true;
   else
      return false;
}

bool isfull(int top) {

   if(top == MAXSIZE)
      return true;
   else
      return false;
}

void push(int stack[MAXSIZE], int* top, float data) {

   if(isfull(*top) == false) {
      *top = *top + 1;
      stack[*top] = data;
   }
}

int avg_stack(int stack[MAXSIZE], int top) {
	int sum = 0;
	for (size_t i = 0 ; i <= top ; i ++){
		sum += stack[i];
	}
	return (int)(sum/(top + 1));
}
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
int volume_number = 0;
int last_pressed_time = 0;
/* USER CODE END 0 */

/* External variables --------------------------------------------------------*/
extern ADC_HandleTypeDef hadc4;
extern TIM_HandleTypeDef htim2;
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

  int duration = HAL_GetTick() - last_pressed_time;
  if (duration > 1000) {
	  last_pressed_time = 0;
  } else {
	  last_pressed_time = HAL_GetTick();
	  return;
  }

  HAL_GPIO_TogglePin(GPIOE, GPIO_PIN_9);

  if (is_on_password_page() == true && is_password_choosed() == false) {
	  apply_volume();
	  display_page();
  } else if (is_password_choosed() == true) {
	  HAL_GPIO_TogglePin(GPIOE, GPIO_PIN_10);
	  validate_password();
  } else {
	  clear();
	  change_page();
	  display_page();
  }

  HAL_Delay(1000);
  /* USER CODE END EXTI0_IRQn 1 */
}

/**
  * @brief This function handles TIM2 global interrupt.
  */
void TIM2_IRQHandler(void)
{
  /* USER CODE BEGIN TIM2_IRQn 0 */


  /* USER CODE END TIM2_IRQn 0 */
  HAL_TIM_IRQHandler(&htim2);
  /* USER CODE BEGIN TIM2_IRQn 1 */


  //
//  	  if (volume_number != adc_num) {
//  		  char snum[5] = "";
//  		  clear();
//  		  itoa(volume_number, snum, 10);
//  		  setCursor(0, 1);
//  		  print(snum);
//  //		  strcat(snum, "\n");
//
//  		  extern UART_HandleTypeDef huart2;
//  		  HAL_UART_Transmit(&huart2, snum, sizeof(snum), 1000);
//  		  volume_number = adc_num;
//  	  }
  /* USER CODE END TIM2_IRQn 1 */
}

/**
  * @brief This function handles ADC4 interrupt.
  */
void ADC4_IRQHandler(void)
{
  /* USER CODE BEGIN ADC4_IRQn 0 */

  /* USER CODE END ADC4_IRQn 0 */
  HAL_ADC_IRQHandler(&hadc4);
  /* USER CODE BEGIN ADC4_IRQn 1 */

  int adc_num = HAL_ADC_GetValue(&hadc4) * 100 / 4095 / 10;

  if (adc_num != volume_number) {
	  volume_number = adc_num;
	  set_volume(volume_number * 10);
	  display_page();
	  buzzerChangeTone(1000, 50);
	  HAL_Delay(200);
	  buzzerChangeTone(0, 0);
//
//	  char num[3] = "";
//	  itoa(volume_number * 10, num, 10);
//	  clear();
//	  setCursor(0, 1);
//	  print(num);
//	  extern UART_HandleTypeDef huart2;
	//  HAL_UART_Transmit(&huart2, num, sizeof(num), 1000);
  }

//  if(isfull(volume_top) == false) {
//	  push(volume_stack, &volume_top, adc_num);
//  }
//  else if (isfull(volume_top) == true) {
//  	  int avg = avg_stack(volume_stack, volume_top);
//  	  clear_stack(&volume_top);

//  	  if (volume_number != avg) {
//  		  char snum[3] = "";
//  		  clear();
//  		  itoa(avg, snum, 10);
//  		  setCursor(0, 1);
//  		  print(snum);
//  		  volume_number = avg;
//  		  extern UART_HandleTypeDef huart2;
//  		  HAL_UART_Transmit(&huart2, snum, sizeof(snum), 1000);

//  	  }
//    }


  HAL_ADC_Start_IT(&hadc4);
  /* USER CODE END ADC4_IRQn 1 */
}

/* USER CODE BEGIN 1 */

/* USER CODE END 1 */
