FLAGS = -Wall -Wextra -g -lm
COMP = gcc

ex9: main.c
	$(COMP) $(FLAGS) main.c ../SystemErrors/errors.c ex9.c -o ex9.exe
	valgrind ./ex9.exe
