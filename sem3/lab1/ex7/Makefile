
FLAGS=-Wall -Wextra -g -c
FLAGSMAIN = -Wall -Wextra -g
COMP = gcc


ex7: main.c
	$(COMP) ex7.c $(FLAGS)
	$(COMP) main.c ex7.o -lm -o ex7.exe $(FLAGSMAIN)
#   Меняем флаги и пути внизу
	rm ex7.o