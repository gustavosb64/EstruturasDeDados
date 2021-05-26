all:
	gcc -g -o main main.c parceiros_de_trabalho.c

run:
	./main

debug:
	valgrind --leak-check=full --show-leak-kinds=all ./main
