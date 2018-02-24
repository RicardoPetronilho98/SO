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


void exe_3_2(const char **argv){

	char c = 'a';
	int n, f;

	//f é o file descriptor
	f = open(argv[1], O_WRONLY | O_CREAT, ALL_OWNER_PERMI);

	for (n = 0; n < MB; n++)
		write (f, &c, 1); // vai escrever no ficheiro apontado por f, caracter a caracter 

	close(f);
	exit(n);
}


int convertStringToInt(const char *str){

	int n = 0;
	int i;

	int dim = strlen(str);

	for (i = dim - 1; i >= 0; i--) 
		n += (str[dim - i - 1] - '0') * pow (10, i);

	return n;
}


void exe_3_3(const char **argv){ 

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


void exe_3_4(const char **argv){

	exe_3_3(argv);
}


ssize_t readln(int fildes, void *buf, size_t nbyte){

	// copyright: José Pereira

	int n, i = 0;

	while(i < nbyte){

		n = read(fildes, (char *) buf + i, sizeof(char));
		//                >>> n <<< ??
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
	
	int N = KB; // reservar 1KB bytes para o buffer
	int *buf = malloc(N); // criar o buffer com os 64 bytes

	n = readln(0, buf, N); // le uma linha do terminal e retorna o tamanho

	write(1, buf, n + 1); // escreve essa mesma linha para testar se esta correto
}


void exe_3_6_vDIFICIL(int argc, const char **argv){
    
    int N = KB; // 1KB - memória reservada para o buffer
    int field;
    int len;
    int linha_1 = 1;
    int linha_2 = 1;
    int fixLastLinha_2 = 0;
    ssize_t n1;
    ssize_t n2;
    char *buf = malloc(N);
    char *bufNext = malloc(N);
    char *num = malloc(NUM_SIZE * sizeof(char)); // string que contem o numero da linha
    char newLine = '\n';
    char tab = 9;
    
    if ( (field = open(argv[1], O_RDONLY, ALL_PERMI)) == -1){ //ler do ficheiro
        perror("impossível ler ficheiro");
        exit(-1);
    }
    
   	n1 = readln(field, buf, N);
    
    while(n1){ //o que interessa é que o n1 (dimensão do buf) contenha informação para escrita
        
        n2 = readln(field, bufNext, N);
        
        sprintf(num, "%d ", linha_1); // coloca o nº da linha_1 numa string
        for (len = 0; num[len]; len++); // determina a dimensao dessa string
        write(1, &tab, sizeof(char));
        write(1, num, len * sizeof(char)); //escreve essa string (nº da linha_1) no terminal
        write(1, buf, n1);
        
        if ( strcmp(buf, bufNext) == 0 && n2){ //n2 garante que a ultima linha caso nao entre em BUG
            
            fixLastLinha_2 = 1;
            
            loop: //isto aqui foi so para nao escrever 2 vezes coisas muito semelhantes...
                sprintf(num, " %d", linha_2); // coloca o nº da linha_2 numa string
                for (len = 0; num[len]; len++); // determina a dimensao dessa string
                write(1, num, len * sizeof(char)); //escreve essa string (nº da linha_2) no terminal
                linha_2++;
                if (fixLastLinha_2 == 0) linha_2 = 1; //neste ponto ja passou no goto
        }else{
            
            if (fixLastLinha_2 == 1) { // Correção do bug de ultima repetição não ser numerada
                fixLastLinha_2 = 0;
                goto loop;
            }
        }
        
        
        write(1, &newLine, sizeof(char));
        linha_1++;
        strcpy(buf, bufNext);
        n1 = n2;
    }
    
    free(num);
    free(buf);
    free(bufNext);
}


void exe_3_6_vFACIL(int argc, const char **argv){
    
    ssize_t n;
    int N = KB, field, len, linha = 1;
    char *buf = malloc(N), *num = malloc(NUM_SIZE * sizeof(char)); // string que contem o numero da linha
    char newLine = '\n';
    int maxSpaces = 6;
    
    if (argc <= 1) field = 0; // ler do terminal
    else if ( (field = open(argv[1], O_RDONLY, ALL_PERMI)) == -1){ //ler do ficheiro
        perror("impossível ler ficheiro");
        exit(-1);
    }
    
    while( (n = readln(field, buf, N) ) > 0) { 
        
        sprintf(num, "%d  ", linha); // coloca o nº da linha numa string
        for (len = 0; num[len]; len++); // determina a dimensao dessa string
		alignSpaces(maxSpaces, len - 2);
        write(1, num, len * sizeof(char)); //escreve essa string (nº da linha) no terminal
        write(1, buf, n); 
        write(1, &newLine, sizeof(char));
        linha++;
    }
    
    free(num);
    free(buf);
}


int create_buffer(int filedes, struct buffer_t *buffer, size_t nbyte){
    
    if (buffer == NULL){
        perror("could not CREATE buffer_t because its memory is not allocated");
        exit(20);
    }
    
    buffer->size = nbyte;
    buffer->buf = malloc ( buffer->size * sizeof(char) );
    buffer->field = filedes;
    buffer->lastLine = 0;

    return 0;
}


int destroy_buffer(struct buffer_t *buffer){

	if (buffer == NULL){
        perror("could not DESTROY buffer_t because its memory is not allocated");
        exit(20);
    }
    
    free(buffer->buf); //e preciso isto??
    free(buffer);
    
    return 0;
}

// por o perror caso a memoria do buffer seja insuficiente
ssize_t readln_2(struct buffer_t *buffer, void **buf){

	int i, lineSize;
	size_t n;

	/* caso o buffer estaja vazio (ou a sua informação esteja totalmente utilizada)
	   lê novamente buffer->size bytes de informação e coloca no buffer->buf
	*/
	if (buffer->lastLine == 0){
		n = read(buffer->field, buf, buffer->size); 
	}

	// deteta a posição do '\n' (para saber até onde se imprime a linha)
	for (i = buffer->lastLine; ((char*)buf)[i] != '\n' && i != buffer->size; i++);

	// se entrar neste if singifica que o buffer não tem memória para conter uma única linha
	if (i == buffer->size && buffer->lastLine == 0){
		perror("Memoria reservada para o buffer insuficiente.\nNo mínimo o buffer tem de ter espaço para conter uma única linha.\nSugestão - reservar 10 KB ou mais para o buffer");
		exit(30);
	}
 
	// singifica que chegou ao fim do buffer mas não encontrou uma nova linha ('\n')
	if ( ((char*)buf)[i] != '\n' && i == buffer->size){
		perror("fim do buffer sem NOVA LINHA encontrada");
		exit(50);
	}

	// buffer->line aponta para o inicio da linha a ser impressa
	buffer->line = buf + buffer->lastLine;
	
	// dimensão da nova linha a ser impressa
	lineSize = i - buffer->lastLine;

	// atualiza o posição da nova linha
	buffer->lastLine = i;

	//if (buffer->lastLine == )

	return lineSize;
}


void exe_3_7(const char **argv){

	p_buffer_t buffer = (p_buffer_t) malloc( sizeof(struct buffer_t) ); 

	//size_t nbyte = KB * 10; // 10 KB
	size_t nbyte = 6;
	ssize_t n;
	int field = open(argv[1], O_RDONLY, S_IRUSR);
	char newLine = '\n';
	char num[12];
	int debug;

	create_buffer(field, buffer, nbyte);

	debug = 2;
	
	while(debug){ // para debugging

		n = readln_2(buffer, buffer->buf);

		write(1, buffer->line, n);
		write(1, &newLine, sizeof(char) );
		sprintf(num, "%zd", n); 
	    printf("Dimensao da linha = %zd\n", n); // para debugging
	    debug--;
	}

	destroy_buffer(buffer);
}


void exe_3_8(int argc, const char **argv){
    
    p_buffer_t buffer = (p_buffer_t) malloc( sizeof(struct buffer_t) ); // pointer to buffer_t
    ssize_t n;
    //size_t nbyte = KB * 10; // 10 KB
    size_t nbyte = 30;
    int field = open(argv[1], O_RDONLY);   
    int len;
    int linha = 1;
    char *num = malloc( NUM_SIZE * sizeof(char) ); // string que contem o numero da linha
    char newLine = '\n';
    char tab = 9;

    create_buffer(field, buffer, nbyte);
        
    while( (n = readln_2(buffer, buffer->buf) ) > 0 && linha < 30){

	    sprintf(num, "%d ", linha); // coloca o nº da linha_1 numa string
	    for (len = 0; num[len]; len++); // determina a dimensao dessa string
	    write(1, &tab, sizeof(char));
	    write(1, num, len * sizeof(char)); //escreve essa string (nº da linha_1) no terminal
	    write(1, buffer->line, n);
	    write(1, &newLine, sizeof(char) );
	    linha++;
    }
    
    free(num);
    destroy_buffer(buffer);
}


void exe_4_1(int argc, const char **argv){

	int i, f, n;
	int buffSize = KB * 2; // 2 KB
	char *buf = malloc(buffSize);
	char c = '\n';

	if (argc < 2){
		perror("file was not specified");
		exit(200);
	}
	
	for (i = 1; i < argc; i++){

		if ( (f = open(argv[i], O_RDONLY, ALL_PERMI)) == -1 ){
			perror("could not open file ");
			exit(f);
		}

		while ( (n = readln(f, buf, buffSize)) > 0){

			write(1, buf, n); // escreve o conteudo do ficheiro no terminal
			write(1, &c, 1); // new line entre cada ficehiro
		}

		close(f);
	}
}


void exe_4_3(int argc, const char **argv){

	// clear && ./guiao_1 -3 /Users/ricardopetronilho/Desktop/SO/guiao_1/file.txt /Users/ricardopetronilho/Desktop/SO/guiao_1/file2.txt

	int n, f, i;
	int buffSize = KB * 2;
	int setasSize = 4;
	int linhaParaImprimir; 
	int linha;
	char c = '\n';
	char setaDir[] = "==> ";
	char setaEsq[] = " <==";
	char *buf = malloc(buffSize); 

	if (argc < 2){
		perror("file was not specified");
		exit(1);
	}

	if (argv[1][0] == '-'){
		i = 2; // significa que a linha foi especificada
		linhaParaImprimir = convertStringToInt(argv[1] + 1);
	}
	else{
		i = 1;
		linha = 10; // por omissão lê 10 linhas
	}

	
	for ( ; i < argc; i++){

		linha = linhaParaImprimir;

		if ( (f = open(argv[i], O_RDONLY, ALL_PERMI)) == -1 ){
			perror("could not open file ");
			exit(f);
		}

		for (n = 0; argv[i][n]; n++);

		write(1, setaDir, setasSize);
		write(1, argv[i], n * sizeof(char) );
		write(1, setaEsq, setasSize); 
		write(1, &c, 1); 

		while ( (n = readln(f, buf, buffSize)) > 0 && linha){

			write(1, buf, n); // escreve o conteudo do ficheiro no terminal
			write(1, &c, 1); // new line entre cada ficehiro
			linha--;
		}

		close(f);
	}

	free(buf);
}


void exe_4_4(int argc, const char **argv){
	
	int n, f, i; 
	int len;
	int buffSize = KB * 2;
	char c = '\n';
	char *buf = malloc(buffSize); 
	char doisPontos = ':';

	if (argc < 3){
		perror("file or word is not specified");
		exit(1);
	}

	for (i = 2; i < argc; i++){

		if ( (f = open(argv[i], O_RDONLY, ALL_PERMI)) == -1 ){
			perror("could not open file ");
			exit(f);
		}

		for (len = 0; argv[i][len]; len++);

		while ( (n = readln(f, buf, buffSize)) > 0){

			if ( strstr(buf, argv[1]) != NULL){

				write(1, argv[i], len * sizeof(char) );
				write(1, &doisPontos, sizeof(char));
				write(1, buf, n * sizeof(char) ); // escreve o conteudo do ficheiro no terminal
				write(1, &c, 1); // new line entre cada ficehiro
			}
		}

		close(f);
	}

	free(buf);	
}


int wordsInString(char *str, int N){

	int i, count = 0;

	for (i = 0; str[i] && N; i++, N--)
		if (str[i] == ' ') count++;

	return count;
}


void alignSpaces(int N, int len){

	int i;
	char space = ' ';

	for(i = 0; i < N - len; i++) 
		write(1, &space, sizeof(char));
}


void exe_4_5(int argc, const char **argv){

	int n, f, i, len;
	int lines, words, chars;
	int Tlines = 0, Twords = 0, Tchars = 0;
	int buffSize = KB * 2;
	char c = '\n';
	char space = ' ';
	char *buf = malloc(buffSize); 
	char num[12];
	int maxSpaces = 8;

	if (argc < 2){
		perror("file not specified");
		exit(1);
	}

	for (i = 1; i < argc; i++){ // para cada ficheiro

		if ( (f = open(argv[i], O_RDONLY)) == -1 ){
			perror("could not open file ");
			exit(f);
		}

		lines = words = chars = 0; // para cada ficheiro os contadores começam a 0 

		while ( (n = readln(f, buf, buffSize)) > 0){

			words += wordsInString(buf, n) + 1;
			lines++;
			chars += n + 1;
		}

		if (buf[words + lines] != '\n') { // words + lines (nº de caracteres do ficheiro)
			//este if acontece quando o ficheiro NÃO acaba com '\n' - buf fix
			lines--;
			chars--;
		}

		Twords += words; // total de todos os ficheiros
		Tlines += lines;
		Tchars += chars;

		sprintf(num, "%d", lines);
		for(len = 0; num[len]; len++);
		alignSpaces(maxSpaces, len);
		write(1, num, sizeof(char) * len);

		sprintf(num, "%d", words);
		for(len = 0; num[len]; len++);
		alignSpaces(maxSpaces, len);
		write(1, num, sizeof(char) * len);

		sprintf(num, "%d", chars);
		for(len = 0; num[len]; len++);
		alignSpaces(maxSpaces, len);
		write(1, num, sizeof(char) * len);

		write(1, &space, sizeof(char));
		for(len = 0; argv[i][len]; len++);
		write(1, argv[i], len * sizeof(char) );
		write(1, &c, 1); // new line entre cada ficehiro

		close(f);
	}

	sprintf(num, "%d", Tlines);
	for(len = 0; num[len]; len++);
	alignSpaces(maxSpaces, len);
	write(1, num, sizeof(char) * len);

	sprintf(num, "%d", Twords);
	for(len = 0; num[len]; len++);
	alignSpaces(maxSpaces, len);
	write(1, num, sizeof(char) * len);

	sprintf(num, "%d", Tchars);
	for(len = 0; num[len]; len++);
	alignSpaces(maxSpaces, len);
	write(1, num, sizeof(char) * len);

	write(1, &space, sizeof(char));
	write(1, "total", 5 * sizeof(char) );
	write(1, &c, 1); // new line entre cada ficehiro

	free(buf);	
}


void exe_4_6(int argc, const char **argv){

	int f1, f2, n1, n2;
	char c1, c2;
	char newLine = '\n';
	int count = 0, lines = 0, len;
	char str[1024];

	if (argc < 2){
		perror("não foram passados ficheiros suficientes como argumento");
		exit(40);
	}

	if ( (f1 = open(argv[1], O_RDONLY, ALL_PERMI)) == -1){
		perror("não foi possivel abrir o ficheiro 1");
		exit(30);
	}
	
	if ( (f2 = open(argv[2], O_RDONLY, ALL_PERMI)) == -1){
		perror("não foi possivel abrir o ficheiro 2");
		exit(30);
	}

	while ( (n1 = read(f1, &c1, sizeof(char)) ) > 0 
		 && (n2 = read(f2, &c2, sizeof(char)) ) > 0 ){
		
		if (c1 == c2) count++;
		if (c1 == '\n' && c2 == '\n') lines++; 
	}

	lines++;
	
	sprintf(str, "%s %s differ: char %d, line %d", argv[1], argv[2], count, lines);
	for (len = 0; str[len]; len++);

	if ( !(c1 == c2) ) write(1, str, len * sizeof(char) );

	write(1, &newLine, 1);
}


int main(int argc, const char **argv){	

	int exe = 3;
	int alinea = 7; 

	int exemplo = 6; // exemplos contidos em /includes/exemplos.h

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
				//exe_3_6_vDIFICIL(argc, argv); //apenas lê do ficheiro
				exe_3_6_vFACIL(argc, argv); 
				break;

			case 7:
				exe_3_7(argv);
				break;

			case 8:
				exe_3_8(argc, argv);
				break;

			default:
				perror("exe 3 ---> nao existe essa alinea");
				exit(-1);
		}	

	} else if (exe == 4){

		switch(alinea){

			case 1:
				exe_4_1(argc, argv);
				break;

			case 3:
				exe_4_3(argc, argv);
				break;

			case 4:
				exe_4_4(argc, argv);
				break;

			case 5:
				exe_4_5(argc, argv);
				break;

			case 6:
				exe_4_6(argc, argv);
				break;

			default:
				perror("exe 4 ---> nao existe essa alinea");
				exit(-1);
		} 
	}

	else arr[exemplo - 1]();

	return 0;
}