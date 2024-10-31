#include "ex5.h"


int IsCorrectNameLastName(String * s){
	for(int i = 0;i < s->size; ++i){
		if(!((s->arr[i] >= 'a' && s->arr[i] <= 'z') ||(s->arr[i] >= 'A' && s->arr[i] <= 'Z'))){
			return 0;
		}
	}
	return 1;
}


error_msg create_student(Student *student) {
	error_msg errorMsg = create_string(&(student->name), "");
	if (errorMsg) {
		return errorMsg;
	}

	errorMsg = create_string(&(student->last_name), "");
	if (errorMsg) {
		destroy_string(&(student->name));
		return errorMsg;
	}

	errorMsg = create_string(&(student->group), "");
	if (errorMsg) {
		destroy_string(&(student->name));
		destroy_string(&(student->last_name));
		return errorMsg;
	}

	student->grades = (unsigned char *)malloc(sizeof(unsigned char) * 5);
	if (!student->grades) {
		destroy_string(&(student->name));
		destroy_string(&(student->last_name));
		destroy_string(&(student->group));
		return MEMORY_ALLOCATED_ERROR;
	}
	return SUCCESS;
}

void destroy_student(Student *student) {
	student->id = 0;
	destroy_string(&(student->name));
	destroy_string(&(student->last_name));
	destroy_string(&(student->group));
	free(student->grades);
}

int read_student(FILE *stream, Student *student) {
	int count_read = 0;
	if (!stream) {
		return INPUT_FILE_ERROR;
	}

	int n = fscanf(stream, "%u ", &(student->id));
	if (n <= 0) {
		return count_read;
	}
	count_read += 1;

	n = read_string(stream, &(student->name));
	if (n <= 0 || !IsCorrectNameLastName(&(student->name))) {
		return count_read;
	}
	count_read += 1;

	n = read_string(stream, &(student->last_name));
	if (n <= 0 || !IsCorrectNameLastName(&(student->last_name))) {
		return count_read;
	}
	count_read += 1;

	n = read_string(stream, &(student->group));
	if (n <= 0) {
		return count_read;
	}
	count_read += 1;

	for (int i = 0; i < 5; ++i) {
		if (feof(stream)) {
			return count_read;
		}
		student->grades[i] = getc(stream);
		if (i != 4) {
			getc(stream);
		}
		count_read += 1;
	}
//	student->grades[5] = '\0';
	return count_read;
}

void print_student(FILE *stream, Student *student) {
	fprintf(stream, "%u ", student->id);
	print_string(stream, &(student->name), "");
	putc(' ', stream);
	print_string(stream, &(student->last_name), "");
	putc(' ', stream);
	print_string(stream, &(student->group), "");
	for (int i = 0; i < 5; ++i) {
		fprintf(stream, " %c", student->grades[i]);
	}
	putc('\n', stream);
}

error_msg GetPaths(int argc, char **argv, const char **path1, const char **path2) {
	if (argc != 3) {
		return INCORRECT_OPTIONS_ERROR;
	}
	*path1 = argv[1];
	*path2 = argv[2];
	return SUCCESS;
}

error_msg read_students(FILE *stream, Students *students) {
	if (!stream) {
		return INPUT_FILE_ERROR;
	}

	students->capacity_students = 20;
	students->count_students = 0;
	students->students = (Student *)calloc(sizeof(Student), students->capacity_students);
	if (!students->students) {
		return MEMORY_ALLOCATED_ERROR;
	}

	int n;
	error_msg errorMsg;
	while (!feof(stream)){
		if(students->count_students == students->capacity_students){
			Student * tmp = (Student*)realloc(students->students, students->capacity_students * 2 * sizeof(Student));
			if(!tmp){
				destroy_students(students);
				return MEMORY_ALLOCATED_ERROR;
			}
			students->students = tmp;
			students->capacity_students *= 2;
		}

		errorMsg = create_student(&(students->students[students->count_students]));
		if(errorMsg){
			students->count_students += 1;
			destroy_students(students);
			return errorMsg;
		}

		n = read_student(stream, &(students->students[students->count_students]));
		if(n == 0 && feof(stream)){
			destroy_student(&(students->students[students->count_students]));
			return SUCCESS;
		}

		if(n != 9 || !check_student_id(students, &(students->students[students->count_students]))){
			destroy_student(&(students->students[students->count_students]));
			destroy_students(students);
			return INCORRECT_OPTIONS_ERROR;
		}

		students->count_students += 1;
	}

	return SUCCESS;
}

