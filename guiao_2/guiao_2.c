#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>

#include "guiao_2.h"


void printInt(int n){

	char num[12]; // array que vai conter o inteiro
	int len;
	char newLine = '\n';

	sprintf(num, "%d", n);
	for (len = 0; num[len]; len++);
	write(STDOUT_FILENO, &num, sizeof(char) * len);
	
	write(STDOUT_FILENO, &newLine, sizeof(char) );
}


void exe_3_1(){

	pid_t pai_pid = getppid();
	//printInt(pai_pid);
	printf("pid da bash = %d\n", pai_pid);
	
	/*
	pid_t pid = getpid();
	printInt(pid);
	*/
}


int main(){

	exe_3_1();
	return 0;
}