#include <unistd.h>     /* chamadas ao sistema: defs e decls essenciais */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define KB		1024

void exe_3_1(){

	execlp("ls", "cenas", "-l", (char*) NULL);
}


void exe_3_2(){

	pid_t p;
	int status;

	if ( (p = fork()) == -1){

		perror("fork error");
		_exit(1);
	}

	if (p == 0){

		execlp("ls", "cenas", "-l", (char*) NULL);
		perror("Erro no execlp\n");
		_exit(1);
	}

	else wait(&status);
}


void exe_3_4(char **argv){

	memcpy(argv[1], "abc", 3 * sizeof(char) );
	execv("exe_3_3", argv);
}


void exe_3_5(int argc, char **argv){

	int i;
	pid_t p;
	int status;

	for(i = 1; i < argc; i++){

		if ( (p = fork()) == -1){

			perror("fork error");
			_exit(1);
		}

		if (p == 0){ 

			execlp(argv[i], "iuasiuhfiuashiuhu", (char*) NULL);
			_exit(0);
		}

	}

	for (i = 1; i < argc; i++) wait(&status);
}


void exe_3_6(const char *cmd){
	
	int i, v = 0;
	int count = 2; //contador de comandos (pelo menos: o primeiro comando e NULL)
	
	int len = strlen(cmd);
	char *r = malloc( sizeof(char) * len );
	memcpy(r, cmd, len * sizeof(char) ); 
	
	for(i = 0; r[i]; i++) // contador do número de comandos e/ou argumentos dados
		if (r[i] == ' ') 
			count++;

	char **strList = malloc( sizeof(char*) * count);
	strList[v++] = r;
	strList[count - 1] = (char*) NULL;

	for (i = 0; r[i]; i++)
		if (r[i] == ' '){
			r[i] = '\0'; // sem esta linha cada apontador mostrava a string toda desde o inicio
			strList[v++] = r + i + 1; 
		}

	// para debug: 
	// for (i = 0; i < count; i++)
	// 	printf("strList[%d] = %s\n", i, strList[i]);
	
	execvp(strList[0], strList);
}


char* getShortPath(const char *path){

	int i, r, len;

	for(len = i = 0; path[i]; i++, len++){
		if (path[i] == '/'){
			r = i;
			len = 0;
		}
	}

	r++;

	char *shortPath = malloc( sizeof(char) * len);
	memcpy(shortPath, path + r, len * sizeof(char) );

	return shortPath;
}


void printBashLogo(){

	char *currentPath = malloc (KB);
	char *bashLogo1 = "SO_É_FIXE:";
	write(1, bashLogo1, strlen(bashLogo1) * sizeof(char));
	char *bashLogo2 = getShortPath( getcwd(currentPath, KB) );
	write(1, bashLogo2, strlen(bashLogo2) * sizeof(char));
	write(1, " ", sizeof(char));
	char *bashLogo3 = getlogin();
	write(1, bashLogo3, strlen(bashLogo3) * sizeof(char));
	write(1, "$ ", 2 * sizeof(char));
}


void printWelcomeMessage(){

	write(1, "\n", sizeof(char));
	char *underscore = "---------------------------------------------------------------------\n";
	write(1, underscore, strlen(underscore) * sizeof(char));
	char *welcome1 = "                       Hello ";
	write(1, welcome1, strlen(welcome1) * sizeof(char));
	char *welcome2 = getlogin();
	write(1, welcome2, strlen(welcome2) * sizeof(char));
	char *welcome4 = "\n                      this is your new bash now\n";
	write(1, welcome4, strlen(welcome4) * sizeof(char));
	char *welcome5 = "                        I'm watching you <3 :)\n";
	write(1, welcome5, strlen(welcome5) * sizeof(char));
	write(1, underscore, strlen(underscore) * sizeof(char));
	write(1, "\n", sizeof(char));
}


void exe_3_7(){

	void *buf = malloc( KB ); // 1 KB para o buffer
	ssize_t n;
	pid_t p;
	int status;

	printWelcomeMessage();

	while(1){
		
		printBashLogo();

		n = read(0, buf, KB);

		// ctrl-D ou exit
		if ( n <= 0 || (n == 5 && memcmp("exit", buf, 4 * sizeof(char)) == 0) ){ 
			
			char *str = "[Process completed]\nI hope I see you soon! - program ended by user\n";
			write( 1, str, sizeof(char) * strlen(str) );
			_exit(0);
		}

		// remover o '\n' no fim
		*( (char*) buf + n - 1) = '\0';

		/*
		man 3 exec
		The exec family of functions replaces the current process image with a new process image.
		
		nota IMPORTANTE:

		como as funções exec() substituem o processo atual pelo novo,
		temos de criar um processo filho, evocar a exec() nesse processo 
		caso contrário perdiamos o executável atual e o programa acabava
		*/

		if ( (p = fork()) == -1){

			perror("fork error");
			_exit(1);
		}

		if (p == 0){ 

			exe_3_6( (const char*) buf );
			_exit(0);
		}

		else{ 
			// o pai (o interpretador) espera pelo fim da execução do comando atual
			wait(&status);
		}
	}
}


int main(int argc, char **argv){

	//exe_3_1();
	//exe_3_2();
	//exe_3_4(argv);
	//exe_3_5(argc, argv);
	//exe_3_6("ls -l");
	exe_3_7();

	// para correr o programa --> make && ./guiao_3

	return 0;
}



























