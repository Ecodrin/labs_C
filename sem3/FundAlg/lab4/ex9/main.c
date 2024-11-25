#include "heaps/heaps.h"

int main() {
	Queue q = {NULL, heaps_functions[1]};
	error_msg errorMsg = q.v.create_heap(&(q.q));
	if(errorMsg.type){
		return print_error(errorMsg);
	}


	q.v.destroy_heap(q.q);
	return 0;
}