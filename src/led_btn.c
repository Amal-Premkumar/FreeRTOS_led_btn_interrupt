/*
 * led_btn.c
 *
 *  Created on: Nov 4, 2025
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

//task prototypes handlers
void LED_task_hndlr(void *params);
void BTN_task_hndlr(void *params);

//variable declaration
uint8_t BTN_pressed = NOT_PRESSED;


int main(void){
RCC_DeInit(); //this function makes HSI on, PLL off,system clk 16mhz

SystemCoreClockUpdate();

pvrt_stup_hdwr();


//create task for led and btn
xTaskCreate(LED_task_hndlr, "LED_task", configMINIMAL_STACK_SIZE, NULL, 1, NULL);

xTaskCreate(BTN_task_hndlr, "BTN_task", configMINIMAL_STACK_SIZE, NULL, 1, NULL);

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

void BTN_task_hndlr(void *params){
	while(1){
		if(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0)){
			BTN_pressed = PRESSED;
		}
		else{
			BTN_pressed = NOT_PRESSED;
		}
	}
}

static void pvrt_stup_hdwr(void){

	//setup btn and led
	pvrt_gpio_setup();
}


void pvrt_gpio_setup(void){

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
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
}
