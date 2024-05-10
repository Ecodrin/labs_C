all:
	g++ -o main.exe main.cpp
	for number in 1 2 3 4 5 6 7 8 ; do \
  		./main.exe test$$number.txt answer$$number.txt ; \
  	done
	rm main.exe

del:
	rm answer*.txt