void print_students(FILE *stream, Students *students) {
	for (int i = 0; i < students->count_students; ++i) {
		print_student(stream, &(students->students[i]));
	}
}

void destroy_students(Students *students) {
	for (int i = 0; i < students->count_students; ++i) {
		destroy_student(&(students->students[i]));
	}
	free(students->students);
	students->count_students = 0;
	students->capacity_students = 0;
}

int check_student_id(Students *students, Student *student) {
	for (int i = 0; i < students->count_students; ++i) {
		if (student->id == students->students[i].id) {
			return 0;
		}
	}
	return 1;
}

void clear_student(Student *student) {
	student->name.size = 0;
	student->last_name.size = 0;
	student->group.size = 0;
}

int find_student_by_id(Students * students, unsigned int id){
	for(int i = 0; i < students->count_students; ++i){
		if(id == students->students[i].id){
			return i;
		}
	}
	return -1;
}

int find_students_by_last_name(Students * students, IntVector * vec, String * last_name){
	int count_students = 0;
	for(int i = 0; i < students->count_students; ++i){
		if(strings_equals(&(students->students[i].last_name), last_name)){
			count_students += 1;
			error_msg errorMsg = push_end_intvector(vec, i);
			if(errorMsg){
				return -1;
			}
		}
	}
	return count_students;
}


int find_students_by_name(Students * students, IntVector * vec, String * name){
	int count_students = 0;
	for(int i = 0; i < students->count_students; ++i){
		if(strings_equals(&(students->students[i].name), name)){
			count_students += 1;
			error_msg errorMsg = push_end_intvector(vec, i);
			if(errorMsg){
				return -1;
			}
		}
	}
	return count_students;
}

int find_students_by_group(Students *students, IntVector *vec, String *group) {
	int count_students = 0;
	for(int i = 0; i < students->count_students; ++i){
		if(strings_equals(&(students->students[i].group), group)){
			count_students += 1;
			error_msg errorMsg = push_end_intvector(vec, i);
			if(errorMsg){
				return -1;
			}
		}
	}
	return count_students;
}

int compare_by_id(const void * a, const void * b){
	Student first = *((Student*)a);
	Student second = *((Student*)b);
	return (int)first.id - (int)second.id;
}

void sort_by_id(Students * students){
	qsort(students->students, students->count_students, sizeof(Student), compare_by_id);
}

int compare_by_name(const void * a, const void * b){
	Student first = *((Student*)a);
	Student second = *((Student*)b);
	return string_comp(&(first.name), &(second.name));
}

void sort_by_name(Students * students){
	qsort(students->students, students->count_students, sizeof(Student), compare_by_name);
}


int compare_by_last_name(const void * a, const void * b){
	Student first = *((Student*)a);
	Student second = *((Student*)b);
	return string_comp(&(first.last_name), &(second.last_name));
}

void sort_by_last_name(Students * students){
	qsort(students->students, students->count_students, sizeof(Student), compare_by_last_name);
}

int compare_by_group(const void * a, const void * b){
	Student first = *((Student*)a);
	Student second = *((Student*)b);
	return string_comp(&(first.group), &(second.group));
}

void sort_by_group(Students * students){
	qsort(students->students, students->count_students, sizeof(Student), compare_by_group);
}


double calculate_average_score_student(Student * student){
	double score = 0.0;
	for(int i = 0; i < 5; ++i){
		score += (double )(student->grades[i] - '0');
	}
	score /= 5.0;
	return score;
}

double calculate_average_score_students(Students * students){
	double score = 0.0;
	for(int i = 0; i < students->count_students; ++i){
		score += calculate_average_score_student(&(students->students[i]));
	}
	score /= (double )students->count_students;
	return score;
}

int filter_students_by_average_score(Students * students, IntVector * result){
	if(!result || !result->arr){
		return -1;
	}
	int count_good_students = 0;
	error_msg errorMsg;
	double average_score;
	double average_score_all_students = calculate_average_score_students(students);
	for(int i = 0; i < students->count_students; ++i){
		average_score = calculate_average_score_student(&(students->students[i]));
		if(average_score > average_score_all_students){
			count_good_students += 1;
			errorMsg = push_end_intvector(result, i);
			if(errorMsg) return -1;
		}
	}
	return count_good_students;
}


void clear_buffer(){
	while ( getchar() != '\n' );
}