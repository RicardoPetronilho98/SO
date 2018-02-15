execute: compile
	./guiao_1 /Users/ricardopetronilho/Desktop/SO/file.txt 

compile: clear
	gcc -Wall guiao_1.c -o guiao_1

clear: 
	clear

git:
	git add * && git commit -m "auto-commit" && git push origin master

clean:
	rm hello.txt file.txt file2.txt


