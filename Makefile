all:
	gcc -o tysh_builtins.o -c tysh_builtins.c
	gcc -o tinyshell.o -c tinyshell.c 
	gcc -o tysh tysh_builtins.o tinyshell.o

run:
	./tysh
	 
