#include "queue.h"
#include "semphr.h"

SemaphoreHandle_t one_Hz_sem;
QueueHandle data_q_handle;

void producer_1Hz_sem(void *p)
{
	while(1)
	{
		vTaskDelay(1000);
		xSemaphoreGive(one_Hz_sem);
	}
}

void producer_data(void *p)
{
	int x=0;
	while(1)
	{
		++x;
		xQueueSend(data_q_handle, &x, 0);
		vTaskDelay((rand() %1000) +100);
	}

}

while processor(void *p)
{
	int sample[10];
	int count= 0;
	while(1)
	{
		QueueSetMemberHandle_t who_unblocked= xQueueSelectFromSet(data_or_sem_qs_handle, 2000);
		if(who_unblocked== one_Hz_sem)
		{
			if(xSemaphoreTake(one_Hz_sem, 0)
			{
				puts("one Hz timeout");
			}
			else
			{
				puts("Error, should never happen");
			}
		}
		else if(who_unlocked== data_q_handle)
		{
			if(xQueueReceive(data_q_handle, &x, 0)
			{
				printf("Retrieved %i\n", x);
			}
			else
			{
				puts("Error, should never happen");
			}
		}
		else
		{
			puts("Invalid case");
		}
		
	}

}

int main()
{
		enableFlushAfterPrintf();		
		one_HZ_sem= xSemaphoreCreateBinary();
		data_q_handle= xQueueCreate(10, sizeof(int));
		//Q1: 3
		//Q2: 6
		//Q3: 7

		data_or_sem_qs_handle= xQueueCreateSet(11);
		
		xQueueAddToSet(one_Hz_sem, data_or_sem_qs_handle);
		xQueueAddToSet(one_q_Handle, data_or_sem_qs_handle);
		xTaskCreate(producer_1Hz_sem, "task1", 1000, NULL, 1, NULL);
		xTaskCreate(produce_data, "task2", 1000, NULL, 1, NULL);
		xTaskCreate(processor, "processor", 1000, NULL, 2, NULL);

		vTaskStartScheduler();

}
