FLAGS = -Wall -Wextra -Werror -g -lm -lcheck -lsubunit -lrt -lpthread -lerrors -L../lib
COMP = gcc

ex10: main.c
	$(COMP) main.c ex2.c test.c -o ex2.a $(FLAGS) `pkg-config --cflags --libs check`


test:
	@./ex2.a

clean:
	rm *.a
