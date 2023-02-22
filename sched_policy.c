#define _GNU_SOURCE

#include<stdio.h>
#include<unistd.h>
#include<sched.h>
#include<sys/wait.h>

void get_sched_policy(pid_t pid)
{
	int policy = sched_getscheduler(pid);
	
	if(policy & SCHED_RESET_ON_FORK)
	{
//             printf("Fork reset enabled\n");
             policy= policy & ~(SCHED_RESET_ON_FORK); // Enabling reset on fork
        }
		
	switch(policy)
	{
		case SCHED_OTHER:
		{
			printf("In %s => PID : %d => SCHED_OTHER Policy\n", __func__, pid);
		}
		break;
		
		case SCHED_BATCH:
		{
			printf("In %s => PID : %d => SCHED_BATCH Policy\n", __func__, pid);
		}
		break;
		
		case SCHED_IDLE:
		{
			printf("In %s => PID : %d => SCHED_IDLE Policy\n", __func__, pid);
		}
		break;
		
		case SCHED_FIFO:
		{
			printf("In %s => PID : %d => SCHED_FIFO Policy\n", __func__, pid);
		}
		break;
		
		case SCHED_RR:
		{
			printf("In %s => PID : %d => SCHED_RR Policy\n", __func__, pid);
		}
		break;

		default:
		{
			printf("Error\n");
		}
		break;
	}
}

int main(void)
{
	pid_t cpid;
	struct sched_param param;
	param.sched_priority = 70; /* Setting-up a RR priority */

	get_sched_policy(getpid());

	sched_setscheduler(getpid(), SCHED_RR | SCHED_RESET_ON_FORK, &param);
	
	get_sched_policy(getpid());

	cpid = fork();
	
	if(cpid == 0)
	{
		printf("\n%s func : In child process with pid %d\n", __func__, getpid());
		get_sched_policy(getpid());
	}
	else
	{
		wait(NULL);
		printf("\n%s func : In parent process with pid %d\n", __func__, getpid());  	
		get_sched_policy(getpid());
	}
	
	return 0;
}
