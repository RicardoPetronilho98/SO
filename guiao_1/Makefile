execute: compile
	./guiao_1 file.txt file2.txt

#./guiao_1 /Users/ricardopetronilho/Desktop/SO/guiao_1/file.txt /Users/ricardopetronilho/Desktop/SO/guiao_1/file2.txt
compile: clear
	gcc -Wall guiao_1.c -o guiao_1

clear: 
	clear

clean: 
	rm hello.txt file3.txt guiao_1 helloWorld.txt arrayA.txt

git: git_commit
	git push origin master --force

git_commit: git_add
	git commit -m "auto-commit"

git_add: 
	git add *





