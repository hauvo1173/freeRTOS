#include "event_groups.h"


/*
	--AB
	1	<--Task1 (good task)
	1	<--Task2 (bad task)
	11	<--WatchDog task waiting for bits to set


*/
EventGroupHandle_t task_watchdog;
const uint32_t good_task_id= (1<<0);
const uint32_t bad_task_id= (1<<1);
const uint32_t tasks_all_bits= (good_task_id | bad_task_id);

void good_task(void *p)
{
	while(1)
	{
		//good task, so let's always set the event group
		xEventGroupSetBits(task_watchdog, good_task_id);
		xTaskDelay(1000);
	}
}

void bad_task(void *p)
{
	int x=0;
	while(1)
	{
		++x;
		if(x>= 3 && x<= 6)
		{

		}
		else
		{
			xEventGroupSetBits(task_watchdog, bad_task_id);
		}
		vTaskDelay(1000);
	}
}

void sw_watchdog(void *)
{
	while(1)
	{
		uint32_t result= xEvenGroupWaitBits(task_watchdog, task_all bits,
	 	pdTRUE,	//Clear bits on exit
		pdTRUE,	//wait for all bits to be set
		2000);
		if((result & tasks_all_bits)== task_all_bits)
		{
			puts("good task stopped responding..");
		}
		if(!(result & bad_task_id))
		{
			puts("bad task stopped responding...");
		}
	}

}
int main()
{
	enableFlushAfterPrintf();

	task watchdog= xEventGroupCreate();
	xTaskCreate(good_task, "task1", 1000, NULL, 1, NULL);
	xTaskCreate(bad_task, "task2", 1000, NULL, 1, NULL);
	xTaskCreate(sw_watchdog, "sw_watchdog", 1000, NULL, 1, NULL);
	vTaskStartScheduler();

return 0;
}
