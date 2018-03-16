#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>

#define KB			   1024
#define MB		1024 * 1024





void exemplo_1(){

	int fd;

	if ( (fd = open("output.txt", O_CREAT | O_WRONLY | O_TRUNC, 0666)) == -1 ){

		perror("Erro ao abrir output.txt");
		_exit(1);
	}

	// fd = 3, mas não temos de saber; usa-se o resultado do open

	dup2(fd, 1);

	//Descriptor 3 doi COPIADO para o stdout, e por isso..

	close(fd);

	// como o printf usa a função write(1, ..., ...);
	// e o 1 é o fd, 
	char *str = "Hello my fellow friends!\n";

	//printf("Hello my fellow friends!\n");
	write(1, str, strlen(str) * sizeof(char));
}






void exe_4_1(){

	int fdIn, fdOut, fdErr;
	int bufSize = 2 * KB;
	void *buf = malloc( bufSize );
	int n;

	if ( (fdErr = open("error.txt", O_CREAT | O_WRONLY | O_TRUNC, 0666)) == -1 ){

		perror("Erro ao abrir error.txt");
		_exit(-1);
	}

	dup2(fdErr, 2); // stderror passa a ser o error.txt

	if ( (fdIn = open("/etc/passwd", O_RDONLY)) == -1 ){

		perror("Erro ao abrir /etc/passwd.txt");
		_exit(-1);
	}

	dup2(fdIn, 0); // stdin passa a ser o /ect/passwd.txt

	if ( (fdOut = open("output.txt", O_CREAT | O_WRONLY | O_TRUNC, 0666)) == -1 ){

		perror("Erro ao abrir output.txt");
		_exit(-1);
	}

	dup2(fdOut, 1); // stdout passa a ser o output.txt

	close(fdIn);
	close(fdOut);
	close(fdErr);

	// ler do stdin
	if ( (n = read(0, buf, bufSize)) == -1){

		perror("Erro ao ler ficheiro /etc/passwd.txt");
		_exit(2);
	}

	// escrever no stdout 
	write(1, buf, n);
}





void exe_4_2(){

	int fdIn, fdOut, fdErr;
	int bufSize = 2 * KB;
	void *buf = malloc( bufSize );
	int n;
	int status;
	pid_t p;

	if ( (fdErr = open("error.txt", O_CREAT | O_WRONLY | O_TRUNC, 0666)) == -1 ){

		perror("Erro ao abrir error.txt");
		_exit(-1);
	}

	dup2(fdErr, 2); // stderror passa a ser o error.txt

	if ( (fdIn = open("/etc/passwd", O_RDONLY)) == -1 ){

		perror("Erro ao abrir /etc/passwd.txt");
		_exit(-1);
	}

	dup2(fdIn, 0); // stdin passa a ser o /ect/passwd.txt

	if ( (fdOut = open("output.txt", O_CREAT | O_WRONLY | O_TRUNC, 0666)) == -1 ){

		perror("Erro ao abrir output.txt");
		_exit(-1);
	}

	dup2(fdOut, 1); // stdout passa a ser o output.txt

	close(fdIn);
	close(fdOut);
	close(fdErr);

	if ( (p = fork()) == -1){

		perror("fork error");
		_exit(3);
	}

	if (p == 0){

		// ler do stdin
		if ( (n = read(0, buf, bufSize)) == -1){

			perror("Erro ao ler ficheiro /etc/passwd.txt");
			_exit(2);
		}

		// escrever no stdout 
		write(1, buf, n);
	} 

	else wait(&status);
}






void exe_4_3(){

	int fdIn, fdOut, fdErr;

	if ( (fdErr = open("error.txt", O_CREAT | O_WRONLY | O_TRUNC, 0666)) == -1 ){

		perror("Erro ao abrir error.txt");
		_exit(-1);
	}

	dup2(fdErr, 2); // stderror passa a ser o error.txt

	if ( (fdIn = open("/etc/passwd", O_RDONLY)) == -1 ){

		perror("Erro ao abrir /etc/passwd.txt");
		_exit(-1);
	}

	dup2(fdIn, 0); // stdin passa a ser o /ect/passwd.txt

	if ( (fdOut = open("output.txt", O_CREAT | O_WRONLY | O_TRUNC, 0666)) == -1 ){

		perror("Erro ao abrir output.txt");
		_exit(-1);
	}

	dup2(fdOut, 1); // stdout passa a ser o output.txt

	close(fdIn);
	close(fdOut);
	close(fdErr);

	execlp("wc", "amo o jose pereira", (char*) NULL);
}


void exe_4_4(){

	// redir [-i fich_entrada] [-o fich_saida] comando arg1 arg2 ...
}




int main(){

	//exemplo_1();
	//exe_4_1();
	//exe_4_2();
	exe_4_3();
}






