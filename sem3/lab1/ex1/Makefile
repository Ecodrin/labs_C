
FLAGS=-Wall -Wextra -g -c
FLAGSMAIN = -Wall -Wextra -g
COMP = clang

ex1: main.c
	$(COMP) ../vector/intvector.c -c
	$(COMP) ex1.c -c
	$(COMP) main.c intvector.o ex1.o -lm -o ex1.exe
#   Меняем флаги и числа внизу
	./ex1.exe 50 -f
	rm ex1.exe 
	rm intvector.o
	rm ex1.o

