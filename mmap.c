#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdlib.h>
#include<string.h>
#include<sys/mman.h>
#include<sys/wait.h>

#define FILE_SIZE 1024

int main(int argc, char *argv[])
{
	int fd;
	pid_t cpid;
	char *fp;

	cpid = fork();

	if(cpid == 0)
	{
		printf("%s : In Child Process : %d\n", __func__, getpid());
		fd = open(argv[1], O_CREAT | O_RDWR, S_IRWXU | S_IRWXO | S_IRWXG);
		
		if(fd < 0)
		{
			perror("In Child, fd system call failed\n");
			exit(1);
		}
		
		write(fd, "Mapped Data", strlen("Mapped Data"));

		fp = mmap(0, FILE_SIZE, PROT_READ | PROT_WRITE | PROT_EXEC, MAP_SHARED, fd, 0); 	
		
		if(fp == MAP_FAILED)
		{
			perror("In Child, mmap system call failed\n");
			exit(2);
		}
		close(fd);
	}
	else
	{
		wait(NULL);
		printf("%s : In Parent Process : %d\n", __func__, getpid());
		
		fd = open(argv[1], O_RDONLY);
		
		if(fd < 0)
		{
			perror("In Parent, fd system call failed\n");
			exit(1);
		}
		
		fp = mmap(0, FILE_SIZE, PROT_READ | PROT_EXEC, MAP_SHARED, fd, 0); 	

		if(fp == MAP_FAILED)
		{
			perror("In Parent, mmap system call failed\n");
			exit(2);
		}
		
		close(fd);

		printf("In Parent : %s\n", (char*)fp);
		
		if(munmap(0, FILE_SIZE) < 0)
		{
			perror("In Parent : munmap failed\n");
			exit(3);
		}
		
	}
	return 0;
}
