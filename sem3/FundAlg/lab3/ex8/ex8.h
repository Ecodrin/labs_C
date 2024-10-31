#ifndef LAB3_EX8_H
#define LAB3_EX8_H

#include <stdlib.h>

#include "../lib/SystemErrors/errors.h"
#include "../lib/vector/charvector.h"

typedef struct Node {
	struct Node* next;
	int data;
} Node;

typedef struct Polynomial {
	Node* coefficients;
	int degree;
} Polynomial;

// Функции для односвязного списка
error_msg create_node(Node** node, int data);
void delete_node(Node* prev, Node* cur);
void destroy_LinkedList(Node* head);
void add_node(Node* prev, Node* cur);
Node* find_node(Node* head, int data);
error_msg push_node(Node** head, int data);
void print_LinkedList(FILE* stream, Node* head, char* separator);

// Функции для многочлена
error_msg create_polynomial(Polynomial** polynomial);
void destroy_polynomial(Polynomial* polynomial);
error_msg read_polynomial_from_string(Polynomial* polynomial, String* string);
#endif  // LAB3_EX8_H
