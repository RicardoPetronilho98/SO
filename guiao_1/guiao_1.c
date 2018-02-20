#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "includes/defines.h"
#include "includes/assinaturas.h"
#include "includes/exemplos.h"



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

void exe_3_6(int argc, char **argv){

	ssize_t n;
	int N = 1024; // reservar 1 MB para o buffer
	int field;
	int linha = 1; // nº da linha
	int linha_2 = 1;
	int initFix = 1;
	int lastLinha_2fix = 0;
	char num[13]; // string que contem o numero da linha
	char newLine = '\n';
	char *bufAnt2 = malloc(N);
	char *bufAnt = malloc(N); // criar o buffer com os 1MB
	char *bufAtual = malloc(N);

	if (argc <= 1) field = 0;  
	else field = open(argv[1], O_RDONLY, ALL_PERMI);

	if (field == -1){
		perror("erro ao ler ficheiro");
		exit(-1);
	}

	while( (n = readln(field, bufAtual, N)) > 0){

		if (strcmp(bufAtual, bufAnt) == 0){ //caso seja igual ao anterior imprime a linha_2

			imprimeLinha(&linha_2, num, initFix, 2);
			write(1, &newLine, 1);
			lastLinha_2fix = 1;
		}

		else{
			
			if (lastLinha_2fix) imprimeLinha(&linha_2, num, initFix, 2);
			if (!initFix) write(1, &newLine, 1);
			linha_2 = 1;
			lastLinha_2fix = 0;	
		}

		imprimeLinha(&linha, num, initFix, 1);
		write(1, bufAtual, n); // escreve a linha do ficheiro no terminal
		initFix = 0;

		strcpy(bufAnt2, bufAnt);
		strcpy(bufAnt, bufAtual);
	}

	if (strcmp(bufAnt2, bufAnt) == 0) imprimeLinha(&linha_2, num, initFix, 2); //buf Fix (caso houvesse repetição na ultima linha) 
	
	write(1, &newLine, 1);
}

void imprimeLinha(int *linha, char* num, int initFix, int v){

	int len;
	char space = ' ';

	if (v == 2) write(1, &space, 1);
	sprintf(num, "%d ", *linha); // coloca o nº da linha numa string
	for (len = 0; num[len]; len++); // determina a dimensao dessa string
	write(1, num, len * sizeof(char)); //escreve essa string no terminal
	*linha = *linha + 1;
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


int main(int argc, char **argv){	

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
				exe_3_6(argc, argv);
				break;

			default:
				perror("nao existe essa alinea");
				exit(-1);
		}	

	}

	else if (exe == 4){

		switch(alinea){

			case 1:
				exe_4_1(argc, argv);
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

