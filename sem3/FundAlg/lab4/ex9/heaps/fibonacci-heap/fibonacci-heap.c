#include "fibonacci-heap.h"

error_msg create_fibonacci_node(FibonacciNode** fibonacciNode, Application* application) {
	if (fibonacciNode == NULL) {
		return (error_msg){INCORRECT_ARG_FUNCTION, "create_fibonacci_node", "get pointer to null"};
	}
	FibonacciNode* tmp = (FibonacciNode*)calloc(1, sizeof(FibonacciNode));
	if (!tmp) {
		return (error_msg){MEMORY_ALLOCATED_ERROR, "create_fibonacci_node", "memory allocated in object"};
	}
	tmp->application = application;
	*fibonacciNode = tmp;
	return (error_msg){SUCCESS, "", ""};
}

error_msg copy_fibonacci_node(FibonacciNode* src, FibonacciNode** dst) {
	if (src == NULL || dst == NULL) {
		return (error_msg){INCORRECT_ARG_FUNCTION, " copy_fibonacci_node", "get pointer to null"};
	}
	Application* tmp;
	error_msg errorMsg = copy_application_new(src->application, &tmp);
	if (errorMsg.type) {
		return errorMsg;
	}

	errorMsg = create_fibonacci_node(dst, tmp);
	if (errorMsg.type) {
		destroy_application(tmp);
		return errorMsg;
	}

	return (error_msg){SUCCESS, "", ""};
}

void destroy_fibonacci_node(FibonacciNode* fibonacciNode) {
	destroy_application(fibonacciNode->application);
	fibonacciNode->child = NULL;
	fibonacciNode->left = NULL;
	fibonacciNode->parent = NULL;
	fibonacciNode->right = NULL;
	free(fibonacciNode);
}

error_msg create_fibonacci_heap(FibonacciHeap** fibonacciHeap) {
	if (fibonacciHeap == NULL) {
		return (error_msg){INCORRECT_ARG_FUNCTION, "create_fibonacci_heap", "get pointer to null"};
	}
	FibonacciHeap* tmp = (FibonacciHeap*)calloc(1, sizeof(FibonacciHeap));
	if (!tmp) {
		return (error_msg){MEMORY_ALLOCATED_ERROR, "create_fibonacci_heap", "memory allocated in object"};
	}
	*fibonacciHeap = tmp;
	return (error_msg){SUCCESS, "", ""};
}


error_msg insert_fibonacci_heap(FibonacciHeap* fibonacciHeap, Application* application) {
	FibonacciNode* new;
	error_msg errorMsg = create_fibonacci_node(&new, application);
	if (errorMsg.type) {
		return errorMsg;
	}
	if (fibonacciHeap->size == 0) {
		fibonacciHeap->size = 1;
		fibonacciHeap->head = new;
		new->right = new;
		new->left = new;
		return (error_msg){SUCCESS, "", ""};
	}
	FibonacciNode* prev_right = fibonacciHeap->head->right;
	fibonacciHeap->head->right = new;
	new->left = fibonacciHeap->head;
	new->right = prev_right;
	prev_right->left = new;

	if (new->application->priority > fibonacciHeap->head->application->priority) {
		fibonacciHeap->head = new;
	}
	fibonacciHeap->size += 1;
	return (error_msg){SUCCESS, "", ""};
}

Application* find_max_priority_element_fibonacci_heap(const FibonacciHeap* fibonacciHeap) {
	if (fibonacciHeap == NULL) {
		return NULL;
	}
	return fibonacciHeap->head->application;
}

error_msg copy_sub_heap(FibonacciNode * src, FibonacciNode ** dst){
	if(src == NULL){
		return (error_msg){SUCCESS, "", ""};
	}

	FibonacciNode * new;
	error_msg errorMsg = copy_fibonacci_node(src, &new);
	if(errorMsg.type){
		return errorMsg;
	}
// TODO
}

error_msg copy_fibonacci_heap(FibonacciHeap * src, FibonacciHeap ** dst){
	if(src == NULL || dst == NULL){
		return (error_msg){INCORRECT_ARG_FUNCTION, "copy_fibonacci_heap", "get pointer to null"};
	}

	FibonacciHeap * tmp;
	error_msg errorMsg = create_fibonacci_heap(&tmp);
	if(errorMsg.type){
		return errorMsg;
	}

	if (src->size == 0) {
		*dst = tmp;
		return (error_msg){SUCCESS, "", ""};
	}

	FibonacciNode * cur_src = src->head;
	FibonacciNode * cur_dst = NULL;

	do {
		errorMsg = copy_fibonacci_node(cur_src, &cur_src);
		if(errorMsg.type){
			destroy_fibonacci_heap(tmp);
			return errorMsg;
		}

		cur_src = cur_src->right;
	} while (cur_src != src->head);
}

void destroy_subheap(FibonacciNode* node) {
	if (node == NULL) return;

	FibonacciNode* current = node;
	do {
		FibonacciNode* next = current->right;
		destroy_subheap(current->child);
		destroy_fibonacci_node(current);
		current = next;
	} while (current != node);
}

error_msg destroy_fibonacci_heap(FibonacciHeap* heap) {
	if (heap == NULL) {
		return (error_msg){INCORRECT_ARG_FUNCTION, "destroy_fibonacci_heap", "get pointer to null"};
	}
	destroy_subheap(heap->head);
	heap->head = NULL;
	heap->size = 0;
	free(heap);
	return (error_msg){SUCCESS, "", ""};
}


error_msg merge_fibonacci_heap_with_destroy(FibonacciHeap* first, FibonacciHeap* second, FibonacciHeap** result) {
	if (first == NULL || second == NULL || result == NULL) {
		return (error_msg){INCORRECT_ARG_FUNCTION, "merge_fibonacci_heap_with_destroy", "get pointer to null"};
	}

	if (first == second) {
		return (error_msg){INCORRECT_ARG_FUNCTION, "merge_fibonacci_heap_with_destroy", "merge by itself"};
	}

	FibonacciHeap* tmp;
	error_msg errorMsg = create_fibonacci_heap(&tmp);
	if (errorMsg.type) {
		return errorMsg;
	}
	if (second->size == 0) {
		tmp->size = first->size;
		tmp->head = first->head;
		first->size = 0;
		*result = tmp;
		free(first);
		free(second);
		return (error_msg){SUCCESS, "", ""};
	}

	if (first->size == 0) {
		tmp->size = second->size;
		tmp->head = second->head;
		second->size = 0;
		*result = tmp;
		free(first);
		free(second);
		return (error_msg){SUCCESS, "", ""};
	}

	FibonacciNode* left = first->head->left;
	FibonacciNode* right = second->head->right;
	second->head->right = first->head;
	first->head->left = second->head;
	left->right = right;
	right->left = left;
	tmp->size = first->size + second->size;
	tmp->head = first->head;
	if (first->head->application->priority < second->head->application->priority) {
		tmp->head = second->head;
	}
	*result = tmp;
	return (error_msg){SUCCESS, "", ""};
}