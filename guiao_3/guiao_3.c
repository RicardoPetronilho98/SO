#include <unistd.h>     /* chamadas ao sistema: defs e decls essenciais */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


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
	
	int i;
	int v = 0;
	int count = 1;
	int len = strlen(cmd);
	char *r = malloc( sizeof(char) * len );
	memcpy(r, cmd, len * sizeof(char) );
	
	for(i = 0; r[i]; i++) 
		if (r[i] == ' ') 
			count++;

	char **strList = malloc( sizeof(char*) * count);
	strList[v++] = r;

	for (i = 0; r[i]; i++){
		
		if (r[i] == ' '){
			r[i] = '\0'; // sem esta linha cada apontador mostrava a string toda desde o inicio
			strList[v++] = r + i + 1; 
		}
	}

	printf("strList[0] = %s\n", strList[0]);
	printf("strList[1] = %s\n", strList[1]);

	execvp(strList[0], strList);
}


int main(int argc, char **argv){

	//exe_3_1();
	//exe_3_2();
	//exe_3_4(argv);
	//exe_3_5(argc, argv);
	exe_3_6("ls -l");

	return 0;
}