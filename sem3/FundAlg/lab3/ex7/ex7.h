#ifndef LAB3_EX7_H
#define LAB3_EX7_H

#include <stdlib.h>

#include "../lib/SystemErrors/errors.h"
#include "../lib/vector/charvector.h"

typedef struct Date {
	unsigned int day;
	unsigned int month;
	unsigned int year;
} Date;

typedef struct Liver {
	String last_name;
	String name;
	String patronymic;
	Date birthday;
	char gender;
	double income;
} Liver;

typedef struct Node {
	struct Node* next;
	Liver data;
} Node;

typedef struct SpecialNode{
/*
 * 0 - удаление
 * 1 - вставка
 * 2 - изменение
 */
	Liver liver;
	int instruction;
	struct SpecialNode * next;
}SpecialNode;

// Функции для односвязного John Smith 15списка
error_msg create_node(Node** node, Liver data);
void destroy_node(Node ** head);
void delete_node(Node* prev, Node* cur);
void destroy_LinkedList(Node* head);
void add_node(Node* prev, Node* cur);
error_msg push_node_end(Node** head, Liver data);
error_msg push_node_start(Node** head, Liver data);
Node* find_node_by_index(Node* head, int index);
error_msg push_node_in_correct_order(Node ** head, Liver * cur);
void print_LinkedList(FILE* stream, Node* head, char* separator);

// Функции для специального односвязного списка(по сути стэк)
error_msg create_special_node(SpecialNode** node, Liver data, int instruction);
void destroy_special_node(SpecialNode ** head);
void destroy_LinkedList_with_special_node(SpecialNode * head);
error_msg push_special_node_start(SpecialNode ** head, Liver data, int instruction);

error_msg read_livers_from_file(FILE* in, Node** head);
int eq_livers(Liver * l1, Liver* l2);
void print_liver(FILE * stream, Liver * liver);
int read_liver(FILE* stream, Liver* liver);
error_msg create_liver(Liver* liver);
error_msg delete_liver(Node ** head, Liver * liver);
error_msg copy_liver(const Liver * dst, Liver * src);
Node * find(Node ** head, Liver * liver);
error_msg change_liver(Node ** head, Liver * liver, Liver * new_liver);
void destroy_liver(Liver * liver);

unsigned int DayInMonth(unsigned int month, unsigned int year);
int IsCorrectDate(Date* time);
int BiggerDate(Date* t1, Date* t2);

void clear_buffer();

int IsCorrectNameLastName(String *s);



#endif  // LAB3_EX7_H
