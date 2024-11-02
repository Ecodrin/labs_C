CFLAGS = -Wall -Wextra -g -lm -std=c99
LIBS_FLAG = -lerrors -lvector -lmstring -L../lib

COMP = gcc


ex10: main.c
	$(COMP) $(CFLAGS) main.c ex8.c -o ex8.a $(LIBS_FLAG)
	valgrind --leak-check=full --show-leak-kinds=all ./ex8.a test test
	rm *a

