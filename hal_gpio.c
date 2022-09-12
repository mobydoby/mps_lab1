#ifndef __HAL_GPIO_H
#define __HAL_GPIO_H

#include "init.h"

void hal_gpio(){

	GPIO_InitTypeDef led_init;
	led_init.Mode = GPIO_MODE_OUTPUT_PP;
//	led_init.Pull = GPIO_PULLDOWN;
	led_init.Pin = GPIO_PIN_13 | GPIO_PIN_5;
	__HAL_RCC_GPIOJ_CLK_ENABLE();
	HAL_GPIO_Init(GPIOJ, &led_init);
	led_init.Pin = GPIO_PIN_12;
	__HAL_RCC_GPIOA_CLK_ENABLE();
	HAL_GPIO_Init(GPIOA, &led_init);
	led_init.Pin = GPIO_PIN_4;
	__HAL_RCC_GPIOD_CLK_ENABLE();
	HAL_GPIO_Init(GPIOD, &led_init);

	GPIO_InitTypeDef header_pin_init;
	header_pin_init.Mode = GPIO_MODE_INPUT;
	header_pin_init.Pull = GPIO_PULLUP;
	header_pin_init.Pin = GPIO_PIN_6 | GPIO_PIN_7;

	//initialize D0 and D1
	__HAL_RCC_GPIOC_CLK_ENABLE();
	HAL_GPIO_Init(GPIOC, &header_pin_init);

	//initialize D3
	header_pin_init.Pin = GPIO_PIN_6;
	__HAL_RCC_GPIOF_CLK_ENABLE();
	HAL_GPIO_Init(GPIOF, &header_pin_init);

	//initialize D2
	header_pin_init.Pin = GPIO_PIN_1;
	HAL_GPIO_Init(GPIOJ, &header_pin_init);


	HAL_GPIO_WritePin(GPIOJ, GPIO_PIN_13, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOJ, GPIO_PIN_5, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_4, GPIO_PIN_SET);
	while(1){
		//read on all header pins
		GPIO_PinState D0_state = HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_6);//d0
		GPIO_PinState D1_state = HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_7);//d1
		GPIO_PinState D3_state = HAL_GPIO_ReadPin(GPIOF, GPIO_PIN_6);//d3
		GPIO_PinState D2_state = HAL_GPIO_ReadPin(GPIOJ, GPIO_PIN_1);//d2

		//LD1 = PJ13
		//LD2 = PJ5
		//LD3 = PA12
		//LD4 = PD4
		if (D0_state == GPIO_PIN_SET) HAL_GPIO_WritePin(GPIOJ, GPIO_PIN_13, GPIO_PIN_SET);
		else HAL_GPIO_WritePin(GPIOJ, GPIO_PIN_13, GPIO_PIN_RESET);
		if (D1_state == GPIO_PIN_SET) HAL_GPIO_WritePin(GPIOJ, GPIO_PIN_5, GPIO_PIN_SET);
		else HAL_GPIO_WritePin(GPIOJ, GPIO_PIN_5, GPIO_PIN_RESET);
		if (D2_state == GPIO_PIN_SET) HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, GPIO_PIN_SET);
		else HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, GPIO_PIN_RESET);
		if (D3_state == GPIO_PIN_SET) HAL_GPIO_WritePin(GPIOD, GPIO_PIN_4, GPIO_PIN_RESET);
		else HAL_GPIO_WritePin(GPIOD, GPIO_PIN_4, GPIO_PIN_SET);
	}
}
#endif
