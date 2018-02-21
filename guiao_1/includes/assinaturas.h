#ifndef ASSINATURAS_H
#define ASSINATURAS_H

typedef struct buffer_t{

	size_t size;
	int lastLine; // posição da ultima linha processada
	void *buf;
	int field;

} *p_buffer_t;

void exemplo_1();
void exemplo_2();
void exemplo_3();
void exemplo_4();
void exemplo_5();
void exemplo_6();

void exe_3_1();
void exe_3_2(const char **argv);
void exe_3_3(const char **argv);
void exe_3_4(const char **argv);
void exe_3_5();
void exe_3_6(int argc, const char **argv);
void exe_3_7(const char **argv);

void exe_4_1(int argc, const char **argv);
void exe_4_6(int argc, const char **argv);

ssize_t readln(int fildes, void *buf, size_t nbyte);
int convertStringToInt(const char *str);
void imprimeLinha(int *linha_2, int initFix, int v);

int create_buffer(int filedes, struct buffer_t *buffer, size_t nbyte);
int destroy_buffer(struct buffer_t *buffer);
ssize_t readln_2(struct buffer_t *bufer, void **buf);

#endif