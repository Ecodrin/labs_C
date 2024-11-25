
#ifndef LAB4_BINOMIAL_HEAP_H
#define LAB4_BINOMIAL_HEAP_H

#include "../../../lib2/SystemErrors2/errors.h"
#include "../../application/application.h"

typedef struct BinomialNode {
	Application* application;
	struct BinomialNode* parent;
	struct BinomialNode* child;
	struct BinomialNode* brother;
	size_t degree;
} BinomialNode;

typedef struct BinomialHeap {
	BinomialNode* head;
	size_t size;
} BinomialHeap;

// Функции для узлов
error_msg create_binomial_node(BinomialNode** binomialNode, Application* application);
error_msg copy_binomial_node_new(BinomialNode* src, BinomialNode** dst);
void destroy_binomial_node(BinomialNode* binomialNode);

// Функции для кучи
error_msg create_binomial_heap(BinomialHeap** binomialHeap);
error_msg merge_binomial_heap_with_destroy(BinomialHeap* first, BinomialHeap* second, BinomialHeap** result);
error_msg merge_binomial_heap_without_destroy(BinomialHeap* first, BinomialHeap* second, BinomialHeap** result);
error_msg copy_binomial_heap_new(const BinomialHeap* src, BinomialHeap** dst);
error_msg insert_binomial_heap(BinomialHeap* binomialHeap, Application* application);
error_msg delete_binomial_heap(BinomialHeap* binomialHeap, Application** application);
Application* find_max_priority_elem_binomial_heap(const BinomialHeap* binaryHeap);
error_msg destroy_binomial_heap(BinomialHeap* binomialHeap);

#endif  // LAB4_BINOMIAL_HEAP_H
