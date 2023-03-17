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
#include "stdlib.h"
#include "stdio.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN TD */

typedef enum {
	true, false
} bool;

#define MAXSIZE 100

float temp_stack[MAXSIZE];
int temp_top = -1;

float light_stack[MAXSIZE];
int light_top = -1;

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
//
//float peek(float stack[MAXSIZE], int top) {
//   return stack[top];
//}

//float pop(float stack[MAXSIZE], int* top) {
//   float data;
//
//   if(isempty(*top) == false) {
//      data = stack[*top];
//      *top = *top - 1;
//      return data;
//   } else {
//	   return -1;
////      printf("Could not retrieve data, Stack is empty.\n");
//   }
//}

void push(float stack[MAXSIZE], int* top, float data) {

   if(isfull(*top) == false) {
      *top = *top + 1;
      stack[*top] = data;
   }
}

int avg_stack(float stack[MAXSIZE], int top) {
	float sum = 0;
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

//int raw_value_temp[20];
//int raw_value_light[20];

int tempreture_value = 0;
int light_value = 0;
bool is_on_alert_mode = false;
bool buzzer_enabled = true;

// for buzzer
extern TIM_HandleTypeDef htim4;
TIM_HandleTypeDef *buzzerPwmTimer = &htim4;
int buzzerPwmChannel = TIM_CHANNEL_1;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/* External variables --------------------------------------------------------*/
extern ADC_HandleTypeDef hadc1;
extern ADC_HandleTypeDef hadc2;
extern TIM_HandleTypeDef htim2;
/* USER CODE BEGIN EV */

void buzzerChangeTone(uint16_t freq, uint16_t volume) {

	if (freq == 0 || freq > 20000) {
		__HAL_TIM_SET_COMPARE(buzzerPwmTimer, buzzerPwmChannel, 0);
	} else {
		const uint32_t internalClockFreq = HAL_RCC_GetSysClockFreq();
		const uint32_t prescaler = 1 + internalClockFreq / freq / 60000;
		const uint32_t timerClock = internalClockFreq / prescaler;
		const uint32_t periodCycles = timerClock / freq;
		const uint32_t pulseWidth = volume * periodCycles / 1000 / 2;

		buzzerPwmTimer->Instance->PSC = prescaler - 1;
		buzzerPwmTimer->Instance->ARR = periodCycles - 1;
		buzzerPwmTimer->Instance->EGR = TIM_EGR_UG;

		__HAL_TIM_SET_COMPARE(buzzerPwmTimer, buzzerPwmChannel, pulseWidth);
	}
}

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

	 int bcd_A = arr[3];
	 int bcd_B = arr[2];
	 int bcd_C = arr[1];
	 int bcd_D = arr[0];

	 HAL_GPIO_WritePin(GPIOE,GPIO_PIN_11, bcd_D);
	 HAL_GPIO_WritePin(GPIOE,GPIO_PIN_12, bcd_C);
	 HAL_GPIO_WritePin(GPIOE,GPIO_PIN_13, bcd_B);
	 HAL_GPIO_WritePin(GPIOE,GPIO_PIN_14, bcd_A);
}

typedef enum Segment {
	A,B,C,D,None
} Segment;

void resetAndEnableSegment(Segment segment) {
    HAL_GPIO_WritePin(GPIOE,GPIO_PIN_7 | GPIO_PIN_8 | GPIO_PIN_9 | GPIO_PIN_10 , 1);

    switch(segment) {
    case A: HAL_GPIO_WritePin(GPIOE,GPIO_PIN_7, 0); break;
    case B: HAL_GPIO_WritePin(GPIOE,GPIO_PIN_8, 0); break;
    case C:	HAL_GPIO_WritePin(GPIOE,GPIO_PIN_9, 0); break;
    case D:	HAL_GPIO_WritePin(GPIOE,GPIO_PIN_10, 0); break;
    case None: break;
    }
}

//void toggleSegment(Segment segment) {
//    switch(segment) {
//    case A: HAL_GPIO_TogglePin(GPIOE,GPIO_PIN_7); break;
//    case B: HAL_GPIO_TogglePin(GPIOE,GPIO_PIN_8); break;
//    case C:	HAL_GPIO_TogglePin(GPIOE,GPIO_PIN_9); break;
//    case D:	HAL_GPIO_TogglePin(GPIOE,GPIO_PIN_10); break;
//    case None: break;
//    }
//}

void show_light_on_7_segment() {
	int tens = light_value/10;
	resetAndEnableSegment(C);
	showNumber(tens);
	HAL_Delay(3);
	int ones = light_value%10;
	resetAndEnableSegment(D);
	showNumber(ones);
}

