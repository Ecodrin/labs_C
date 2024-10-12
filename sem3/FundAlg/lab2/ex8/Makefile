FLAGS = -Wall -Wextra -g -lm
COMP = gcc

ex8: main.c
	$(COMP) $(FLAGS) main.c ../SystemErrors/errors.c ../vector/charvector.c ../vector/stringvector.c ex8.c -o ex8.exe
	valgrind ./ex8.exe
