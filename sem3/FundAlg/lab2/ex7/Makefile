FLAGS = -Wall -Wextra -g -lm
COMP = gcc

ex5: main.c
	$(COMP) $(FLAGS) main.c ../SystemErrors/errors.c ex7.c -o ex7.exe
	valgrind ./ex7.exe
