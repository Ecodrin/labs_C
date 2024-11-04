CFLAGS = -Wall -Wextra -g -lm -std=c99
LIBS_FLAG = -lerrors -lmstring -lvector -L../lib
TEST_FLAGS = -lcheck -lsubunit -lrt -lpthread `pkg-config --cflags --libs check`

COMP = gcc

ex7: main.c
	$(COMP) $(CFLAGS) main.c ex7.c -o ex7.a $(LIBS_FLAG)
	valgrind --leak-check=full --show-leak-kinds=all ./ex7.a
	rm *a