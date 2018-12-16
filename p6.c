#include "FreeRTOS/FreeRTOS.h"
#include "FreeRTOS/task.h"
#include "FreeRTOS/queue.h"

void enableFlushAfterPrintf()
{
	setvbuf(stdout, 0, _IONBF, 0);
	setvbuf(stdin, 0, _IONBF, 0);
}

xQueueHandle Global_Queue_handle=0;
void sender_task(void *p)
{
	int item=0;
	while(1)
	{
		printf("tx() send to queue: ");	
		long ok= xQueueSend(queue_handle, &item, 500);
		puts(ok? "OK" : "FAILED");

		vTaskDelay(200);
	}

}
void receiver_task(void *p)
{
	int rx_int=0;
	while(1)
	{
		if(xQueueReceive(queue_handle, &item, 500))
		{
			printf("rx() Got item from queue\n");
		}
		else
		{
			printf(" rx() failed to get an item within t0");
		}
		
	}

}

int main()
{
	setvbuf(stdout, 0, _IONBF, 0);
	setvbuf(stdin, 0, _IONBUF, 0);

	queue_handle= xQueueCreate(2, sizeof(int));
	xTaskCreated(tx, (signed char) "tx", 1024, NULL, 1, NULL);
	xTaskCreated(tx, (signed char) "rx", 1024, NULL, 2, NULL);
	vTaskStartScheduler();
	return 0;

}
