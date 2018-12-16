#include <stdio.h>
#include "tlm/cpp_task.hpp"


void enableFlushAfterPrintf()
{
	setvbuf(stdout, 0, _IONBF, 0);
	setvbuf(stdin, 0, _IONBF, 0);
}

class tx_task: public scheduler_task
{
	public:
		tx_task(): scheduler_task("tx", 4000, 1, NULL)
		{

		}
		bool init(void)
		{
			xQueuHandle intQ= xQueueCreate(1, sizeof(int));
			addSharedObject("intq_handle", intQ);	
			return true;
		}
		
		bool run( void *p)
		{
			static int item= 0;
			++item;
			xQueueHandle intQ= getSharedObject("intq_handle");
			xQueueSend(intQ, &item, 0);
			vTaskDelay(2000);
			return true;
		}
};

class rx_task: public scheduler_task
{
	public:
		rx_task(): scheduler_task("rx", 4000, 1, NULL)
		{

		}
		bool run( void *p)
		{
			xQueueHandle intQ= getSharedObject("intq_Handle");
			if(xQueueReceive(intQ, &buffer, 9999))
			{
				printf("Got %i from queue\n", buffer);
				scheduler_task *tx_task_ptr= getTaskPtrByName("Tx");
				if(NULL != tx_task_ptr)
				{	
					tx_task_ptr->getTaskHandle();
					puts("The tx task is suspended");
		
				}
			}
			return true;
		}
};
int main()
{
	enableFlushAfterPrintf();

	scheduler_add_task(new tx_task());
	scheduler_add_task(new rx_task());

	scheduler_start(false);
	return 0;

}
