
FLAGS=-Wall -Wextra -g -c
FLAGSMAIN = -Wall -Wextra -g
COMP = gcc


ex9: main.c
	$(COMP) ex9.c $(FLAGS)
	$(COMP) ../vector/intvector.c $(FLAGS)
	$(COMP) main.c ex9.o intvector.o -lm -o ex9.exe $(FLAGSMAIN)
	valgrind --leak-check=full ./ex9.exe 1 10 > test
	rm ex9.o