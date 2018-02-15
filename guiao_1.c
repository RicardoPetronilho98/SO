#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

#include "guiao_1.h"

//								1KB    1MB	  1MB
#define MEGA_10					1024 * 1024 * 1
#define ALL_OWNER_PERMI			S_IRUSR | S_IWUSR | S_IXUSR


//array de apontadores para funcoes 
void (*arr[])(void) = {exemplo_1, exemplo_2, exemplo_3, exemplo_4};

/* 
	API para manipular ficheiros:

	int     open(const char *path, int oflag [, mode]);
	ssize_t read(int fildes, void *buf, size_t nbyte);
	ssize_t write(int fildes, const void *buf, size_t nbyte);
	int     close(int fildes);

	flags mais comuns e importantes da função OPEN:

	O_RDONLY        open for reading only
	O_WRONLY        open for writing only
	O_RDWR          open for reading and writing 
	O_CREAT         create file if it does not exist
*/

/*
	-eu-grupo-outros
	-rwe-rwe-rwe
	-rw-r--r--

	umask 777 
	cp file fileCopia
	fileCopia --> não vai ter premissões de rwe (ls -l fileCopia: ----------)

	if (...) {
		perror("erro na abertura do ficheiro"); 
		exit(-1);
	}
*/

/*
	stty all -> mostra as combinações do teclado para controlo nos processos
	!g ---> india os comandos anteriores (no histórico) começados por g neste caso, ex: gcc -wall ...
*/

int main(int agrc, char **argv){	

	arr[2]();
	//exe_3_1();
	//exe_3_2(argv[1]);
	//exe_3_3(10);
	exe_3_5();

	return 0;
}

void exemplo_1(){

	//char *buf = malloc(...);
	char buf[64];
	int n;

	if ( (n = read(3, buf, 30)) == -1){ // n é os caracteres lidos 

		perror ("erro na abertura do ficheiro");
		exit(-1);
	}
}

void exemplo_2(){

	int n;
	char *buf = malloc(sizeof(char) * 16);
	char *path = "/Users/ricardopetronilho/Desktop/SO/file2.txt";

	int f = open(path, O_WRONLY | O_CREAT, ALL_OWNER_PERMI);

	for (n = 0; n < 1; n++) 
		write(f, buf, 10); 
		//significa ---> escreve no ficheiro apontado por f, 10 bytes do que esta apontado por buf

	/* 
		neste caso foi escrito 5 blocos de HEXADECIMAL
		1 HEXADECIMAL == 16 bits (0-15) == 2 bytes
		5 HEXADECIMAL == 10 bytes
		
		o que faz sentido pois mandei escrever 1 vez -> 10 bytes
		MAS...

		-------> DUVIDA: pq escreve em HEXADECIMAL quando se tenta escrever
						 mais bytes do que o tamanho do buffer??? 
	*/

	free(buf);
}

void exemplo_3(){

	int n, N;
	char c = ' ';
	char str[] = "Hello World!";
	for (N = 0; str[N]; N++);

	char *path = "/Users/ricardopetronilho/Desktop/SO/helloWorld.txt";

	int f = open(path, O_WRONLY | O_CREAT, ALL_OWNER_PERMI);

	for (n = 0; n < 2; n++){
		write(f, str, N * sizeof(char));
		if (n != 1) write(f, &c, sizeof(char));
	}

	//exit(n);
}


void exemplo_4(){

	int n;
	int N = 4;
	int a[] = {1, 2, 3, 4};

	char *path = "/Users/ricardopetronilho/Desktop/SO/arrayA.txt";

	int f = open(path, O_WRONLY | O_CREAT, ALL_OWNER_PERMI);

	for (n = 0; n < 1; n++)
		write(f, a, N * sizeof(int));

	//exit(n);
}


void exe_3_1(){

	char c;
	int n;

	while ( (n = read(0, &c, 1)) > 0) 
		write (1, &c, 1); //ai!!! devia ver se deu erro

	exit(n);
}

void exe_3_2(char *path){

	char c = 'a';
	int n, f;

	//the file descriptor is returned to the calling process
	f = open(path, O_WRONLY | O_CREAT, ALL_OWNER_PERMI);

	for (n = 0; n < MEGA_10; n++)
		write (f, &c, 1); // vai escrever no ficheiro apontado por f, caracter a caracter 

	exit(n);
}

void exe_3_3(int N){

	//DUVIDA -----> NÃO FUNCIONA...

	char buf[N];
	int n;

	while ( (n = read(0, buf, N)) > 0)
		write(1, buf, N * sizeof(char));

	exit(n);
}

void exe_3_5(){


}

