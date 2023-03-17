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
#include "string.h"
#include "stdlib.h"
#include "stdio.h"
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


typedef struct {
    uint32_t frequency;
    int duration;
} Tone;

typedef enum {
	play, pause
} State;

char uart_input[10];
int current_tone_id = 0;
State state = pause;
extern TIM_HandleTypeDef htim1;
const TIM_HandleTypeDef *buzzerPwmTimer = &htim1;
int buzzerPwmChannel = TIM_CHANNEL_1;
int current_volume = 0;
const int tempo = 120;
const int wholenote = (60000 * 4) / tempo;
void buzzerChangeTone(uint16_t freq, uint16_t volume);
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

#define NOTE_B0  31
#define NOTE_C1  33
#define NOTE_CS1 35
#define NOTE_D1  37
#define NOTE_DS1 39
#define NOTE_E1  41
#define NOTE_F1  44
#define NOTE_FS1 46
#define NOTE_G1  49
#define NOTE_GS1 52
#define NOTE_A1  55
#define NOTE_AS1 58
#define NOTE_B1  62
#define NOTE_C2  65
#define NOTE_CS2 69
#define NOTE_D2  73
#define NOTE_DS2 78
#define NOTE_E2  82
#define NOTE_F2  87
#define NOTE_FS2 93
#define NOTE_G2  98
#define NOTE_GS2 104
#define NOTE_A2  110
#define NOTE_AS2 117
#define NOTE_B2  123
#define NOTE_C3  131
#define NOTE_CS3 139
#define NOTE_D3  147
#define NOTE_DS3 156
#define NOTE_E3  165
#define NOTE_F3  175
#define NOTE_FS3 185
#define NOTE_G3  196
#define NOTE_GS3 208
#define NOTE_A3  220
#define NOTE_AS3 233
#define NOTE_B3  247
#define NOTE_C4  262
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784
#define NOTE_GS5 831
#define NOTE_A5  880
#define NOTE_AS5 932
#define NOTE_B5  988
#define NOTE_C6  1047
#define NOTE_CS6 1109
#define NOTE_D6  1175
#define NOTE_DS6 1245
#define NOTE_E6  1319
#define NOTE_F6  1397
#define NOTE_FS6 1480
#define NOTE_G6  1568
#define NOTE_GS6 1661
#define NOTE_A6  1760
#define NOTE_AS6 1865
#define NOTE_B6  1976
#define NOTE_C7  2093
#define NOTE_CS7 2217
#define NOTE_D7  2349
#define NOTE_DS7 2489
#define NOTE_E7  2637
#define NOTE_F7  2794
#define NOTE_FS7 2960
#define NOTE_G7  3136
#define NOTE_GS7 3322
#define NOTE_A7  3520
#define NOTE_AS7 3729
#define NOTE_B7  3951
#define NOTE_C8  4186
#define NOTE_CS8 4435
#define NOTE_D8  4699
#define NOTE_DS8 4978
#define REST      0


