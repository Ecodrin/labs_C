
/*
 * описание интерфейса взаимодействия кучами
 */

#pragma once

#include "../application/application.h"
#include "binary-heap/binary-heap.h"
#include "binomial-heap/binomial-heap.h"
#include "fibonacci-heap/fibonacci-heap.h"
#include "leftist-heap/leftist-heap.h"
#include "skew-heap/skew-heap.h"

typedef union Q_queue {
	BinaryHeap bin_h;
	BinomialHeap binomial_h;
	FibonacciHeap fibonacci_h;
	SkewHeap skew_h;
	LeftistHeap leftist_h;
} Q_queue;

typedef struct V_table {
	error_msg (*create_heap)(Q_queue **);
	error_msg (*insert_heap)(Q_queue *, Application *);
	error_msg (*delete_heap)(Q_queue *, Application **);
	error_msg (*merge_heap_with_destroy)(Q_queue *, Q_queue *, Q_queue **);
	error_msg (*merge_heap_without_destroy)(Q_queue *, Q_queue *, Q_queue **);
	error_msg (*destroy_heap)(Q_queue *);
	Application *(*find_max_priority_elem)(const Q_queue *);
} V_table_queue;

typedef struct Queue {
	Q_queue *q;
	V_table_queue v;
} Queue;

extern V_table_queue heaps_functions[];

// Binary heap
error_msg create_binary(Q_queue **queue);
error_msg insert_binary(Q_queue *queue, Application *application);
error_msg delete_binary(Q_queue *queue, Application **result);
error_msg merge_binary_with_destroy(Q_queue *first, Q_queue *second, Q_queue **result);
error_msg merge_binary_without_destroy(Q_queue *first, Q_queue *second, Q_queue **result);
Application *find_max_priority_elem_binary(const Q_queue *queue);
error_msg destroy_binary(Q_queue *queue);

// Binomial heap
error_msg create_binomial(Q_queue ** queue);
error_msg insert_binomial(Q_queue * queue, Application * application);
error_msg delete_binomial(Q_queue * queue, Application ** result);
error_msg merge_binomial_with_destroy(Q_queue * first, Q_queue * second, Q_queue ** result);
error_msg merge_binomial_without_destroy(Q_queue * first, Q_queue * second, Q_queue ** result);
Application *find_max_priority_elem_binomial(const Q_queue *queue);
error_msg destroy_binomial(Q_queue *queue);

// Fibonacci heap
error_msg create_fibonacci(Q_queue **queue);
error_msg insert_fibonacci(Q_queue *queue, Application *application);
error_msg delete_fibonacci(Q_queue *queue, Application **result);
error_msg merge_fibonacci_with_destroy(Q_queue * first, Q_queue * second, Q_queue ** result);
error_msg merge_fibonacci_without_destroy(Q_queue * first, Q_queue * second, Q_queue ** result);
Application *find_max_priority_elem_fibonacci(const Q_queue *queue);
error_msg destroy_fibonacci(Q_queue* queue);

// Skew heap
error_msg create_skew(Q_queue **queue);
error_msg insert_skew(Q_queue *queue, Application *application);
error_msg delete_skew(Q_queue *queue, Application **result);
error_msg merge_skew_with_destroy(Q_queue *first, Q_queue *second, Q_queue **result);
error_msg merge_skew_without_destroy(Q_queue *first, Q_queue *second, Q_queue **result);
Application *find_max_priority_elem_skew(const Q_queue *queue);
error_msg destroy_skew(Q_queue *queue);

// Leftist heap
error_msg create_leftist(Q_queue ** queue);
error_msg insert_leftist(Q_queue * queue, Application * application);
error_msg delete_leftist(Q_queue * queue, Application ** result);
error_msg merge_leftist_with_destroy(Q_queue * first, Q_queue * second, Q_queue ** result);
error_msg merge_leftist_without_destroy(Q_queue *first, Q_queue *second, Q_queue **result);
Application * find_max_priority_elem_leftist(const Q_queue * queue);
error_msg destroy_leftist(Q_queue * queue);