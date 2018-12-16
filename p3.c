#include <stdio.h>
#include <freeRTOS.h>
#include "task.h"
#include "queue.h"
#include "semphr.h"



void enableFlushAfterPrintf()
{
	setvbuf(stdout, 0, _IONBF, 0);
	setvbuf(stdin, 0, _IONBF, 0);
}

xSemaphoreHandle employee_signal= 0;
void boss(void *p)
{
	while(1)
	{
		puts("Boss giving the signal");
		xSemaphoreGive(employee_signal);
		puts("Boss finished given the signal");
		vTaskDelay(2000);	
	}
	

}
void employee(void *p)
{
	while(1)
	{
		if(xSemaphoreTake(employee_signal, portMAX_DELAY))
		{
			employee_task();
			puts("employee has finish its task");
		}
	}

}

int main()
{
	enableFlushAfterPrintf();
	vSemaphoreCreateBinary(employee_signal);
	xSemaphoreTake(employee_signal, 0);
	
	// Create Tasks
	xTaskCreate(boss, (signed char*) "t1", 1024, NULL, 1, NULL);	
	xTaskCreate(employee, (signed char*) "rx", 1024, NULL, 2, NULL);	//employee has higher priority
	vTakeStartScheduler();
	return 0;

}
