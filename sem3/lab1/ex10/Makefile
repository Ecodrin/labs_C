FLAGS=-Wall -Wextra -g -c
FLAGSMAIN = -Wall -Wextra -g
COMP = gcc



ex10: main.c
	gcc $(FLAGSMAIN) main.c charvector.o -lm -o ex10.exe
	valgrind --leak-check=full ./ex10.exe < test