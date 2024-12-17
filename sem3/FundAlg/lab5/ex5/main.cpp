#include <iostream>



int main(){
	int b = 3;
	int &&a = 212;
	printf("%d", *((char*)&a));
}