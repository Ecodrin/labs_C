COMP = gcc
FLAGS = -c -Wall -Wextra -Werror


comp:
	$(COMP) $(FLAGS) errors.c
	ar cr liberrors_2.a errors.o
	mv liberrors_2.a ../
	rm *.o