Tone imperialmarch[] = {

    {NOTE_A4,-4},
    {NOTE_A4,-4},
    {NOTE_A4,16},
    {NOTE_A4,16},
    {NOTE_A4,16},
    {NOTE_A4,16},
    {NOTE_F4,8},
    {REST,8},
    {NOTE_A4,-4},
    {NOTE_A4,-4},
    {NOTE_A4,16},
    {NOTE_A4,16},
    {NOTE_A4,16},
    {NOTE_A4,16},
    {NOTE_F4,8},
    {REST,8},
    {NOTE_A4,4},
    {NOTE_A4,4},
    {NOTE_A4,4},
	{NOTE_F4,-8},
    {NOTE_C5,16},

    {NOTE_A4,4},
    {NOTE_F4,-8},
    {NOTE_C5,16},
    {NOTE_A4,2},//4
    {NOTE_E5,4},
    {NOTE_E5,4},
    {NOTE_E5,4},
    {NOTE_F5,-8},
    {NOTE_C5,16},
    {NOTE_A4,4},
    {NOTE_F4,-8},
    {NOTE_C5,16},
    {NOTE_A4,2},

    {NOTE_A5,4},
    {NOTE_A4,-8},
    {NOTE_A4,16},
    {NOTE_A5,4},
    {NOTE_GS5,-8},
    {NOTE_G5,16}, //7
    {NOTE_DS5,16},
    {NOTE_D5,16},
    {NOTE_DS5,8},
    {REST,8},
    {NOTE_A4,8},
    {NOTE_DS5,4},
    {NOTE_D5,-8},
    {NOTE_CS5,16},

    {NOTE_C5,16},
    {NOTE_B4,16},
    {NOTE_C5,16},
    {REST,8},
    {NOTE_F4,8},
    {NOTE_GS4,4},
    {NOTE_F4,-8},
    {NOTE_A4,-16},//9
    {NOTE_C5,4},
    {NOTE_A4,-8},
    {NOTE_C5,16},
    {NOTE_E5,2},

    {NOTE_A5,4},
    {NOTE_A4,-8},
    {NOTE_A4,16},
    {NOTE_A5,4},
    {NOTE_GS5,-8},
    {NOTE_G5,16}, //7
    {NOTE_DS5,16},
    {NOTE_D5,16},
    {NOTE_DS5,8},
    {REST,8},
    {NOTE_A4,8},
    {NOTE_DS5,4},
    {NOTE_D5,-8},
    {NOTE_CS5,16},

    {NOTE_C5,16},
    {NOTE_B4,16},
    {NOTE_C5,16},
    {REST,8},
    {NOTE_F4,8},
    {NOTE_GS4,4},
    {NOTE_F4,-8},
    {NOTE_A4,-16},//9
    {NOTE_A4,4},
    {NOTE_F4,-8},
    {NOTE_C5,16},
    {NOTE_A4,2}

};



Tone cantinaband[] = {

    // Cantina BAnd - Star wars
    // Score available at https://musescore.com/user/6795541/scores/1606876
    {NOTE_B4,-4},
    {NOTE_E5,-4},
    {NOTE_B4,-4},
    {NOTE_E5,-4},
    {NOTE_B4,8},
    {NOTE_E5,-4},
    {NOTE_B4,8},
    {REST,8},
    {NOTE_AS4,8},
    {NOTE_B4,8},
    {NOTE_B4,8},
    {NOTE_AS4,8},
    {NOTE_B4,8},
    {NOTE_A4,8},
    {REST,8},
    {NOTE_GS4,8},
    {NOTE_A4,8},
    {NOTE_G4,8},
    {NOTE_G4,4},
    {NOTE_E4,-2},
    {NOTE_B4,-4},
    {NOTE_E5,-4},
    {NOTE_B4,-4},
    {NOTE_E5,-4},
    {NOTE_B4,8},
    {NOTE_E5,-4},
    {NOTE_B4,8},
    {REST,8},
    {NOTE_AS4,8},
    {NOTE_B4,8},
    {NOTE_A4,-4},
    {NOTE_A4,-4},
    {NOTE_GS4,8},
    {NOTE_A4,-4},
    {NOTE_D5,8},
    {NOTE_C5,-4},
    {NOTE_B4,-4},
    {NOTE_A4,-4},
    {NOTE_B4,-4},
    {NOTE_E5,-4},
    {NOTE_B4,-4},
    {NOTE_E5,-4},
    {NOTE_B4,8},
    {NOTE_E5,-4},
    {NOTE_B4,8},
    {REST,8},
    {NOTE_AS4,8},
    {NOTE_B4,8},
    {NOTE_D5,4},
    {NOTE_D5,-4},
    {NOTE_B4,8},
    {NOTE_A4,-4},
    {NOTE_G4,-4},
    {NOTE_E4,-2},
    {NOTE_E4, 2},
    {NOTE_G4,2},
    {NOTE_B4, 2},
    {NOTE_D5,2},
    {NOTE_F5,-4},
    {NOTE_E5,-4},
    {NOTE_AS4,8},
    {NOTE_AS4,8},
    {NOTE_B4,4},
    {NOTE_G4,4},
};

