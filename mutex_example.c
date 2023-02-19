#include<stdio.h>
#include<pthread.h>
#define SYNC_COUNT 15

int n = 0;
pthread_mutex_t lock;

void* odd_print(void *arg)
{
	while (n < SYNC_COUNT)
	{
		pthread_mutex_lock(&lock);
		if(n%2 ==  1 && (n < SYNC_COUNT))
		{
			printf("ODD PRINT:%d\n", n);
			n++;
		}	
		pthread_mutex_unlock(&lock);
	}
}

void* even_print(void *arg)
{
	while (n < SYNC_COUNT)
	{
		pthread_mutex_lock(&lock);
		if(n%2 == 0 && (n < SYNC_COUNT))
		{
			printf("EVEN PRINT:%d\n", n);
			n++;
		}
		pthread_mutex_unlock(&lock);
	}
}

int main(void)
{
	pthread_t t1, t2;

	if ( pthread_mutex_init(&lock, NULL) != 0 )
	{
	     printf("mutex_init failed\n");
	}
	
	pthread_create(&t1, NULL, &even_print, NULL);
	pthread_create(&t2, NULL, &odd_print, NULL);

	pthread_exit(NULL);

	return 0;
}
