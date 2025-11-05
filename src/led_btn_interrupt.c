/*
 * led_btn_interrupt.c
 *
 *  Created on: Nov 5, 2025
 *      Author: Amal
 */


#include "stm32f4xx.h"
#include <stdio.h>
#include <string.h>

#include "FreeRTOS.h"
#include "task.h"


#define TRUE 1
#define FALSE 0
#define PRESSED TRUE
#define NOT_PRESSED FALSE

//function prototypes
static void pvrt_stup_hdwr(void);
void pvrt_gpio_setup(void);
void EXTI0_IRQHandler(void);

//task prototypes handlers
void LED_task_hndlr(void *params);
uint8_t BTN_hndlr(void);

//variable declaration
uint8_t BTN_pressed = NOT_PRESSED;



int main(void){
RCC_DeInit(); //this function makes HSI on, PLL off,system clk 16mhz

SystemCoreClockUpdate();

pvrt_stup_hdwr();


//create task for led and btn
xTaskCreate(LED_task_hndlr, "LED_task", configMINIMAL_STACK_SIZE, NULL, 1, NULL);


//start scheduling
vTaskStartScheduler();
while(1);
}


void LED_task_hndlr(void *params){
	while(1){
		if(BTN_pressed == PRESSED){
			//led on
			GPIO_WriteBit(GPIOD ,GPIO_Pin_15, Bit_SET);
		}
		else {
			//led off
			GPIO_WriteBit(GPIOD, GPIO_Pin_15, Bit_RESET);
		}

	}
}

uint8_t BTN_hndlr(void){

    for (volatile int i = 0; i < 50000; i++);  // small delay
    if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0))
        return TRUE;
    else
        return FALSE;
}


static void pvrt_stup_hdwr(void){

	//setup btn and led
	pvrt_gpio_setup();
}


void pvrt_gpio_setup(void){

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE); //enabling syscfg peripheral
	GPIO_InitTypeDef led_init , btn_init;

	led_init.GPIO_Mode = GPIO_Mode_OUT;
	led_init.GPIO_OType = GPIO_OType_PP;
	led_init.GPIO_Pin = GPIO_Pin_15;
	led_init.GPIO_PuPd = GPIO_PuPd_NOPULL;
	led_init.GPIO_Speed = GPIO_Low_Speed;

	GPIO_Init(GPIOD, &led_init);


	btn_init.GPIO_Mode = GPIO_Mode_IN;
	btn_init.GPIO_OType = GPIO_OType_PP;
	btn_init.GPIO_Pin = GPIO_Pin_0;
	btn_init.GPIO_PuPd = GPIO_PuPd_NOPULL;
	btn_init.GPIO_Speed = GPIO_Low_Speed;

	GPIO_Init(GPIOA, &btn_init);

	//button interrupt configuration(pinA 0)
	//first, system configuration for exti line (SYSCFG settings)

	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA, EXTI_PinSource0);

	//exti line configuration of falling edge and interrupt mode
	EXTI_InitTypeDef exti_init;
	exti_init.EXTI_Line = EXTI_Line0;
	exti_init.EXTI_Mode = EXTI_Mode_Interrupt;
	exti_init.EXTI_Trigger = EXTI_Trigger_Rising;
	exti_init.EXTI_LineCmd = ENABLE;

	EXTI_Init(&exti_init);

	//NVIC settings (irq setting for PA0)
	NVIC_SetPriority(EXTI0_IRQn, 5);
	NVIC_EnableIRQ(EXTI0_IRQn);
}

void EXTI0_IRQHandler(void){

	 if (BTN_hndlr())   // call the debounce function
	       {
	        BTN_pressed = !BTN_pressed;  // toggle state
	       }
	 //clear the interrupt pending bit of exti line 0
	 EXTI_ClearITPendingBit(EXTI_Line0);
}
