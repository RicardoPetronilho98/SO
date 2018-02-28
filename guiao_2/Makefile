#execute: compile
#	./guiao_2

compile: clear
	gcc -Wall guiao_2.c -o guiao_2

clear: 
	clear

clean: 
	rm -r latex html hello.txt file.txt file2.txt file3.txt guiao_1 helloWorld.txt arrayA.txt 

doc:
	doxygen

git: git_commit
	git push origin master

git_commit: git_add
	git commit -m "auto-commit"

git_add: 
	git add *





