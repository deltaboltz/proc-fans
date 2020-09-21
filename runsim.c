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
#include <unistd.h>
#include <getopt.h>

char** get_exec_argv(char* str);
void print_usage();

int* parse_cmd_line_args(int argc, char *argv[]);

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
	exec_argv[i] == NULL;

	return exec_argv; 
}

int* parse_cmd_line_args(int argc, char *argv[])
{	
	int option;

	int* procLimit = malloc(sizeif(int));

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

int main(int argc, char *argv[])
{
	//set max number of concurrent children
	//get count of number of children
	


	//process cmd argument
	//get childpid
	//pass execv
	

	//get limit user inputted for procLimit
	procLimit = parse_cmd_line_args(argc, argv)

	//check to see if we fork a child
	//exec_argv
	//execvp
	//print a perror
	

	//increment procCount
	//wait
	//decrement procCount
	

	//check to see if childpid is > 0
	//if so while(NULL) > 0
	
	//deallocate procLimit
	
	return 0;
}
