#ifdef __USE_CMSIS
#include "LPC17xx.h"
#endif
#include <cr_section_macros.h>
#include "pwm.h"
#include "timer.h"


uint32_t msTicks = 0;

int main(void) {
	uint32_t green = 1000;
	uint32_t blue = 1000;
	uint32_t red = 1000;

	SysTick_Config(SystemCoreClock / 1000);

//PWM1.4 is green, PWM1.5 is blue, and PWM1.6 is red.
//When a color is set to 1000 the LED is off, 0 for on, 500 for 50%.
	PWM_Init(1, 4, 1000);
	PWM_Init(1, 5, 1000);
	PWM_Init(1, 6, 1000);
	PWM_Set(1, 4, 1000);
	PWM_Set(1, 5, 1000);
	PWM_Set(1, 6, 1000);
	PWM_Start(1);
	while (1) {
//Slowly fade the green LED from off to on
		for (green = 1000; green > 1; green--) {
			PWM_Set(1, 4, green);
			msTicks = 1;
			while(msTicks);
//			delayMs(0, 1);
		}
//Slowly fade the blue LED from off to on
		for (blue = 1000; blue > 1; blue--) {
			PWM_Set(1, 5, blue);
			msTicks = 1;
			while(msTicks);
//			delayMs(0, 1);
		}
//Slowly fade the red LED from off to on
		for (red = 1000; red > 1; red--) {
			PWM_Set(1, 6, red);
			msTicks = 1;
			while(msTicks);
//			delayMs(0, 1);
		}
//Slowly fade the green LED from on to off
		for (green = 0; green < 1000; green++) {
			PWM_Set(1, 4, green);
			msTicks = 1;
			while(msTicks);
//			delayMs(0, 1);
		}
//Slowly fade the blue LED from on to off
		for (blue = 0; blue < 1000; blue++) {
			PWM_Set(1, 5, blue);
			msTicks = 1;
			while(msTicks);
//			delayMs(0, 1);
		}
//Slowly fade the red LED from on to off
		for (red = 0; red < 1000; red++) {
			PWM_Set(1, 6, red);
			msTicks = 1;
			while(msTicks);
//			delayMs(0, 1);
		}
	}
}

void SysTick_Handler(void) {

	if(msTicks){
		msTicks--;
	}
}

///*****************************************************************************
// *
// *   Copyright(C) 2011, Embedded Artists AB
// *   All rights reserved.
// *
// ******************************************************************************
// * Software that is described herein is for illustrative purposes only
// * which provides customers with programming information regarding the
// * products. This software is supplied "AS IS" without any warranties.
// * Embedded Artists AB assumes no responsibility or liability for the
// * use of the software, conveys no license or title under any patent,
// * copyright, or mask work right to the product. Embedded Artists AB
// * reserves the right to make changes in the software without
// * notification. Embedded Artists AB also make no representation or
// * warranty that such application will be suitable for the specified
// * use without further testing or modification.
// *****************************************************************************/
//
///******************************************************************************
// * Includes
// *****************************************************************************/
//
//#include "lpc17xx_pinsel.h"
//#include "lpc17xx_gpio.h"
//#include "lpc17xx_ssp.h"
//#include "lpc17xx_uart.h"
//#include "lpc17xx_timer.h"
//#include "lpc17xx_can.h"
//#include <string.h>
//#include <stdio.h>
//
//#include "board.h"
//
//#include "canpt.h"
//
//#include "AndroidAccessoryHost.h"
//
///******************************************************************************
// * Typdefs and defines
// *****************************************************************************/
//
//#define DISCOVER_TIME_MS (5000)
//
///******************************************************************************
// * Local variables
// *****************************************************************************/
//
//static uint32_t msTicks = 0;
//static uint32_t lastDiscover = 0;
//
//static uint32_t msTicksL = 0;
//
///******************************************************************************
// * Local functions
// *****************************************************************************/
//
///******************************************************************************
// * Public functions
// *****************************************************************************/
//
//
//uint32_t getMsTicks(void)
//{
//  return msTicks;
//}
//
//void SysTick_Handler(void) {
//  msTicks++;
//  msTicksL++;
//
//}
//
//int main (void)
//{
//
//  SysTick_Config(SystemCoreClock / 1000);
//
//  canpt_init();
//
//  while(1) {
//
//    if (lastDiscover + DISCOVER_TIME_MS < getMsTicks()) {
//      lastDiscover = getMsTicks();
////      canpt_discover();
////      sendMessage(CANPT_MSG_CMN_ID_DISC, 0);
//
////      sendMessage(LPC_CAN2, CANPT_MSG_CMN_ID_DISC, 0);
//    }
//
//    canpt_task();
//
//    if (1000 < msTicksL) {
//    	msTicksL = 0;
//
//    }
//
//  }
//
//}
//
//
//void check_failed(uint8_t *file, uint32_t line)
//{
//  /* User can add his own implementation to report the file name and line number,
//	 ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
//
//  /* Infinite loop */
//  while(1);
//}
//
