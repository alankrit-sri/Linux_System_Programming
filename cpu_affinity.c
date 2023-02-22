#define _GNU_SOURCE

#include<stdio.h>
#include<unistd.h>
#include<sched.h>

int main(void)
{
	cpu_set_t set;
	int no_of_processors;

	printf("PID : %d\n", getpid());

	no_of_processors = sysconf(_SC_NPROCESSORS_CONF);
	printf("Total available processors : %d\n", no_of_processors);

	if(sched_getaffinity(getpid(), sizeof(set), &set) == -1)
	{
		printf("Get CPU Affinity Failed\n");
	}

	CPU_ZERO(&set);
	CPU_SET(2, &set);

	if(sched_setaffinity(getpid(), sizeof(set), &set) == -1)
	{
		printf("Set CPU Affinity Failed\n");
	}
		
	return 0;
}