// iterate over the notes of the melody.
// Remember, the array is twice the number of notes (notes + durations)
void setupTonessss() {
//	Tone currentToneNumber[] = {};
//	if (current_tone_id == 0) {
//		memcpy(currentToneNumber, cantinaband, sizeof(cantinaband));
//	} else if (current_tone_id == 1) {
//		memcpy(currentToneNumber, imperialmarch, sizeof(imperialmarch));
//	} else if (current_tone_id == 2) {
//
//	} else {
//		memcpy(currentToneNumber, imperialmarch, sizeof(imperialmarch));
//	}

	int notes_count = sizeof(imperialmarch)/sizeof(imperialmarch[0]);
	for(int thisNote = 0; thisNote < notes_count; thisNote++) {
		if (state == pause) {
			return;
		}
		int divider = 0, noteDuration = 0;
		divider = imperialmarch[thisNote].duration;

	    if (divider > 0) {
	      // regular note, just proceed
	      noteDuration = (wholenote) / divider;
	    } else if (divider < 0) {
	      // dotted notes are represented with negative durations!!
	      if (divider < 0) {
		      noteDuration = (wholenote) / (-divider);
	      } else {
		      noteDuration = (wholenote) / divider;
	      }
	      noteDuration *= 1.5; // increases the duration in half for dotted notes
	    }

	    buzzerChangeTone(imperialmarch[thisNote].frequency, 50);
	    HAL_Delay(noteDuration);

	    buzzerChangeTone(0,5);
	}
}

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
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/* External variables --------------------------------------------------------*/
extern TIM_HandleTypeDef htim2;
extern UART_HandleTypeDef huart2;
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
  * @brief This function handles TIM2 global interrupt.
  */
void TIM2_IRQHandler(void)
{
  /* USER CODE BEGIN TIM2_IRQn 0 */
	if (state == pause) { return; }
	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_8, 1);
  /* USER CODE END TIM2_IRQn 0 */
  HAL_TIM_IRQHandler(&htim2);
  /* USER CODE BEGIN TIM2_IRQn 1 */
  setupTonessss();
  HAL_GPIO_WritePin(GPIOE, GPIO_PIN_8, 0);
  /* USER CODE END TIM2_IRQn 1 */
}

/**
  * @brief This function handles USART2 global interrupt / USART2 wake-up interrupt through EXTI line 26.
  */
void USART2_IRQHandler(void)
{
  /* USER CODE BEGIN USART2_IRQn 0 */

	  const int uart_input_size = sizeof(uart_input);

	  printf("%c", uart_input[0]);
	  if (uart_input[0] == 'v') {
		  sscanf(uart_input, "v%d", &current_volume);
	  } else if (uart_input[0] == 's') { // stop
		  state = pause;
		  HAL_GPIO_WritePin(GPIOE, GPIO_PIN_9, 0);
	  } else if (uart_input[0] == 'p') { // play
		  state = play;
		  HAL_GPIO_WritePin(GPIOE, GPIO_PIN_9, 1);
	//	  HAL_GPIO_WritePin(GPIOE, GPIO_PIN_8, 1);

	//	  HAL_GPIO_WritePin(GPIOE, GPIO_PIN_8, 0);
	//	  HAL_Delay(1000);
	  } else if (uart_input[0] == 't') {
		  sscanf(uart_input, "t%d", &current_tone_id);
	  }

//	  HAL_Delay(300);

//	  memset(uart_input, 0, sizeof uart_input);


  /* USER CODE END USART2_IRQn 0 */
  HAL_UART_IRQHandler(&huart2);
  /* USER CODE BEGIN USART2_IRQn 1 */


  HAL_UART_Receive_IT(&huart2, uart_input, uart_input_size);

  /* USER CODE END USART2_IRQn 1 */
}

/* USER CODE BEGIN 1 */

/* USER CODE END 1 */
