
FLAGS=-Wall -Wextra -g -c
FLAGSMAIN = -Wall -Wextra -g
COMP = clang

ex1: main.c
	$(COMP) $(FLAGS) vector/intvector.c
	$(COMP) $(FLAGS) ex1/ex1.c
	$(COMP) $(FLAGSMAIN) main.c intvector.o ex1.o -lm -o ex1.exe
#   Меняем флаги и цифру внизу
	valgrind ./ex1.exe -s 123
	rm ex1.exe 
	rm intvector.o
	rm ex1.o


ex2: main.c
	$(COMP) ex2/ex2.c -c
	$(COMP) main.c ex2.o -lm -o ex2.exe
	./ex2.exe 
	rm ex2.exe
	rm ex2.o

