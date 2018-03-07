#execute: compile
#	./guiao_2

compile: clear
	gcc -Wall exe_3_3.c -o exe_3_3 && gcc -Wall guiao_3.c -o guiao_3

clear: 
	clear

clean: 
	rm -r latex html hello.txt file.txt file2.txt file3.txt guiao_3 helloWorld.txt arrayA.txt 

doc:
	doxygen

git: git_commit
	git push origin master

git_commit: git_add
	git commit -m "auto-commit"

git_add: 
	git add *





