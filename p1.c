#include <stdio.h>
#include <freeRTOS.h>
#include "task.h"
#include "queue.h"


void enableFlushAfterPrintf()
{
	setvbuf(stdout, 0, _IONBF, 0);
	setvbuf(stdin, 0, _IONBF, 0);
}

xQueueHandle Global_Queue_handle=0;
void sender_task(void *p)
{
	int i=0;
	while(1)
	{
		printf("send %i to receiver take\n", i);
		if(!xQueueSend(Global_Queue_Handle, &i, 1000))
		{
			printf("Failed to send to queue");
		}
		++i;
		vTaskDelay(1000);  //sleep for 1 second
	}

}
void receiver_task(void *p)
{
	int rx_int=0;
	while(1)
	{
		if(xQueueReceive(Global_Queue_handle, &rx_int, 1000)	//only wake up when Queue is received
		{
			printf("Receive %i\n", rx_int);
		}
		else
		{
			puts("Failed to receive data from Queue");
		}
		
	}

}

int main()
{
	enableFlushAfterPrintf();

	Global_Queue_Handle= xQueueCreate(3, sizeof(int));

	
	xTaskCreate(sender_task, (signed char*) "tx", 1024, NULL, 1, NULL);
	xTaskCreate(receiver_task, (signed char*) "rx", 1024, NULL, 1, NULL);
	vTakeStartScheduler();
	return 0;

}
