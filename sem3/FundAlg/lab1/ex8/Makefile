
FLAGS=-Wall -Wextra -g -c
FLAGSMAIN = -Wall -Wextra -g
COMP = gcc
EXE = valgrind --leak-check=full 


ex8: main.c
	$(COMP) ex8.c $(FLAGS)
	$(COMP) main.c ex8.o -lm -o ex8.exe $(FLAGSMAIN)
#   Меняем флаги и пути внизу
	$(EXE) ./ex8.exe text sd
	rm ex8.o