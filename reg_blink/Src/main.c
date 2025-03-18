/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Auto-generated by STM32CubeIDE
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2025 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */

#include <stdint.h>
#include "main.h"


void SystemClockConfig(void);
void gpioConfig(void);
void delay(uint32_t time);

int main(void)
{
	SystemClockConfig();
	gpioConfig();


	while(1)
	{
		GPIOA->BSRR |= 1<<5;
		delay(100000);
		GPIOA->BSRR |= (1<<5)<<16;
		delay(100000);
	}
}

void SystemClockConfig(void)
{
	/*
	 * enable hse for pll and wait flag(hse ready)
	 */
	RCC->CR |= 1<<16;
	while (!(RCC->CR & 1<<17));

	/*
	 * set the power enable clock and voltage regulator
	 */
	RCC->APB1ENR |= 1<<28;
	PWR->CR |= PWR_CR_VOS;

	/*
	 * flssh related
	 */
	FLASH->ACR |= 7<<8 | 5<<0;

	/*
	 * prescalars
	 */
	RCC->CFGR |= 7<<4;  //ahb divided by 1
	RCC->CFGR |= 5<<10; //apb1 divided by 4
	RCC->CFGR |= 4<<13; //apb2 divided by 2

	/*
	 * config pll
	 */
	RCC->PLLCFGR |= 4<<0 | 180<<6 | 1<<16 | 1<<22;

	/*
	 * enable pll
	 */
	RCC->CR |= 1<<24;
	while(!(RCC->CR & 1<<25));

	/*
	 * set the clock source
	 */
	RCC->CFGR |= 2<<0;
	while(!(RCC->CFGR & 2<<2));
}

void gpioConfig(void)
{
	/*
	 * first enable gpio clock
	 */

	RCC->AHB1ENR |= 5<<0;
	GPIOA->MODER |= 1<<10;
	GPIOA->OSPEEDR |= 0<<10;
	GPIOA->PUPDR |= 0<<10;
}


void delay(uint32_t time)
{
	while(time--);
}
