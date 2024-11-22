#include "ex6.h"


int main(){
	Vector a(12, 5);

	std::cout << a << std::endl;

	a.insert(15, -1);
	a[3] = 12;
	std::cout << a << std::endl;

	a.erase(3);

	std::cout << a;


	return 0;
}