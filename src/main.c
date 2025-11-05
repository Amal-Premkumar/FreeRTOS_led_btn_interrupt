#include"FreeRTOS.h"
#include <stdio.h>
#include "stm32f4xx.h"
#include "task.h"



TaskHandle_t vTask_handle1=NULL;
TaskHandle_t vTask_handle2=NULL;

//task functions prototypes
vTask1_handler(void *params);
vTask2_handler(void * params);
static void pvrt_stup_hdwr(void);
#ifdef USE_SEMIHOSTING
extern void initialise_monitor_handles(void);  // for semihosting
#endif
int main(void) {

#ifdef USE_SEMIHOSTING
	initialise_monitor_handles();
	printf("initialzing rcc\n");
#endif
	RCC_DeInit(); //this function makes HSI on, PLL off,system clk 16mhz

	SystemCoreClockUpdate();

	pvrt_stup_hdwr();

	//create 2 tasks

	xTaskCreate(vTask1_handler, "task1", configMINIMAL_STACK_SIZE, NULL, 0, &vTask_handle1);

	xTaskCreate(vTask2_handler, "task2", configMINIMAL_STACK_SIZE, NULL, 0, &vTask_handle2);


	vTaskStartScheduler(); //what basically does is it'll start running each task for a set of time and shift to other task


    while(1); // Should never reach here
}

vTask1_handler(void *params){

while(1){
	printf("task1 complied\n");
}
}

vTask2_handler(void * params){

while(1){
	printf("task2 complied\n");
}
}

static void pvrt_stup_hdwr(void){

}
