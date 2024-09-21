
FLAGS=-Wall -Wextra -g -c
FLAGSMAIN = -Wall -Wextra -g
COMP = gcc


ex4: main.c
	$(COMP) ex7.c -c 
	$(COMP) main.c ex7.o -lm -o ex7.exe
#   Меняем флаги и пути внизу
	./ex7.exe -r ../text2 ../text s
	rm ex7.o