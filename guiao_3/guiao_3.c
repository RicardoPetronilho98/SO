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

		if (p == 0){ //

			execlp(argv[i], "iuasiuhfiuashiuhu", (char*) NULL);
			_exit(0);
		}

	}

	for (i = 1; i < argc; i++) wait(&status);
}


int main(int argc, char **argv){

	//exe_3_1();
	//exe_3_2();
	//exe_3_4(argv);
	exe_3_5(argc, argv);

	return 0;
}