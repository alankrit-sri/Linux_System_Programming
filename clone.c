#define _GNU_SOURCE
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sched.h>

#define STACK_SIZE 8192

int var;

int update_var(void *arg)
{
	var = 2;
	
	printf("%s => var : %d\n", __func__, var);
	printf("Child PID : %d\n", getpid());
	return 0;
}

int main(void)
{
	var = 1;
	
	printf("%s => var : %d\n", __func__, var);
	printf("Parent PID : %d\n", getpid());

	int *child_stack = (int*)malloc(STACK_SIZE);

	/* If CLONE_VM flag is SET then Parent Process and Child Process runs in the same virtual address space */	
	clone(update_var, child_stack + STACK_SIZE, CLONE_VM | CLONE_FILES, NULL);
	
	//clone(update_var, child_stack + STACK_SIZE, CLONE_FILES, NULL);
	
	sleep(1);

	printf("%s => var : %d\n", __func__, var);
	printf("Parent PID : %d\n", getpid());

	free(child_stack);

	return 0;
}
