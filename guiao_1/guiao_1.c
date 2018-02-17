#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "guiao_1.h"

//								1KB    1MB	  1MB
#define MEGA_10					1024 * 1024 * 1
#define ALL_OWNER_PERMI			S_IRUSR | S_IWUSR | S_IXUSR
#define ALL_PERMI				0777

//array de apontadores para funcoes 
void (*arr[])(void) = {exemplo_1, exemplo_2, exemplo_3, exemplo_4, exemplo_5, exemplo_6};

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


void exemplo_1(){ //imprime um erro caso nao consiga ler caracters do ficheiro apontado por fd = 3

	//char *buf = malloc(...);
	char buf[64];
	int n;

	if ( (n = read(3, buf, 30)) == -1){ // n é os caracteres lidos 

		perror ("erro na abertura do ficheiro");
		exit(-1);
	}
}

void exemplo_2(){ //cria um ficheiro file2.txt com 10 bytes do conteudo apontado por buf

	int n;
	char *buf = malloc(sizeof(char) * 16);
	char *path = "/Users/ricardopetronilho/Desktop/SO/guiao_1/file2.txt";

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

	close(f);
	free(buf);
}

void exemplo_3(){ //cria o ficheiro hello.txt com texto 

	int n, N;
	char c = ' ';
	char str[] = "Hello World!";
	for (N = 0; str[N]; N++);

	char *path = "/Users/ricardopetronilho/Desktop/SO/guiao_1/helloWorld.txt";

	int f = open(path, O_WRONLY | O_CREAT, ALL_OWNER_PERMI);

	for (n = 0; n < 2; n++){
		write(f, str, N * sizeof(char));
		if (n != 1) write(f, &c, sizeof(char));
	}

	close(f);
	//exit(n);
}


void exemplo_4(){ //cria o ficheiro arrayA.txt com os inteiros apontados pelo array (a) em HEXADECIMAL 

	int n;
	int N = 4;
	int a[] = {1, 2, 3, 4};

	/* 
		no ficheiro apareçe por exemplo o inteiro 1 da seguinte forma: 0100 0000
		o que tem sentido pois nos barramentos de dados, cada "word" é enviada
		"ao contrário" ou seja 0100 0000 na realidade é 0000 0001
	*/

	char *path = "/Users/ricardopetronilho/Desktop/SO/guiao_1/arrayA.txt";

	int f = open(path, O_WRONLY | O_CREAT, ALL_OWNER_PERMI);

	for (n = 0; n < 1; n++)
		write(f, a, N * sizeof(int));

	close(f);
	//exit(n);
}

void exemplo_5(){ //le o texto de um ficheiro.txt e imprime no terminal

	int n, N;
	char c = ' ';
	char str[] = "Hello World!";
	for (N = 0; str[N]; N++);

	char *path = "/Users/ricardopetronilho/Desktop/SO/guiao_1/helloWorld.txt";

	int f = open(path, O_RDWR | O_CREAT, ALL_OWNER_PERMI);

	for (n = 0; n < 2; n++){
		write(f, str, N * sizeof(char));
		if (n != 1) write(f, &c, sizeof(char));
	}

	// aqui temos o ficheiro helloWorld.txt com texto contido

	char g = '\n';
	char *buf = malloc(sizeof(char) * 64); // 64 bytes 

	lseek(f, 0, SEEK_SET);

	if ( (n = read(f, buf, 64)) == -1){

		perror("Erro ao ler ficheiro");
		exit(-1);
	}

	close(f);

	// write(1, ..., ...) e equivalente ao printf (output)
	write(1, buf, 12);
	write(1, &g, 1);
}

void exemplo_6(){ //imprime um erro caso nao consiga ler caracters do ficheiro apontado por fd = 3

	char c;
	int n;

	char *path = "/Users/ricardopetronilho/Desktop/SO/guiao_1/file3.txt";

	int f = open(path, O_RDWR | O_CREAT, ALL_OWNER_PERMI);

	while ( (n = read(0, &c, 1)) > 0) //ciclo infinito que apenas termina com o CTRL+D
		write (f, &c, 1);
}

void exe_3_1(){

	char c;
	int n;

	while ( (n = read(0, &c, 1)) > 0) //ciclo infinito que apenas termina com o CTRL+D
		write (1, &c, 1);
}

void exe_3_1_v2(){

	char c;
	int n = 1;

	while (n > 0){
		n = read(0, &c, 1);
		write (1, &c, 1);
	}
}

void exe_3_2(char **argv){

	char c = 'a';
	int n, f;

	//f é o file descriptor
	f = open(argv[1], O_WRONLY | O_CREAT, ALL_OWNER_PERMI);

	for (n = 0; n < MEGA_10; n++)
		write (f, &c, 1); // vai escrever no ficheiro apontado por f, caracter a caracter 

	close(f);
	exit(n);
}

int convertStringToInt(char *str){

	int n = 0;
	int i;

	int dim = strlen(str);

	for (i = dim - 1; i >= 0; i--) 
		n += (str[dim - i - 1] - '0') * pow (10, i);

	return n;
}

