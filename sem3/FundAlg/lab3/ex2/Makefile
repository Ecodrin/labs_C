FLAGS = -Wall -Wextra -Werror -g -lm -lcheck -lsubunit -lrt -lpthread -lerrors -L../lib
COMP = gcc
LIBFLAGS = -lerrors -L../lib


test_val: main.c
	$(COMP) main.c ex2.c -o ex2.a $(LIBFLAGS) -Wall -Wextra -g -Werror -lm
	valgrind --leak-check=full ./ex2.a
	rm ex2.a



clean:
	rm *.a
