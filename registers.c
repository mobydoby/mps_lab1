#ifndef __REGISTERS_H
#define __REGISTERS_H

#include "init.h"


//------------------------------------------------------------------------------------
//Extra thing to consider...
//------------------------------------------------------------------------------------
void setup_reg() {
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOJEN; // or through registers
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN;
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOFEN;
	//// Below two lines are example on how to access a register by knowing it's memory address
	//volatile uint32_t * RCC_AHB1_CLOCK_ENABLE = (uint32_t*) 0x40023830U; // Enable clock for peripheral bus on GPIO Port J
	//*RCC_AHB1_CLOCK_ENABLE |= 512U; // Bitmask for RCC AHB1 initialization: 0x00000200U or 512U in decimal
	//Mode registers
	//port J - j1 input, j5,output, j13 output
	GPIOJ->MODER |= 67109888U;
	GPIOJ->OTYPER |= 0U;
	GPIOJ->PUPDR |= 1U;

	GPIOA->MODER |= 16777216U;


	//port c - c6 c7 inputs
	GPIOC->MODER &= 0U; //BGPIO C Pin 6 and 7 initialization (set it to input mode):1024U in decimal
	GPIOC->OTYPER &= 63U;
	GPIOC->PUPDR |= 20480U;

	//port d - d5 output
	GPIOD->MODER |= 256U;
	GPIOD->OTYPER |= 31U;

	//port F - f6 input
	GPIOF->MODER &= 0U;//f6
	GPIOF->OTYPER &= 63U;
	GPIOF->PUPDR |= 4096U;

//	GPIOD->BSRR = (uint32_t)GPIO_PIN_4 << 16;
//	GPIOA->BSRR = (uint32_t)GPIO_PIN_12 << 16;
//	GPIOJ->BSRR = (uint32_t)GPIO_PIN_5 << 16;
//	GPIOD->BSRR = ((uint16_t)GPIO_PIN_4);

}

void registers(){
	setup_reg();

	GPIOD->BSRR = (uint32_t)GPIO_PIN_4;
	GPIOA->BSRR = (uint32_t)GPIO_PIN_12 << 16;
	GPIOJ->BSRR = (uint32_t)GPIO_PIN_5 << 16;
	GPIOJ->BSRR = (uint32_t)GPIO_PIN_13 << 16;
    while(1)
    {

    	//
    	if((GPIOC->IDR & 0x80U)) {
    		printf("%d",0x80U);
    		printf("\r\n\n\n\n");


    		GPIOJ->BSRR = (uint16_t)GPIO_PIN_13; // Turn on Green LED (LED1)

    	}else{
    		GPIOJ->BSRR  = (uint32_t)GPIO_PIN_13 << 16;
    		printf("off\n\r");
    	}
    	if((GPIOC->IDR & 0x40U)){

    		GPIOJ->BSRR = (uint16_t)GPIO_PIN_5; // Turn on Green LED (LED2)

//    		GPIOC->BSRR |= 64U;

    	}else{
    		GPIOJ->BSRR = (uint32_t)GPIO_PIN_5 << 16;
    	}
    	if((GPIOJ->IDR & 0x2U)) {
    		GPIOA->BSRR = (uint16_t)GPIO_PIN_12; // Turn on Green LED (LED2)

    		printf("d2 is on\n\r");
    	}else{
    		GPIOA->BSRR = (uint32_t)GPIO_PIN_12 << 16;
    	}
    	if((GPIOF->IDR & 0x40U)) {
    		GPIOD->BSRR = (uint32_t)GPIO_PIN_4 << 16;

    		// Turn on Green LED (LED2)
    		printf("d3 is on\n\r");
    	}else{
    		GPIOD->BSRR = ((uint16_t)GPIO_PIN_4);
    	}
//    	GPIOD->BSRR = (uint32_t)GPIO_PIN_4 << 16;
//    	GPIOA->BSRR = (uint32_t)GPIO_PIN_12 << 16;
//    	GPIOJ->BSRR = (uint32_t)GPIO_PIN_5 << 16;
//    	GPIOJ->BSRR = (uint32_t)GPIO_PIN_13 << 16;

//    	GPIOJ->BSRR = (uint16_t)GPIO_PIN_13;
//    	GPIOJ->BSRR = (uint16_t)GPIO_PIN_5;
//    	GPIOA->BSRR = (uint16_t)GPIO_PIN_12;
//    	GPIOD->BSRR = ((uint16_t)GPIO_PIN_4);
//    	GPIOD->BSRR = (uint32_t)GPIO_PIN_4 << 16;



    }
}

#endif
