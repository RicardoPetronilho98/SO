#ifndef GUIAO_2_H
#define GUIAO_2_H

/*
	API a usar neste guiao:

	pid_t getpid(void);
	pid_t getppid(void);
	pid_t fork(void);
	void _exit(int status);
	pid_t wait(int *status);
	pid_t waitpid(pid_t pid, int *status, int options);
	int WIFEXITED(int status); 
	int WEXITSTATUS(int status); 
*/

void printInt(int n);
void exe_3_1(void);

#endif