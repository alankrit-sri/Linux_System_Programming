#include<stdio.h>
#include<unistd.h>

int var = 10;

int main(void)
{
	pid_t cpid;
//	int var = 10;
		
	printf("In Parent Process : %d ; var : %d\n", getpid(), var);

	cpid = vfork();
	
	if(cpid == 0)
	{
		var = 20;
		printf("In Child Process : %d ; var : %d\n", getpid(), var);
	}
	else
	{	
		printf("In Parent Process : %d ; var : %d\n", getpid(), var);
	}

	return 0;
}
