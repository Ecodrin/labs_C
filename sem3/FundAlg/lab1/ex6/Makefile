
FLAGS=-Wall -Wextra -g -c
FLAGSMAIN = -Wall -Wextra -g
COMP = clang


ex5: main.c
	$(COMP) ex6.c -c
	$(COMP) main.c ex6.o -lm -o ex6.exe
	./ex6.exe 0.0001
	rm ex6.o
