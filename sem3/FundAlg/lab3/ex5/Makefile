CFLAGS = -Wall -Wextra -Werror -g -lm -std=c99
LIBS_FLAG = -lerrors -lvector -lmstring -L../lib

COMP = gcc


ex5: main.c
	$(COMP) $(CFLAGS) main.c ex5.c -o ex5.a $(LIBS_FLAG)
	valgrind --leak-check=full --show-leak-kinds=all ./ex5.a test test2
	rm *a

