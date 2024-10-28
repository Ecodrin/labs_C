FLAGS = -Wall -Wextra -Werror -g -lm -lcheck -lsubunit -lrt -lpthread -lerrors -L../lib
COMP = gcc
LIBFLAGS = -lerrors -L../lib

ex10:
	$(COMP) test.c ex2.c test.c -o ex2.a $(FLAGS) `pkg-config --cflags --libs check`

test_val: main.c
	$(COMP) main.c ex2.c -o ex2.a $(LIBFLAGS) -Wall -Wextra -g -Werror -lm
	valgrind --leak-check=full ./ex2.a
	rm ex2.a



clean:
	rm *.a
