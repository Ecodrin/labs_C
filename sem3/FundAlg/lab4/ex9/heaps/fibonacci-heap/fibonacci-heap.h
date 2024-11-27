#pragma once

#include <stdlib.h>

#include "../../../lib2/SystemErrors2/errors.h"
#include "../../application/application.h"

typedef struct FibonacciNode {
	Application * application;
	size_t degree;
	struct FibonacciNode * right;
	struct FibonacciNode * left;
	struct FibonacciNode * parent;
	struct FibonacciNode * child;
} FibonacciNode;


typedef struct FibonacciHeap{
	size_t size;
	FibonacciNode * head;
} FibonacciHeap;

// Функции для кучи
error_msg create_fibonacci_heap(FibonacciHeap ** fibonacciHeap);
error_msg insert_fibonacci_heap(FibonacciHeap * fibonacciHeap, Application * application);
// Удаление
Application * find_max_priority_element_fibonacci_heap(const FibonacciHeap * fibonacciHeap);
// Слияние с разрушением
error_msg merge_fibonacci_heap_with_destroy(FibonacciHeap * first, FibonacciHeap * second, FibonacciHeap ** result);
error_msg destroy_fibonacci_heap(FibonacciHeap* heap);



