CFLAGS = -Wall -Wextra -Werror -g -lm -lcheck -lsubunit -lrt -lpthread -lerrors -lmstring -lvector -L../lib/ -std=c99
COMP = gcc

ex4: test.c
	$(COMP) test.c $(CFLAGS) -o ex4.a `pkg-config --cflags --libs check`

test_val:
	$(COMP) main.c -Wall -Wextra -Werror -g -lm -lerrors -lmstring -lvector -L../lib/ -std=c99
	valgrind ./a.out
	rm ./a.out