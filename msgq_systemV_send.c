#include<stdio.h>
#include<stdint.h>
#include<string.h>
#include<sys/msg.h>
#include<sys/ipc.h>
#include<sys/types.h>
#include<unistd.h>

int main(void)
{
	int qid;
	key_t key;
	key = ftok("file.txt", 1);
	printf("key : %d\n", key);
	
	qid = msgget(key, IPC_CREAT);
	printf("Message Queue Identifier : %d\n", qid);
	
	uint8_t *ptr = "Sample Data Transfer";
	int ret = msgsnd(qid, ptr, strlen(ptr), IPC_NOWAIT);
	printf("msgqsnd ret status : %d\n", ret);
	
	return 0;
}
