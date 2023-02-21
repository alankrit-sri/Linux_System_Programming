#include<stdio.h>

int main(int argc, char *argv[])
{
	if(argc == 1)
	{
		printf("No Arguments Present\n");
		return 0;
	}
	for(int i = 1; i < argc; ++i)
	{
		printf("Argument %d : %s\n", i, argv[i]); 
	}
	
	return 0;
}
