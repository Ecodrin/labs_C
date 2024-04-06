

test_1:
	g++ main.cpp
	./a.out < test1
	rm ./a.out
	
	

test_2:
	g++ main.cpp
	./a.out < test2
	rm ./a.out



val_test1:
	g++ -Wall -Wextra -g main.cpp
	valgrind ./a.out < test1
	rm ./a.out
	
val_test2:
	g++ -Wall -Wextra -g main.cpp
	valgrind ./a.out < test2
	rm ./a.out	
