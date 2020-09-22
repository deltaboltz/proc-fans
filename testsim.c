#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
	int i;
	int repeat;
	int sleepTime;
	
	if(argc != 3)
	{
		fprintf(stderr, "Usage %s repeatFactor sleep NULL\n", argv[0]);
		return 1;
	}

	repeat = atoi(argv[1]);
	sleepTime = atoi(argv[2]);

	for(i = 0; i < repeat; i++)
	{
		sleep(sleepTime);
		fprintf(stderr, "pid: %d _ repeat factor: %d _ sleep time:%d\n", getpid(), repeat, sleepTime);
	}

	return 0;
}
