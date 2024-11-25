#include "heaps.h"

V_table heaps_functions[] = {{create_binary, insert_binary, delete_binary, merge_binary_with_destroy,
                              merge_binary_without_destroy, destroy_binary, find_max_priority_elem_binary},
                             {create_binomial, insert_binomial, delete_binomial, merge_binomial_with_destroy,
                              merge_binomial_without_destroy, destroy_binomial, find_max_priority_elem_binomial}};

error_msg create_binary(Q_queue **queue) {
	if (queue == NULL) {
		return (error_msg){INCORRECT_ARG_FUNCTION, "create_binary", "get pointer to null"};
	}
	BinaryHeap *binaryHeap = &((*queue)->bin_h);
	error_msg errorMsg = create_binary_heap(&binaryHeap);
	*queue = (Q_queue *)binaryHeap;
	return errorMsg;
}

error_msg insert_binary(Q_queue *queue, Application *application) {
	if (queue == NULL) {
		return (error_msg){INCORRECT_ARG_FUNCTION, "insert_binary", "get pointer to null"};
	}
	return insert_binary_heap(&(queue->bin_h), application);
}

error_msg destroy_binary(Q_queue *queue) {
	if (queue == NULL) {
		return (error_msg){INCORRECT_ARG_FUNCTION, "destroy_binary", "get pointer to null"};
	}
	return destroy_binary_heap(&(queue->bin_h));
}

error_msg delete_binary(Q_queue *queue, Application **result) {
	if (queue == NULL) {
		return (error_msg){INCORRECT_ARG_FUNCTION, "delete_binary", "get pointer to null"};
	}
	return delete_binary_heap(&(queue->bin_h), result);
}

error_msg merge_binary_without_destroy(Q_queue *first, Q_queue *second, Q_queue **result) {
	if (first == NULL || second == NULL || result == NULL) {
		return (error_msg){INCORRECT_ARG_FUNCTION, "merge_binary_without_destroy", "get pointer to null"};
	}

	BinaryHeap *res = &((*result)->bin_h);
	error_msg errorMsg = merge_binary_heaps_without_destroy(&(first->bin_h), &(second->bin_h), &res);
	*result = (Q_queue *)res;
	return errorMsg;
}

error_msg merge_binary_with_destroy(Q_queue *first, Q_queue *second, Q_queue **result) {
	if (first == NULL || second == NULL || result == NULL) {
		return (error_msg){INCORRECT_ARG_FUNCTION, "merge_binary_with_destroy", "get pointer to null"};
	}
	BinaryHeap *res = &((*result)->bin_h);
	error_msg errorMsg = merge_binary_heaps_with_destroy(&(first->bin_h), &(second->bin_h), &res);
	*result = (Q_queue *)res;
	return errorMsg;
}

Application *find_max_priority_elem_binary(const Q_queue *queue) {
	if (queue == NULL) {
		return NULL;
	}
	return find_max_priority_elem_binary_heap(&(queue->bin_h));
}

error_msg create_binomial(Q_queue **queue) {
	if (queue == NULL) {
		return (error_msg){INCORRECT_ARG_FUNCTION, "create_binomial", "get pointer to null"};
	}
	BinomialHeap *binomialHeap = &((*queue)->binomial_h);
	error_msg errorMsg = create_binomial_heap(&binomialHeap);
	*queue = (Q_queue *)binomialHeap;
	return errorMsg;
}

error_msg insert_binomial(Q_queue *queue, Application *application) {
	if (queue == NULL) {
		return (error_msg){INCORRECT_ARG_FUNCTION, "insert_binomial", "get pointer to null"};
	}
	return insert_binomial_heap(&(queue->binomial_h), application);
}

error_msg delete_binomial(Q_queue *queue, Application **result) {
	if (queue == NULL) {
		return (error_msg){INCORRECT_ARG_FUNCTION, "delete_binomial", "get pointer to null"};
	}
	return delete_binomial_heap(&(queue->binomial_h), result);
}

error_msg merge_binomial_with_destroy(Q_queue *first, Q_queue *second, Q_queue **result) {
	if (first == NULL || second == NULL || result == NULL) {
		return (error_msg){INCORRECT_ARG_FUNCTION, "merge_binomial_with_destroy", "get pointer to null"};
	}
	BinomialHeap *res = &((*result)->binomial_h);
	error_msg errorMsg = merge_binomial_heap_with_destroy(&(first->binomial_h), &(second->binomial_h), &res);
	*result = (Q_queue *)res;
	return errorMsg;
}
error_msg merge_binomial_without_destroy(Q_queue *first, Q_queue *second, Q_queue **result) {
	if (first == NULL || second == NULL || result == NULL) {
		return (error_msg){INCORRECT_ARG_FUNCTION, "merge_binomial_without_destroy", "get pointer to null"};
	}
	BinomialHeap *res = &((*result)->binomial_h);
	error_msg errorMsg = merge_binomial_heap_without_destroy(&(first->binomial_h), &(second->binomial_h), &res);
	*result = (Q_queue *)res;
	return errorMsg;
}

Application *find_max_priority_elem_binomial(const Q_queue *queue) {
	if (queue == NULL) {
		return NULL;
	}
	return find_max_priority_elem_binomial_heap(&(queue->binomial_h));
}

error_msg destroy_binomial(Q_queue *queue) {
	if (queue == NULL) {
		return (error_msg){INCORRECT_ARG_FUNCTION, "destroy_binomial", "get pointer to null"};
	}
	return destroy_binomial_heap(&(queue->binomial_h));
}