void show_tempreture_on_7_segment() {
	int tens = tempreture_value/10;
	resetAndEnableSegment(A);
	showNumber(tens);

	HAL_Delay(3);

	int ones = tempreture_value%10;
	resetAndEnableSegment(B);
	showNumber(ones);

	HAL_Delay(3);
}

int alert_time = 0;
bool is_alert_seg_on = false;
void evaluate_alert_state() {
	if (is_on_alert_mode == true) {
		int duration = HAL_GetTick() - alert_time;

		if (duration >= 500) {
			if (is_alert_seg_on == true) {
				is_alert_seg_on = false;
			} else {
				is_alert_seg_on = true;
			}
			alert_time = HAL_GetTick();
		}

		if (is_alert_seg_on == false) {

//			resetAndEnableSegment(None);

//			HAL_Delay(3);

			resetAndEnableSegment(None);

			HAL_Delay(3);
		} else {
			show_tempreture_on_7_segment();
		}
	} else {
		show_tempreture_on_7_segment();
	}

}

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
  * @brief This function handles EXTI line2 and Touch Sense controller.
  */
void EXTI2_TSC_IRQHandler(void)
{
  /* USER CODE BEGIN EXTI2_TSC_IRQn 0 */
	if(buzzer_enabled == true) {
		buzzer_enabled = false;
	} else {
		buzzer_enabled = true;
	}
	HAL_Delay(3);
  /* USER CODE END EXTI2_TSC_IRQn 0 */
  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_2);
  /* USER CODE BEGIN EXTI2_TSC_IRQn 1 */

  /* USER CODE END EXTI2_TSC_IRQn 1 */
}

/**
  * @brief This function handles ADC1 and ADC2 interrupts.
  */
void ADC1_2_IRQHandler(void)
{
  /* USER CODE BEGIN ADC1_2_IRQn 0 */

  /* USER CODE END ADC1_2_IRQn 0 */
  HAL_ADC_IRQHandler(&hadc1);
  HAL_ADC_IRQHandler(&hadc2);
  /* USER CODE BEGIN ADC1_2_IRQn 1 */

  int raw_value = HAL_ADC_GetValue(&hadc1);
  const float Voltage_mv = raw_value * 3300 / 4095;
  const float Temperature_c = Voltage_mv / 10;

  if(isfull(temp_top) == false) {
	  push(temp_stack, &temp_top, Temperature_c);
  }


  int raw_value_light_ = HAL_ADC_GetValue(&hadc2);
  const float x1 = raw_value_light_ - 5;
  const float x2 = 3234 - 5;
  const float light_value_c = x1 * 100 / x2;

  if (isfull(light_top) == false) {
	  push(light_stack, &light_top, light_value_c);
  }

//  extern UART_HandleTypeDef huart2;
//  unsigned char buffer[30] = "";
//
//  if (raw_value_temp < raw_value){
//	  raw_value_temp = raw_value;
//  }
//
////  	  strcat(buffer, "t: ");
////  	  itoa(raw_value_temp, buffer, 10);
////  	  strcat(buffer, "\n");
//
////  	  strcat(buffer, "l: ");
//  	  itoa(raw_value_light, buffer, 10);
//  	  strcat(buffer, "\n");
//
//  	  HAL_UART_Transmit(&huart2, buffer, sizeof(unsigned char) * strlen(buffer), 1000);
//  	  HAL_Delay(3);

  HAL_ADC_Start_IT(&hadc1);
  HAL_ADC_Start_IT(&hadc2);
  /* USER CODE END ADC1_2_IRQn 1 */
}

/**
  * @brief This function handles TIM2 global interrupt.
  */
void TIM2_IRQHandler(void)
{
  /* USER CODE BEGIN TIM2_IRQn 0 */
	if(isfull(temp_top) == true) {
		tempreture_value = avg_stack(temp_stack, temp_top);
		clear_stack(&temp_top);
	}
	if(isfull(light_top) == true) {
		light_value = avg_stack(light_stack, light_top);
		clear_stack(&light_top);
	}
	if (tempreture_value >= 30) {
		is_on_alert_mode = true;
	} else {
		is_on_alert_mode = false;
		buzzer_enabled = true;
	}

	if (buzzer_enabled == true && is_on_alert_mode == true) {
		buzzerChangeTone(2000, 2);
	} else {
		buzzerChangeTone(0, 0);
	}

	evaluate_alert_state();
	HAL_Delay(3);
	show_light_on_7_segment();
	HAL_Delay(3);

  /* USER CODE END TIM2_IRQn 0 */
  HAL_TIM_IRQHandler(&htim2);
  /* USER CODE BEGIN TIM2_IRQn 1 */
  // this timer handle showing temp on 7seg

  /* USER CODE END TIM2_IRQn 1 */
}

/* USER CODE BEGIN 1 */

/* USER CODE END 1 */
