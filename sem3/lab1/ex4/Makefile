
FLAGS=-Wall -Wextra -g -c
FLAGSMAIN = -Wall -Wextra -g
COMP = clang


ex4: main.c
	$(COMP) ex4.c -c
	$(COMP) main.c ex4.o -lm -o ex4.exe
#   Меняем флаги и пути внизу
	./ex4.exe -ns ../text sadfsdf
	rm ex4.exe
	rm ex4.o