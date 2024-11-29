COMP = gcc
CFLAGS = -std=c99 -Wall -Werror -Wextra -g -o ex9
LIB_FLAGS = -L../lib2 -lerrors2 -lvector2 -lmstring2 -lm
FILES = application/application.c heaps/heaps.c heaps/binary-heap/binary-heap.c heaps/binomial-heap/binomial-heap.c heaps/fibonacci-heap/fibonacci-heap.c heaps/skew-heap/skew-heap.c


ex2: main.c
	$(COMP) $(CFLAGS) main.c $(FILES) $(LIB_FLAGS)

val: ex2
	valgrind --leak-check=full ./ex9
	rm ex9
