/*
 * rccconfig.h
 *
 *  Created on: Mar 13, 2025
 *      Author: pbu05
 */

#ifndef RCCCONFIG_H_
#define RCCCONFIG_H_

#include "../../reg_adc/cmsis/Device/ST/STM32F4xx/Include/stm32f446xx.h"

/*
 * system clock source: HSE PLL
 * SYSCLK 180MHz
 * HCLK   180MHz
 * AHB   prescaler 1
 * APB1  prescaler 4
 * APB2  prescaler 2
 * HSE   80MHz
 * pll_m  4
 * pll_n  180
 * pll_p  2
 * vdd    3.3v
 * main regulator output voltage scale 1 mode
 * flash latency = 5ws
 */


void sysclkConfig(void)
{
	RCC->CR |= 1<<16;
	while(!(RCC->CR & 1<<17));

	RCC->APB1ENR |= 1<<28;
	RCC->CR |= 3<<14;

	FLASH->ACR |= 7<<8 | 5<<0;;

	RCC->CFGR |= 7<<4;
	RCC->CFGR |= 5<<10;
	RCC->CFGR |= 4<<13;

	RCC->PLLCFGR |= 4<<0 | 180<<6 | 1<<16;

	RCC->CR |= 1<<24;
	while(!(RCC->CR & 1<<25));

	RCC->CFGR |= 2<<0;
	while(!(RCC->CFGR & 2<<2));
}

#endif /* RCCCONFIG_H_ */
