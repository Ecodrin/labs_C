CFLAGS_TEST = -Wall -Wextra -Werror -g -lm -lcheck -lsubunit -lrt -lpthread -lerrors -lmstring -lvector -L../lib/ -std=c99 -fsanitize=address
CFLAGS = -Wall -Wextra -Werror -g -lm -std=c99
LIBS_FLAG = -lerrors -lvector -lmstring -L../lib

COMP = gcc

ex4_string: test.c
	@$(COMP) test.c $(CFLAGS) $(LIBS_FLAG) -o ex4.a `pkg-config --cflags --libs check`

post: main.c
	@$(COMP) $(CFLAGS) main.c mail.c -o ex4_2.a $(LIBS_FLAG)
	valgrind --leak-check=full ./ex4_2.a
	rm *a


test_val:
	$(COMP) main.c -Wall -Wextra -Werror -g -lm -lerrors -lmstring -lvector -L../lib/ -std=c99
	valgrind ./a.out
	rm ./a.out