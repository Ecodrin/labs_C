


all:
	g++ -c table.cpp
	g++ main.cpp table.o
	./a.out test
	rm ./a.out
	rm table.o

val:
	g++ -c table.cpp
	g++ -Wall -Wextra -g main.cpp table.o
	valgrind ./a.out test
	rm ./a.out
	rm table.o