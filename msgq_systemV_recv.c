#include<stdio.h>
#include<stdint.h>
#include<string.h>
#include<unistd.h>
#include<sys/msg.h>
#include<sys/ipc.h>
#include<sys/types.h>

int main(void)
{
	uint8_t buffer[50];
	int buffer_size = sizeof(buffer)/sizeof(buffer[0]);
	int qid;
	
	key_t key;
	key = ftok("file.txt", 1);
	
	qid = msgget(key, IPC_CREAT);
	printf("qid : %d\n", qid);
	
	memset(buffer, 0, buffer_size);
	
	int size = msgrcv(qid, buffer, buffer_size, 0, IPC_NOWAIT);
	printf("Received bytes : %d\n", size);
	printf("Data Received : %s\n", buffer);
	
//	msgctl(qid, IPC_RMID, NULL);
	
	return 0;
}
