#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>

#include "guiao_2.h"


void printInt(int n){

	char num[12]; // numero
	int len;
	char newLine = '\n';

	sprintf(num, "%d", n);
	for (len = 0; num[len]; len++);
	write(STDOUT_FILENO, &num, sizeof(char) * len);
	
	write(STDOUT_FILENO, &newLine, sizeof(char) );
}


void exe_3_1(){

	pid_t pid = getpid();
	pid_t pai_pid = getppid();

	printInt(pid);
	printInt(pai_pid);
}


int main(){

	exe_3_1();

	return 0;
}