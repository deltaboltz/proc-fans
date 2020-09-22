//TODO make main function still
//	process children
//	fork children
//	use waitpid to wait on children
//

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <err.h>
#include <unistd.h>
#include <sys/wait.h>
#include <getopt.h>

const int MAX_CANON = 10;
char** get_exec_argv(char* str);
void print_usage();

int* parse_cmd_line_args(int argc, char *argv[]);

int main(int argc, char *argv[])
{
	//Limit set by cmdln arguments
	int* procLimit;
	

	//Number of children allowed
	int procCount = 0;
	char cmd[MAX_CANON];
	
	//Child proc id
	pid_t childpid = 0;
	char** exec_argv;
	
	procLimit = parse_cmd_line_args(argc, argv);
	
	
	while(fgets(cmd, MAX_CANON, stdin))
	{
		if(procCount == *procLimit)
		{
			wait(NULL);
			procCount--;
		}
	
	
		//Check to see if we fork a child
		if((childpid = fork()) == 0)
		{
			//Remove newlines
			strtok(cmd, "\n");
		
			//pass execvp
			exec_argv = get_exec_argv(cmd);

			//execvp
			execvp(exec_argv[0], exec_argv);

			//print perror
			perror("Child fault: execvp failed");
			return 1;
		}

		//Check to see if fork failed
		if(childpid == -1)
		{
			perror("Child fault: fork failed");
			return 1;
		}
		
		//Increment procCount since we forked
		procCount++;
	

		//Wait check, did child finish?
		if(waitpid(-1, NULL, WNOHANG) > 0)
		{
			//Child finished, decrement
			procCount--;
		}
	}

	//check to see if childpid is > 0
	if(childpid > 0)
	{
		//if so while wait(NULL) > 0
		while(wait(NULL) > 0);
	}

	//deallocate procLimit
	free(procLimit);
	return 0;
}

char** get_exec_argv(char* str)
{
	int i = 0;
	char* substr;
	char** exec_argv = malloc(10 * sizeof(char));

	substr = strtok(str, " ");

	while(substr != NULL)
	{
		exec_argv[i] = malloc(20 * sizeof(char));
		exec_argv[i] = substr;
		substr = strtok(NULL, " ");
		i++;
	}
	exec_argv[i] = NULL;

	return exec_argv; 
}

int* parse_cmd_line_args(int argc, char *argv[])
{	
	int option;

	int* procLimit = malloc(sizeof(int));

	if(argc < 2)
	{
		print_usage();
	}
	
	while((option = getopt(argc, argv, "n:h")) != -1)
	switch(option)
	{
		case 'h':
			print_usage();
		
		case 'n':
			*procLimit = atoi(optarg);
			break;
		
		default:
			print_usage();
	}

	return procLimit;


}

void print_usage()
{
	fprintf(stderr, "-n is the max number of concurrent children allowed");
	exit(2);
}


