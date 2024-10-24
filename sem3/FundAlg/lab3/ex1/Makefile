FLAGS = -Wall -Wextra -Werror -g -lm -lcheck -lsubunit -lrt -lpthread -lerrors -L../lib
COMP = gcc

ex10: test.c
	$(COMP) test.c ex1.c -o ex1.a $(FLAGS) `pkg-config --cflags --libs check`


test:
	@./ex1.a

clean:
	rm *.a
