
FLAGS=-Wall -Wextra -g -c
FLAGSMAIN = -Wall -Wextra -g
COMP = clang

ex1: main.c
	$(COMP) ../vector/intvector.c -c
	$(COMP) ex1.c -c
	$(COMP) main.c intvector.o ex1.o -lm -o ex1.exe
#   Меняем флаги и числа внизу
	valgrind ./ex1.exe -f 5
	rm ex1.exe 
	rm intvector.o
	rm ex1.o

