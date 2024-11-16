
CFLAGS = -pthread -g -fsanitize=thread -o game
COMP = clang

game: main.c
	$(COMP) $(CFLAGS) main.c utility/utility.c utility/functions.c SystemErrors/errors.c
#	time ./game 8 22 33 44 55 67
#	rm game

