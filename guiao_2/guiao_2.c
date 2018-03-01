#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "guiao_2.h"

#define TRUE 		1
#define FALSE		0

/**
@file guiao_2.c
Main file
*/


/**
\brief Escreve em STDOUT_FILENO (terminal) o inteiro n
@param n - inteiro n
*/
void printInt(int n){

	char num[12]; // array que vai conter o inteiro
	int len;
	char newLine = '\n';

	sprintf(num, "%d", n);
	for (len = 0; num[len]; len++);
	write(STDOUT_FILENO, &num, sizeof(char) * len);
	
	write(STDOUT_FILENO, &newLine, sizeof(char) );
}


/**
\brief Criar um processo filho\n
	   Pai e filho imprimem o seu identificador de processo e o do seu pai\n
	   O pai imprime o pid do seu filho
*/
void exemplo_1(){

	char str[1024];
	char newLine = '\n';

	strcpy(str, "antes do fork() - apenas o pai executa esta parte\n");
	write( 1, str, strlen(str) );
	write(1, &newLine, sizeof(char) );

	pid_t p = fork(); // criar um processo filho e devovle o seu pid
	
	pid_t pai_pid = getppid();
	strcpy(str, "PID do meu pai = ");
	write( 1, str, strlen(str) );
	printInt(pai_pid);

	pid_t pid = getpid();
	strcpy(str, "myPID = ");
	write( 1, str, strlen(str) );
	printInt(pid);

	strcpy(str, "PID do meu filho = ");
	write( 1, str, strlen(str) );
	printInt(p);

	write(1, &newLine, sizeof(char) );
}


/**
\brief Criar um processo filho\n
	   Pai e filho imprimem o seu identificador de processo e o do seu pai\n
	   O pai imprime o pid do seu filho e espera que o filho termine a sua execução
*/
void exemplo_2(){

	char str[1024];
	char newLine = '\n';
	pid_t p, w, pai_pid, pid;
	int status;

	strcpy(str, "antes do fork() - apenas o pai executa esta parte\n");
	write( 1, str, strlen(str) );
	write(1, &newLine, sizeof(char) );

	if ( (p = fork()) == -1 ){
	/* Upon successful completion, fork() returns a value of 0 to the child process and returns the
	process ID of the child process to the parent process.  Otherwise, a value of -1 is returned
	to the parent process, no child process is created, and the global variable errno is set to
	indicate the error. */
		perror("fork error");
		_exit(p);
	}

	if (  p != 0 &&  (w = wait(&status)) == -1 ){
	/* If wait() returns due to a stopped or terminated child process, the process ID of the child is
	returned to the calling process.  Otherwise, a value of -1 is returned and errno is set to
	indicate the error. */

		perror("wait error");
		_exit(w);

	} else if ( p != 0 ) printf("wait return (child pid) = %d\n", w);

	pai_pid = getppid();
	strcpy(str, "PID do meu pai = ");
	write( 1, str, strlen(str) );
	printInt(pai_pid);

	pid = getpid();
	strcpy(str, "myPID = ");
	write( 1, str, strlen(str) );
	printInt(pid);

	strcpy(str, "PID do meu filho = ");
	write( 1, str, strlen(str) );
	printInt(p);

	write(1, &newLine, sizeof(char) );
}


/**
\brief Exercício 3.1 do guião 2\n
	   Imprimir o identificador de processo e o do seu pai\n
	   Deve-se utilizar o comando - ps - para confirmar os PIDs dos processos
*/
void exe_3_1(){

	pid_t pai_pid = getppid();
	write( 1, "PID do pai = ", 14 * sizeof(char) );
	printInt(pai_pid);
	
	pid_t pid = getpid();
	write( 1, "myPID = ", 8 * sizeof(char) );
	printInt(pid);
	getchar(); 
}


/**
\brief Executa alternativamente um dos exercícios pedidos no guiao 2
*/
int main(){

	//exe_3_1();
	//exemplo_1();
	exemplo_2();
	return 0;
}






