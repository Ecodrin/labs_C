#include "overloads.h"

int main(void) {
	overfprintf(stdout, "%%%d%Ro%1d%lld%Ro%mi%*d", 1, 1, 1, 1, 1, 1, 1);

}