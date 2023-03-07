#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/mman.h>
#include<sys/stat.h>
#include<sys/wait.h>
#include<fcntl.h>
#include<semaphore.h>

#define NAME "file.txt"
#define SEMA "SEMA"

typedef struct{
	sem_t *sem;
	int val;
}shared_mem_t;

int main(int argc, char *argv[])
{
	pid_t cpid;
	int fd, ftrunc_status;
	sem_t *sem_ret;
	shared_mem_t *addr;

	cpid = fork(); 

	if(cpid == 0)
	{
		printf("Child PID : %d\n", getpid());

		fd = shm_open(NAME, O_RDWR | O_CREAT, 666);
		ftrunc_status = ftruncate(fd, sizeof(shared_mem_t));
		
		if(ftrunc_status != 0)
		{
			perror("ftruncate failed\n");
			exit(10);
		}

		addr = (shared_mem_t *)mmap(NULL, sizeof(shared_mem_t), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
		if(addr == MAP_FAILED)
		{
			printf("mmap sys call failed in Child Process\n");
			exit(1);
		}

		sem_ret = sem_open(SEMA, O_CREAT, S_IRUSR | S_IWUSR | S_IXUSR | S_IROTH | S_IWOTH | S_IRGRP | S_IWGRP, 1);
		addr->sem = sem_ret;
		
		sem_wait(addr->sem);
		addr->val = 0;
		for(int i = 0; i < 5; ++i)
			{
				addr->val += 10;
				printf("Child status : %d\n", addr->val);
			}
		sem_post(addr->sem);
		munmap(addr, sizeof(shared_mem_t));
	}

	else
	{
		sleep(1);
		printf("\nParent PID : %d\n", getpid());
		fd = shm_open(NAME, O_RDWR, 666);

		addr = (shared_mem_t*)mmap(NULL, sizeof(shared_mem_t), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

		if(addr == MAP_FAILED)
		{
			printf("mmap sys call failed in Parent Process\n");
			exit(3);
		}	

		sem_ret = sem_open(SEMA, O_CREAT, S_IRUSR | S_IWUSR | S_IXUSR | S_IROTH | S_IWOTH | S_IRGRP | S_IWGRP, 1);
		addr->sem = sem_ret;
		
		sem_wait(addr->sem);
		for(int i = 0; i < 5; ++i)
		{
			addr->val += 20;
			printf("Parent status : %d\n", addr->val);
		}
		sem_post(addr->sem);

		sem_destroy(addr->sem);
		munmap(addr, sizeof(shared_mem_t));
	}

	return 0;
}

