
FLAGS=-Wall -Wextra -g -c
FLAGSMAIN = -Wall -Wextra -g
COMP = clang


ex5: main.c
	$(COMP) ex5.c -c
	$(COMP) main.c ex5.o -lm -o ex5.exe
	./ex5.exe 0.0001 1 > test
	rm ex5.exe 
	rm ex5.o
