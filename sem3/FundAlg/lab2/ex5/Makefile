FLAGS = -Wall -Wextra -g -lm
COMP = gcc

ex5: main.c
	$(COMP) $(FLAGS) main.c ../SystemErrors/errors.c  ../vector/stringvector.c ../vector/charvector.c overloads.c -o ex5.exe
	valgrind ./ex5.exe
