CFLAGS = -Wall -Wextra -g -lm -std=c99
LIBS_FLAG = -lerrors -lmstring -lvector -L../lib
TEST_FLAGS = -lcheck -lsubunit -lrt -lpthread `pkg-config --cflags --libs check`

COMP = gcc


ex10: main.c
	$(COMP) $(CFLAGS) main.c ex8.c -o ex8.a $(LIBS_FLAG)
	valgrind --leak-check=full --show-leak-kinds=all ./ex8.a test test
	rm *a


tt: test.c
	$(COMP) test.c ex8.c -o ex8.a $(LIBS_FLAG) $(TEST_FLAGS)
	./ex8.a

