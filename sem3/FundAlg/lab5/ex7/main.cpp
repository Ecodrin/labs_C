#include "ex7.h"


int main(){
	Date d{12125};
	Date s{12124};
	std::cout << d << std::endl;
	std::cout << s << std::endl;
	std::cout << (d <=> s) << std::endl;



}