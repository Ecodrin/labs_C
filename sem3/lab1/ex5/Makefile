
FLAGS=-Wall -Wextra -g -c
FLAGSMAIN = -Wall -Wextra -g
COMP = gcc


ex5: main.c
	$(COMP) ex5.c $(FLAGS)
	$(COMP) main.c ex5.o -lm -o ex5.exe $(FLAGSMAIN)
	rm ex5.o
