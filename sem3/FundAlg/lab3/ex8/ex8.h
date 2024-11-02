#ifndef LAB3_EX8_H
#define LAB3_EX8_H

#include <limits.h>
#include <stdlib.h>

#include "../lib/SystemErrors/errors.h"
#include "../lib/vector/charvector.h"
#include "../lib/mstring/mstring.h"

typedef struct Node {
	struct Node* next;
	int data;
} Node;

typedef struct Polynomial {
	Node* coefficients;
	int degree;
} Polynomial;

#define max(a, b) (a > b) ? a : b

// Функции для односвязного списка
error_msg create_node(Node** node, int data);
void delete_node(Node* prev, Node* cur);
void destroy_LinkedList(Node* head);
void add_node(Node* prev, Node* cur);
Node* find_node(Node* head, int data);
error_msg push_node_end(Node** head, int data);
error_msg push_node_start(Node** head, int data);
Node * find_node_by_index(Node * head, int index);
void print_LinkedList(FILE* stream, Node* head, char* separator);


// Функции для многочлена
error_msg create_polynomial(Polynomial** polynomial);
void destroy_polynomial(Polynomial** polynomial);
error_msg copy_polynomial(Polynomial** dest, Polynomial ** src);
error_msg read_polynomial_from_string(Polynomial** polynomial, String* string);
void delete_leading_zeros(Polynomial * p);
void print_polynomial(FILE * stream, Polynomial* polynomial);
error_msg add_polynomials(Polynomial ** res, Polynomial * first, Polynomial * second);
error_msg subtract_polynomials(Polynomial** res, Polynomial * first, Polynomial * second);
error_msg product_polynomials(Polynomial ** result, Polynomial * first, Polynomial * second);
error_msg divide_polynomials(Polynomial ** quotient, Polynomial ** remainder, Polynomial * numerator, Polynomial * denominator);
int eval_polynomial(Polynomial * src, int x);
int diff_polynomial(Polynomial ** res, Polynomial *dst, int order);
error_msg composition_polynomials(Polynomial** res, Polynomial * first, Polynomial * second);



// Функции обработки файла
error_msg read_file_with_instruction(FILE * in, FILE * out);
error_msg read_command(FILE* stream, String* string, char separator);
#endif  // LAB3_EX8_H
