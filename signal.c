#include<stdio.h>
#include<unistd.h>
#include<signal.h>

void sig_handler(int signal)
{
	printf("Interrupt Signal Triggered : %d\n", signal);
}

int main(void)
{
	struct sigaction sig;
	sig.sa_handler = sig_handler;
	
	if(sigaction(SIGINT, &sig, NULL) < 0)
	{
		perror("Signal registration failed\n");
	}

	while(1)
	{
		printf("In %s func , PID : %d\n", __func__, getpid());
		sleep(1);
	}

	return 0;
}
