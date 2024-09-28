
FLAGS=-Wall -Wextra -g -c
FLAGSMAIN = -Wall -Wextra -g
COMP = gcc


ex4: main.c
	$(COMP) ex4.c $(FLAGS)
	$(COMP) ../vector/intvector.c $(FLAGS)
	$(COMP) main.c ex4.o intvector.o -lm -o ex4.exe $(FLAGSMAIN)
#   Меняем флаги и пути внизу
	rm ex4.o