
FLAGS=-Wall -Wextra -g -c
FLAGSMAIN = -Wall -Wextra -g
COMP = gcc


ex7: main.c
	$(COMP) ex7.c -c 
	$(COMP) main.c ex7.o -lm -o ex7.exe
#   Меняем флаги и пути внизу
	./ex7.exe -a ../text ../text2
	rm ex7.o