FLAGS = -Wall -Wextra -Werror -g -lm -lcheck -lsubunit -lrt -lpthread -lerrors -L../lib
COMP = gcc

ex10: main.c
	$(COMP) main.c ex1.c test.c -o ex1.a $(FLAGS) `pkg-config --cflags --libs check`