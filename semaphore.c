#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>
#include <semaphore.h>

void *myfunc1(void *ptr);
void *myfunc2(void *ptr);

int buf[24];
sem_t mutex;

int main(int argc, char *argv[])
{
	pthread_t thread1;
	pthread_t thread2;

	char *msg1= "Thread 1";
	char *msg2= "Thread 2";
	
	sem_init(&mutex, 0, 1);

	pthread_create(&thread1, NULL, myfunc1, (void *) msg1);
	pthread_create(&thread2, NULL, myfunc2, (void *) msg2);

	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);

	sem_destroy(&mutex);


return 0;
}

void *myfunc1(void *ptr)
{
	char *msg= (char*) ptr;

	printf("%s \n", msg);

	sem_wait(&mutex);

	printf(buf, "%s", "Hello There !");

	sem_post(&mutex);

	pthread_exit(0);
	
	
}

void *myfunc2(void *ptr)
{
	char *msg= (char*) ptr;

	printf("%s\n", msg);

	sem_wait(&mutex);

	printf("%s\n", buf);

	sem_post(&mutex);

	

	pthread_exit(0);
	
		
}
