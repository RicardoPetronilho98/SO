execute: compile
	./guiao_1 /Users/ricardopetronilho/Desktop/SO/file.txt 

compile: clear
	gcc -Wall guiao_1.c -o guiao_1

clear: 
	clear


