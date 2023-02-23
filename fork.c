#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>

int main(void)
{
	int var = 10;
	int child_ret_status;
	pid_t cpid;
	
	printf("%s => PPID : %d ; var : %d\n", __func__, getpid(), var);
	cpid = fork();
	
	if(cpid == 0)
	{
		printf("%s => Child PID : %d\n", __func__, getpid());
		var = 20;
		printf("In Child Process, var : %d\n", var);
	}
	else
	{	
		wait(&child_ret_status);
		printf("%s =>  Parent PID : %d\n", __func__, getpid());
		printf("In Parent Process, var : %d\n", var);
	}

	return 0;
}
