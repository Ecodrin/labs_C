#ifndef LAB3_EX5_H
#define LAB3_EX5_H

#include <memory.h>
#include <stdio.h>
#include <stdlib.h>

#include "../lib/SystemErrors/errors.h"
#include "../lib/vector/charvector.h"
#include "../lib/vector/intvector.h"

typedef struct Student {
	unsigned int id;
	String name;
	String last_name;
	String group;
	unsigned char* grades;
} Student;

typedef struct Students {
	Student* students;
	int count_students;
	int capacity_students;
} Students;

error_msg GetPaths(int argc, char** argv, const char** path1, const char** path2);

int check_student_id(Students* students, Student* student);
error_msg create_student(Student* student);
void destroy_student(Student* student);
int read_student(FILE* stream, Student* student);
void print_student(FILE* stream, Student* student);
error_msg read_students(FILE* stream, Students* students);
void print_students(FILE* stream, Students* students);
void destroy_students(Students* students);
void clear_student(Student* student);

// Поиск
int find_student_by_id(Students* students, unsigned int id);
int find_students_by_last_name(Students* students, IntVector* vec, String* last_name);
int find_students_by_name(Students* students, IntVector* vec, String* name);
int find_students_by_group(Students* students, IntVector* vec, String* group);

// Сортировка
void sort_by_id(Students * students);
void sort_by_name(Students * students);
void sort_by_last_name(Students * students);
void sort_by_group(Students * students);


// Comp
int compare_by_id(const void * a, const void * b);
int compare_by_name(const void * a, const void * b);
int compare_by_last_name(const void * a, const void * b);
int compare_by_group(const void * a, const void * b);


// Средний балл
int filter_students_by_average_score(Students * students, IntVector * result);
double calculate_average_score_students(Students * students);
double calculate_average_score_student(Student * student);

void clear_buffer();
#endif  // LAB3_EX5_H
