#include "ex8.h"

error_msg create_node(Node** node, int data) {
	*node = (Node*)calloc(1, sizeof(Node));
	if (!*node) {
		return MEMORY_ALLOCATED_ERROR;
	}
	(*node)->data = data;
	return SUCCESS;
}

void add_node(Node* prev, Node* cur) {
	cur->next = prev->next;
	prev->next = cur;
}

void delete_node(Node* prev, Node* cur) {
	prev->next = cur->next;
	cur->data = 0;
	cur->next = NULL;
	free(cur);
}
void destroy_LinkedList(Node* head) {
	Node* tmp;
	while (head) {
		tmp = head;
		head = head->next;
		tmp->data = 0;
		tmp->next = NULL;
		free(tmp);
	}
}

Node* find_node(Node* head, int data) {
	while (head) {
		if (head->data == data) {
			return head;
		}
		head = head->next;
	}
	return NULL;
}

error_msg push_node(Node** head, int data) {
	Node* tmp = *head;
	error_msg errorMsg;
	if (!tmp) {
		errorMsg = create_node(head, data);
		if (errorMsg) {
			return errorMsg;
		}
	} else {
		while (tmp->next) tmp = tmp->next;
		errorMsg = create_node(&(tmp->next), data);
		if (errorMsg) {
			return errorMsg;
		}
	}
	return SUCCESS;
}

void print_LinkedList(FILE* stream, Node* head, char* separator) {
	while (head) {
		fprintf(stream, "%d%s", head->data, separator);
		head = head->next;
	}
}

error_msg create_polynomial(Polynomial** polynomial) {
	*polynomial = (Polynomial*)calloc(1, sizeof(Polynomial));
	error_msg errorMsg = create_node(&((*polynomial)->coefficients), 0);
	if (errorMsg) {
		return errorMsg;
	}
	(*polynomial)->degree = 0;
	return SUCCESS;
}

void destroy_polynomial(Polynomial* polynomial) {
	destroy_LinkedList(polynomial->coefficients);
	polynomial->degree = 0;
	free(polynomial);
}

error_msg read_polynomial_from_string(Polynomial* polynomial, String* input_string) {
	String string;
	error_msg errorMsg = create_string(&string, "");
	if (errorMsg) {
		return errorMsg;
	}
	for (int i = 0; i < input_string->size; ++i) {
		if (input_string->arr[i] != ' ') {
			errorMsg = push_end_string(&string, input_string->arr[i]);
			if (errorMsg) {
				destroy_string(&string);
				return errorMsg;
			}
		}
		if (input_string->arr[i] != ' ' && input_string->arr[i] != 'x' && input_string->arr[i] != '+' && input_string->arr[i] != '-' &&
		    input_string->arr[i] != '^' && (input_string->arr[i] < '0' || input_string->arr[i] > '9')) {
			destroy_string(&string);
			return INCORRECT_OPTIONS_ERROR;
		}
	}
	int sign = 1;
	int degree = 0;
	int coefficient = 0;
	int has_coefficient = 0;
	for (int i = 0; i < string.size;) {
		if (string.arr[i] == '+' || string.arr[i] == '-') {
			if (string.arr[i] == '+')
				sign = 1;
			else
				sign = -1;
			++i;
		}

		while (string.arr[i] >= '0' && string.arr[i] <= '9') {
			coefficient = coefficient * 10 + (string.arr[i] - '0');
			i++;
			has_coefficient = 1;
		}

		if (!has_coefficient) {
			coefficient = 1;
		}
		coefficient *= sign;
		if (string.arr[i] == 'x') {
			i++;
			if(string.arr[i] != '^' && string.arr[i] != '+' && string.arr[i] != '-'){
				destroy_string(&string);
				return INCORRECT_OPTIONS_ERROR;
			}
			if (string.arr[i] == '^') {
				i++;
				if(!(string.arr[i] >= '0' && string.arr[i] <= '9')){
					destroy_string(&string);
					return INCORRECT_OPTIONS_ERROR;
				}
				while (string.arr[i] >= '0' && string.arr[i] <= '9') {
					degree = degree * 10 + (string.arr[i] - '0');
					i++;
				}
			} else {
				degree = 1;
			}
		} else {
			degree = 0;
		}
		if (polynomial->degree < degree) {
			for (int j = 0; j < degree - polynomial->degree; ++j) {
				errorMsg = push_node(&(polynomial->coefficients), 0);
				if (errorMsg) {
					destroy_string(&string);
					return errorMsg;
				}
			}
			polynomial->degree = degree;
		}
		Node* moving_head = polynomial->coefficients;
		for (int j = 0; j < degree; ++j) {
			moving_head = moving_head->next;
		}
		moving_head->data = moving_head->data + coefficient;
		coefficient = 0;
		has_coefficient = 0;
		degree = 0;
		sign = 1;
	}
	destroy_string(&string);
	return SUCCESS;
}
