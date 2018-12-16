#include <stdio.h>
#include <freeRTOS.h>
#include "rit_isr.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"



void enableFlushAfterPrintf()
{
	setvbuf(stdout, 0, _IONBF, 0);
	setvbuf(stdin, 0, _IONBF, 0);
}

xSemaphoreHandle employee_signal= 0;

void one_sec_isr(void)
{
	long task_woken= 0;
	xSemaphoreGiveFromISR(binary_sem, &task_woken);
	if(task_woken)
	{
		vPortYieldFromISR();
	}
}
/*
	task1----->
		ISR------> Give Sem
			----> Back to Task1
	Task1----->
		ISR------> Give Sem then we also do yield
			Get back to sem_task()

*/
void sem_task(void *p)
{
	while(1)
	{
		if(xSemaphoreTake(binary_sem, portMAX_DELAY))
		{
			puts("Tick!");
		}
	}

}

int main()
{
	enableFlushAfterPrintf();
	rit_setup_callback(one_sec_isr, 1000);
	xTaskCreate(sem_task, (signed char*) "t", 2018, NULL, 1, NULL);	
	vTakeStartScheduler();
	return 0;

}
