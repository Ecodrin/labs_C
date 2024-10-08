
FLAGS=-Wall -Wextra -g -c
FLAGSMAIN = -Wall -Wextra -g
COMP = clang


ex3: main.c
	$(COMP) ex3.c -c
	$(COMP) main.c ex3.o -lm -o ex3.exe
#   Меняем флаги и числа внизу
	./ex3.exe -q 0.0001 0 23.1 2.1
	./ex3.exe -m -28 23
	./ex3.exe -t 0.0001 3 4 5
	rm ex3.o
