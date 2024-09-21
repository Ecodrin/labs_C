
FLAGS=-Wall -Wextra -g -c
FLAGSMAIN = -Wall -Wextra -g
COMP = clang

ex1: main.c
	$(COMP) ../vector/charvector.c -c
	$(COMP) ../vector/intvector.c -c
	$(COMP) ex1.c -c
	$(COMP) main.c charvector.o intvector.o ex1.o -lm -o ex1.exe
	rm charvector.o
	rm ex1.o
# 100 93326215443944152681699238856266700490715968264381621468592963895217599993229915608941463976156518286253697920827223758251185210916864000000000000000000000000
