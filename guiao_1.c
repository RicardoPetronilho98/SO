#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

//								1KB    1MB	  1MB
#define MEGA_10					1024 * 1024 * 1
#define ALLPERMISSIONS			0777

void exemplo_1();
void exe_3_1();
void exe_3_2(char *path);

//array de apontadores para funcoes 
void (*arr[])(void) = {exemplo_1, exe_3_1};


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

	//arr[0]();
	exe_3_2(argv[1]);
	return 0;
}

void exemplo_1(){

	//void *buf = malloc(...);
	char buf[64];
	int n;

	if ( (n = read(3, buf, 30)) == -1){ // n é os caracteres lidos 

		perror ("erro na abertura do ficheiro");
		exit(-1);
	}
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
	f = open(path, O_WRONLY | O_CREAT, ALLPERMISSIONS);

	for (n = 0; n < MEGA_10; n++)
		write (f, &c, 1); // vai escrever no ficheiro apontado por f, caracter a caracter 

	exit(n);
}



