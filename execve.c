#include<stdio.h>
#include<unistd.h>

int main(int argc, char *argv[])
{
	printf("Pre-execve calling\n");
	execve("./test_execve", argv, NULL);
	printf("Post-execve call\n");
        return 0;
}
