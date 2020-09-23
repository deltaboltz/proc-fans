#include <stdio.h>
#include <string.h>
#include <err.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <ctype.h>
#include <getopt.h>

const int MAX_CANON = 10;
char** get_exec_argv(char* str);
void print_usage();

int* parse_cmd_line_args(int argc, char *argv[]);

int main(int argc, char *argv[]){
	//Limit set by cmdln arguments
	int* proc_limit;
	

	//Number of children allowed
	int proc_count = 0;
	char cmd[MAX_CANON];
	
	//Child proc id
	pid_t childpid = 0;
	char** exec_argv;
	
	proc_limit = parse_cmd_line_args(argc, argv);
	
	
	while(fgets(cmd, MAX_CANON, stdin)){
		if(proc_count == *proc_limit){
			wait(NULL);
			proc_count -= 1;
		}
	
	
		//Check to see if we fork a child
		if((childpid = fork()) == 0){
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
		if(childpid == -1){
			perror("Child fault: fork failed");
			return 1;
		}
		
		//Increment procCount since we forked
		proc_count += 1;
	

		//Wait check, did child finish?
		if(waitpid(-1, NULL, WNOHANG) > 0){
			//Child finished, decrement
			proc_count -= 1;
		}
	}

	//check to see if childpid is > 0
	if(childpid > 0){
		//if so while wait(NULL) > 0
		while(wait(NULL) > 0);
	}

	//deallocate procLimit
	free(proc_limit);
	return 0;
}

char** get_exec_argv(char* str){
	
	char* substr;
	char** exec_argv = malloc(10 * sizeof(char));

	substr = strtok(str, " ");

	int i = 0;
	while(substr != NULL){
		exec_argv[i] = malloc(20 * sizeof(char));
		exec_argv[i] = substr;
		substr = strtok(NULL, " ");
		i++;
	}
	exec_argv[i] = NULL;

	return exec_argv; 
}

int* parse_cmd_line_args(int argc, char *argv[]){	
	

	int* proc_limit = malloc(sizeof(int));

	if(argc < 2){
		print_usage();
	}
	
	int option;
	while((option = getopt(argc, argv, "n:h")) != -1)
	switch(option){
		case 'h':
			print_usage();
		
		case 'n':
			*proc_limit = atoi(optarg);
			break;
		
		default:
			print_usage();
	}

	return proc_limit;
}

void print_usage(){
	fprintf(stderr, "-n is the max number of concurrent children allowed");
	exit(2);
}