void exe_3_3(char **argv){ 

	/* 
		nota: (ENTER) conta como caracter ou seja, ao introduzir por exemplo 
		      ppp e carregar (ENTER) de seguida, na realidade estamos a introduzir
		      4 caracteres ---> ppp(ENTER)
	*/

	int N = convertStringToInt(argv[1]);
	char buf[N];
	int n;

	while ( (n = read(0, buf, N * sizeof(char))) > 0)
		write(1, buf, N * sizeof(char));

	exit(n);
}


void exe_3_4(char **argv){

	exe_3_3(argv);
}

ssize_t readln(int fildes, void *buf, size_t nbyte){

	// copyright: José Pereira

	int n, i = 0;

	while(i < nbyte){

		n = read(fildes, (char *) buf + i, sizeof(char));
		if ( *((char *) buf + i) == '\n' || n <= 0) break;
		i++;
	}

	if (i == nbyte){
		perror("Memoria reservada para o buffer insuficiente");
		exit(-1);
	}

	return i;
}


void exe_3_5(){	

	ssize_t n;
	
	int N = 64; // reservar 64 bytes para o buffer
	int *buf = malloc(N); // criar o buffer com os 64 bytes

	n = readln(0, buf, N); // le uma linha do terminal e retorna o tamanho

	write(1, buf, n + 1); // escreve essa mesma linha para testar se esta correto
}

void exe_3_6(char **argv){

	ssize_t n;
	char newLine = '\n';
	int linha = 1; // nº da linha
	int linha_2 = 1;
	char num_1[13]; // string que contem o numero da linha
	char num_2[13]; // string que contem o numero da linha repetida
	int dim; // dimensao da string
	
	int N = 1024; // reservar 1 MB para o buffer
	char *buf = malloc(N); // criar o buffer com os 64 bytes
	char *bufAnt = malloc(N); 
	
	int f = open(argv[1], O_RDONLY, ALL_PERMI);

	if (f == -1){
		perror("erro ao ler ficheiro");
		exit(-1);
	}

	while( (n = readln(f, buf, N)) > 0){

		sprintf(num_1, "%d ", linha); // coloca o nº da linha numa string
		for (dim = 0; num_1[dim]; dim++); // determina a dimensao dessa string
		write(1, num_1, dim * sizeof(char)); //escreve essa string no terminal
		write(1, buf, n); // escreve a linha do ficheiro no terminal
		
		if ( strcmp(buf, bufAnt) == 0 ){ // caso haja linhas repetidas, faz a numeração

			sprintf(num_2, " %d", linha_2); // coloca o nº da linha numa string
			for (dim = 0; num_2[dim]; dim++); // determina a dimensao dessa string
			write(1, num_2, dim * sizeof(char)); //escreve essa string no terminal
			linha_2++;

		} else linha_2 = 1;

		write(1, &newLine, 1);
		linha++;
		strcpy(bufAnt, buf);
	}
}

void exe_4_1(int agrc, char **argv){

	int i, f, n;
	int buffSize = 1024 * sizeof(char); //  1024 bytes = 1 MB
	char *buf = malloc(buffSize);
	char c = '\n';
	
	for (i = 1; i < agrc; i++){

		f = open(argv[i], O_RDONLY, ALL_PERMI);

		if ( (n = read(f, buf, buffSize)) == -1){ // le o conteudo do ficheiro

			perror("Erro ao ler ficheiro");
			exit(-1);
		}

		close(f);

		write(1, buf, n); // escreve o conteudo do ficheiro no terminal

		write(1, &c, 1); // new line entre cada ficehiro
	}
}

void exe_4_6(char **argv){

	int f1, f2, n1, n2;
	char c1, c2;
	char buf1[] = "True"; 
	char buf2[] = "False"; 
	//char newLine = '\n';
	int count = 0;

	f1 = open(argv[1], O_RDONLY, ALL_PERMI);
	f2 = open(argv[2], O_RDONLY, ALL_PERMI);

	while ( (n1 = read(f1, &c1, 1)) == -1 
		 && (n2 = read(f2, &c2, 1)) == -1 
		 && c1 == c2 ) count++;

	if (c1 == c2) write(1, buf1, 4);
	else write(1, buf2, 5);

	printf("\n%d\n", count);

	//write(1, &newLine, 1);
}


int main(int agrc, char **argv){	

	int exe = 3;
	int alinea = 6; 

	int exemplo = 6;

	if (exe == 3){

		switch(alinea){

			case 1:
				exe_3_1();
				//exe_3_1_v2();
				break;

			case 2:
				exe_3_2(argv);
				break;

			case 3:
				exe_3_3(argv);
				break;

			case 4:
				exe_3_4(argv);
				break;

			case 5:
				exe_3_5();
				break;

			case 6:
				exe_3_6(argv);
				break;

			default:
				perror("nao existe essa alinea");
				exit(-1);
		}	

	}

	else if (exe == 4){

		switch(alinea){

			case 1:
				exe_4_1(agrc, argv);
				break;

			case 6:
				exe_4_6(argv);
				break;

			default:
				perror("nao existe essa alinea");
				exit(-1);
		}	

	}

	else arr[exemplo - 1]();

	return 0;
}

