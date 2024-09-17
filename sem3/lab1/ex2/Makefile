
FLAGS=-Wall -Wextra -g -c
FLAGSMAIN = -Wall -Wextra -g
COMP = clang


ex2: main.c
	$(COMP) ex2.c -c
	$(COMP) main.c ex2.o -lm -o ex2.exe
	./ex2.exe 0.001
	rm ex2.exe
	rm ex2.o
