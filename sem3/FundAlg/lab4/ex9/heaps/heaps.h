
/*
 * описание интерфейса взаимодействия кучами
 */

#pragma once

#include "../application/application.h"
#include "binary-heap/binary-heap.h"
#include "binomial-heap/binomial-heap.h"
#include "fibonacci-heap/fibonacci-heap.h"

typedef union Q_queue {
	BinaryHeap bin_h;
	BinomialHeap binomial_h;
} Q_queue;

typedef struct V_table {
	error_msg (*create_heap)(Q_queue **);
	error_msg (*insert_heap)(Q_queue *, Application *);
	error_msg (*delete_heap)(Q_queue *, Application **);
	error_msg (*merge_heap_with_destroy)(Q_queue *, Q_queue *, Q_queue **);
	error_msg (*merge_heap_without_destroy)(Q_queue *, Q_queue *, Q_queue **);
	error_msg (*destroy_heap)(Q_queue *);
	Application *(*find_max_priority_elem)(const Q_queue *);
} V_table;

typedef struct Queue {
	Q_queue *q;
	V_table v;
} Queue;

extern V_table heaps_functions[];

// Бинарная куча
error_msg create_binary(Q_queue **queue);
error_msg insert_binary(Q_queue *queue, Application *application);
error_msg delete_binary(Q_queue *queue, Application **result);
error_msg merge_binary_with_destroy(Q_queue *first, Q_queue *second, Q_queue **result);
error_msg merge_binary_without_destroy(Q_queue *first, Q_queue *second, Q_queue **result);
Application *find_max_priority_elem_binary(const Q_queue *queue);
error_msg destroy_binary(Q_queue *queue);


// Биноминальная куча
error_msg create_binomial(Q_queue ** queue);
error_msg insert_binomial(Q_queue * queue, Application * application);
error_msg delete_binomial(Q_queue * queue, Application ** result);
error_msg merge_binomial_with_destroy(Q_queue * first, Q_queue * second, Q_queue ** result);
error_msg merge_binomial_without_destroy(Q_queue * first, Q_queue * second, Q_queue ** result);
Application *find_max_priority_elem_binomial(const Q_queue *queue);
error_msg destroy_binomial(Q_queue *queue);
