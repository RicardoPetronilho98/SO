#execute: compile
#	./guiao_2

compile: clear
	gcc -Wall guiao_4.c -o guiao_4

clear: 
	clear

clean: 
	rm -r guiao_4 output.txt error.txt

doc:
	doxygen

git: git_commit
	git push origin master

git_commit: git_add
	git commit -m "auto-commit"

git_add: 
	git add *





