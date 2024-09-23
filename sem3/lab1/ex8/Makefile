
FLAGS=-Wall -Wextra -g -c
FLAGSMAIN = -Wall -Wextra -g
COMP = gcc


ex8: main.c
	$(COMP) ex8.c $(FLAGS)
	$(COMP) main.c ex8.o -lm -o ex8.exe $(FLAGSMAIN)
#   Меняем флаги и пути внизу
	rm ex8.o