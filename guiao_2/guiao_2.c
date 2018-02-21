#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>

#include "guiao_2.h"

/*
	API a usar neste guiao:

	pid_t getpid(void);
	pid_t getppid(void);
	pid_t fork(void);
	void _exit(int status);
	pid_t wait(int *status);
	pid_t waitpid(pid_t pid, int *status, int options);
	int WIFEXITED(int status); 
	int WEXITSTATUS(int status); 
*/

void printInt(int n){

	char num[12]; // numero
	int len;
	char newLine = '\n';

	sprintf(num, "%d", n);
	for (len = 0; num[len]; len++);
	write(1, &num, sizeof(char) * len);
	
	write(1, &newLine, sizeof(char) );
}


int main(){

	pid_t pid = getpid();
	pid_t pai_pid = getppid();

	printInt(pid);
	printInt(pai_pid);

	return 0;
}