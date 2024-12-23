COMP = gcc
CFLAGS = -fsanitize=address -g -Wall -Wextra
DIN_FLAGS = -fPIC -shared
LIB_FLAGS = -L. -lerrors

all: al1 al2
	$(COMP) $(CFLAGS) main.c $(LIB_FLAGS) -ldl -o main

main:
	$(COMP) $(CFLAGS) main.c $(LIB_FLAGS) -ldl -o main

al1:
	$(COMP) $(CFLAGS) $(DIN_FLAGS) free-blocks-allocators/free-block-allocator.c -o libfree-block-allocator.so

al2:
	$(COMP) $(CFLAGS) $(DIN_FLAGS) mccusIcarels-algorithm/mccusIcarels-algorithm.c -o libmccusIcarels-algorithm.so


clean:
	rm -f main
	rm -f *.so
