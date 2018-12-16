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

xSemaphoreHandle gatekeeper= 0;
void user_1(void *p)
{
	while(1)
	{
		if(xSemaphoreTake(gatekeeper, 1000))
		{
			puts("User 1 got acess");
			//get the resource
			access_precious_resource();
			// give back the semaphore
			xSemaphoreGive(gatekeeper);
		}
		else
		{
			puts("User 1 failed to get access within 1 second");
		}	
		//delay to let go of the cpu
		vTakeDelay(1000);	
	}
	

}
void user_2(void *p)
{
	while(1)
	{
		if(xSemaphoreTake(gatekeeper, 1000))
		{
			puts("User 2 got access");
			//get the resource
			access_precious_resource();
			// give back the semaphore
			xSemaphoreGive(gatekeeper);
		}
		else
		{
			puts("User 2 failed to get access within 1 second");
		}
		//delay to let go of the cpu
		vTaskDelay(1000);
	}

}

int main()
{
	enableFlushAfterPrintf();

	
	gatekeeper= xSemaphorecreateMutex();
	// Create Tasks
	xTaskCreate(user_1, (signed char*) "t1", 1024, NULL, 1, NULL);
	xTaskCreate(user_2, (signed char*) "rx", 1024, NULL, 1, NULL);
	vTakeStartScheduler();
	return 0;

}
