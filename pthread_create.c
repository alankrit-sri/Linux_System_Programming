#include<stdio.h>
#include<pthread.h>
#include<unistd.h>

void* thread1(void *arg)
{
	printf("Thread 1\n");
	sleep(2);
}

void* thread2(void *arg)
{
	printf("Thread 2\n");
}

int main()
{
	pthread_t t1, t2;
	pthread_attr_t attr_t1, attr_t2;
	int ret = 0;
	void *state;
	
	pthread_attr_init(&attr_t1);
	pthread_attr_init(&attr_t2);
	
	pthread_create(&t1, &attr_t1, thread1, NULL);
	pthread_create(&t2, &attr_t2, thread2, NULL);
	
	sleep(5);
	ret = pthread_join(t1, &state);
	printf("pthread_join t1 ret value : %d\n", ret);
	
	ret = pthread_join(t2, &state);
	printf("pthread_join t2 ret value : %d\n", ret);
		
	return 0;
}
