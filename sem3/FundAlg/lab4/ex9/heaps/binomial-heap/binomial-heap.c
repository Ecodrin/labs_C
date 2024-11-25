
#include "binomial-heap.h"

error_msg create_binomial_node(BinomialNode** binomialNode, Application* application) {
	if (binomialNode == NULL) {
		return (error_msg){INCORRECT_ARG_FUNCTION, "create_binomial_node", "get pointer to null"};
	}

	BinomialNode* tmp = (BinomialNode*)calloc(1, sizeof(BinomialNode));
	if (!tmp) {
		return (error_msg){MEMORY_ALLOCATED_ERROR, "create_binomial_node", "memory allocated in object"};
	}
	tmp->application = application;
	*binomialNode = tmp;
	return (error_msg){SUCCESS, "", ""};
}

error_msg copy_binomial_node_new(BinomialNode* src, BinomialNode** dst) {
	if (src == NULL) {
		return (error_msg){INCORRECT_ARG_FUNCTION, "copy_binomial_node_new", "get pointer to null"};
	}
	Application* dst_application;
	error_msg errorMsg = copy_application_new(src->application, &(dst_application));
	if (errorMsg.type) {
		return errorMsg;
	}
	errorMsg = create_binomial_node(dst, dst_application);
	if (errorMsg.type) {
		destroy_application(dst_application);
		return errorMsg;
	}
	BinomialNode* tmp = *dst;
	tmp->brother = NULL;
	tmp->child = NULL;
	tmp->parent = NULL;
	tmp->degree = src->degree;
	return (error_msg){SUCCESS, "", ""};
}

void destroy_binomial_node(BinomialNode* binomialNode) {
	destroy_application(binomialNode->application);
	binomialNode->application = NULL;
	binomialNode->parent = NULL;
	binomialNode->brother = NULL;
	binomialNode->child = NULL;
	free(binomialNode);
}

error_msg create_binomial_heap(BinomialHeap** binomialHeap) {
	if (binomialHeap == NULL) {
		return (error_msg){INCORRECT_ARG_FUNCTION, "create_binomial_heap", "get pointer to null"};
	}
	BinomialHeap* tmp = (BinomialHeap*)calloc(1, sizeof(BinomialHeap));
	if (!tmp) {
		return (error_msg){MEMORY_ALLOCATED_ERROR, "create_binomial_heap", "memory allocated in object"};
	}
	*binomialHeap = tmp;
	return (error_msg){SUCCESS, "", ""};
}

void delete_tree(BinomialNode* tree) {
	if (tree == NULL) return;
	delete_tree(tree->child);
	delete_tree(tree->brother);
	destroy_binomial_node(tree);
}

error_msg destroy_binomial_heap(BinomialHeap* binomialHeap) {
	if (binomialHeap == NULL) {
		return (error_msg){INCORRECT_ARG_FUNCTION, "destroy_binomial_heap", "get pointer to null"};
	}
	BinomialNode* cur = binomialHeap->head;
	delete_tree(cur);
	free(binomialHeap);
	return (error_msg){SUCCESS, "", ""};
}

BinomialNode* merge_trees(BinomialNode* tree1, BinomialNode* tree2) {
	if (tree1->application->priority < tree2->application->priority) {
		BinomialNode* t = tree1;
		tree1 = tree2;
		tree2 = t;
	}
	tree2->parent = tree1;
	tree2->brother = tree1->child;
	tree1->child = tree2;
	tree1->degree++;
	return tree1;
}

/**
 * O(log n)
 */
error_msg merge_binomial_heap_with_destroy(BinomialHeap* first, BinomialHeap* second, BinomialHeap** result) {
	if (first == NULL || second == NULL || result == NULL) {
		return (error_msg){INCORRECT_ARG_FUNCTION, "merge_binomial_heap_with_destroy", "get pointer to null"};
	}
	if (first == second) {
		return (error_msg){INCORRECT_ARG_FUNCTION, "merge_binomial_heap_with_destroy", "merge by itself"};
	}
	BinomialHeap* tmp;
	error_msg errorMsg = create_binomial_heap(&tmp);
	if (errorMsg.type) {
		return errorMsg;
	}

	BinomialNode* res_current = NULL;
	BinomialNode* first_current = first->head;
	BinomialNode* second_current = second->head;
	BinomialNode *prev1, *prev2, *prev_res;

	while (first_current != NULL || second_current != NULL || res_current != NULL) {
		prev1 = first_current;
		prev2 = second_current;
		prev_res = res_current;

		if (first_current && second_current && first_current->degree == second_current->degree) {
			first_current = first_current->brother;
			second_current = second_current->brother;
			res_current = merge_trees(prev1, prev2);
		} else if (first_current && res_current && first_current->degree == res_current->degree) {
			first_current = first_current->brother;
			res_current = merge_trees(first_current, res_current);
		} else if (second_current && res_current && second_current->degree == res_current->degree) {
			second_current = second_current->brother;
			res_current = merge_trees(second_current, res_current);
		} else {
			//			if (first_current && (!second_current || first_current->degree > second_current->degree)) {
			//				prev1 = first_current;
			//				first_current = first_current->brother;
			//			} else if (second_current && (!first_current || second_current->degree < first_current->degree))
			//{ 				prev2 = second_current; 				second_current = second_current->brother;
			//			}

			BinomialNode* new_node;
			if (prev1) {
				first_current = first_current->brother;
				new_node = prev1;
			} else if (prev2) {
				second_current = second_current->brother;
				new_node = prev2;
			} else {
				new_node = prev_res;
				res_current = NULL;
			}

			new_node->brother = tmp->head;
			tmp->head = new_node;
		}
	}

	tmp->size = first->size + second->size;
	*result = tmp;

	// Освобождаем память для first и second, но не для их узлов
	first->head = NULL;
	first->size = 0;
	second->head = NULL;
	second->size = 0;
	free(first);
	free(second);

	return (error_msg){SUCCESS, "", ""};
}

error_msg copy_binomial_heap_new(const BinomialHeap* src, BinomialHeap** dst) {
	if (src == NULL || dst == NULL) {
		return (error_msg){INCORRECT_ARG_FUNCTION, "copy_binomial_heap_new", "get pointer to null"};
	}

	BinomialHeap* tmp;
	error_msg errorMsg = create_binomial_heap(&tmp);
	if (errorMsg.type) {
		return errorMsg;
	}

	if (src->size == 0) {
		*dst = tmp;
		return (error_msg){SUCCESS, "", ""};
	}

	BinomialNode* cur_src = src->head;
	BinomialNode* cur_dst = NULL;

	errorMsg = copy_binomial_node_new(cur_src, &cur_dst);
	tmp->size = 1;
	if (errorMsg.type) {
		return errorMsg;
	}
	tmp->head = cur_dst;

	for (size_t i = 1; tmp->size < src->size; ++i) {
		if (cur_src == NULL) {
			destroy_binomial_heap(tmp);
			return (error_msg){INCORRECT_OPTIONS_ERROR, "copy_binomial_heap_new",
			                   "the number of nodes does not match the size field"};
		}
		if (cur_src->child && cur_dst->child == NULL) {
			cur_src = cur_src->child;
			errorMsg = copy_binomial_node_new(cur_src, &(cur_dst->child));
			if (errorMsg.type) {
				destroy_binomial_heap(tmp);
				return errorMsg;
			}
			tmp->size += 1;
			cur_dst->child->parent = cur_dst;
			cur_dst = cur_dst->child;
		} else if (cur_src->brother && cur_dst->brother == NULL) {
			cur_src = cur_src->brother;
			errorMsg = copy_binomial_node_new(cur_src, &(cur_dst->brother));
			if (errorMsg.type) {
				destroy_binomial_heap(tmp);
				return errorMsg;
			}
			tmp->size += 1;
			cur_dst->brother->parent = cur_dst->parent;
			cur_dst = cur_dst->brother;
		} else {
			cur_src = cur_src->parent;
			cur_dst = cur_dst->parent;
		}
	}

	*dst = tmp;
	return (error_msg){SUCCESS, "", ""};
}

error_msg merge_binomial_heap_without_destroy(BinomialHeap* first, BinomialHeap* second, BinomialHeap** result) {
	BinomialHeap* tmp_1;
	BinomialHeap* tmp_2;
	error_msg errorMsg = copy_binomial_heap_new(first, &tmp_1);
	if (errorMsg.type) {
		return errorMsg;
	}
	errorMsg = copy_binomial_heap_new(second, &tmp_2);
	if (errorMsg.type) {
		destroy_binomial_heap(tmp_1);
		return errorMsg;
	}

	errorMsg = merge_binomial_heap_with_destroy(tmp_1, tmp_2, result);
	if (errorMsg.type) {
		destroy_binomial_heap(tmp_1);
		destroy_binomial_heap(tmp_2);
		return errorMsg;
	}

	return (error_msg){SUCCESS, "", ""};
}

error_msg insert_binomial_heap(BinomialHeap* binomialHeap, Application* application) {
	BinomialHeap* tmp;
	error_msg errorMsg = create_binomial_heap(&tmp);
	if (errorMsg.type) {
		return errorMsg;
	}
	errorMsg = create_binomial_node(&(tmp->head), application);
	if (errorMsg.type) {
		destroy_binomial_heap(tmp);
		return errorMsg;
	}
	tmp->size += 1;
	BinomialHeap* res;
	errorMsg = merge_binomial_heap_without_destroy(binomialHeap, tmp, &res);

	if (errorMsg.type) {
		destroy_binomial_heap(tmp);
		return errorMsg;
	}

	destroy_binomial_heap(tmp);

	// Очищаем старое дерево
	BinomialNode* cur = binomialHeap->head;
	delete_tree(cur);

	binomialHeap->size = res->size;
	binomialHeap->head = res->head;
	free(res);
	return errorMsg;
}

Application* find_max_priority_elem_binomial_heap(const BinomialHeap* binaryHeap) {
	if (binaryHeap == NULL) {
		return NULL;
	}
	BinomialNode* current = binaryHeap->head;
	BinomialNode* max_cur = binaryHeap->head;
	while (current) {
		if (current->application->priority > max_cur->application->priority) {
			max_cur = current;
		}
		current = current->brother;
	}
	return max_cur->application;
}

void counting_size_binomial_node(BinomialNode* binomialNode, size_t* i) {
	if (binomialNode == NULL) {
		return;
	}
	*i += 1;
	counting_size_binomial_node(binomialNode->brother, i);
	counting_size_binomial_node(binomialNode->child, i);
}

error_msg delete_binomial_heap(BinomialHeap* binomialHeap, Application** application) {
	if (binomialHeap == NULL || application == NULL) {
		return (error_msg){INCORRECT_ARG_FUNCTION, "delete_binomial_heap", "get pointer to null"};
	}
	if (binomialHeap->size == 0) {
		return (error_msg){INCORRECT_ARG_FUNCTION, "delete_binomial_heap", "try to delete from empty queue"};
	}

	BinomialNode* prev_max = NULL;
	BinomialNode* cur_max = binomialHeap->head;
	BinomialNode* cur = binomialHeap->head;
	BinomialNode* prev = NULL;
	while (cur) {
		if (cur->application->priority > cur_max->application->priority) {
			prev_max = prev;
			cur_max = cur;
		}
		prev = cur;
		cur = cur->brother;
	}

	if (prev_max == NULL) {
		if (binomialHeap->size != 1) {
			binomialHeap->size -= 1;
		}
		binomialHeap->head = binomialHeap->head->brother;
		*application = cur_max->application;
		free(cur_max);
		return (error_msg){SUCCESS, "", ""};
	}

	// создаем 2 дерева и сливаем их с основным
	BinomialHeap* tmp_1;
	error_msg errorMsg = create_binomial_heap(&tmp_1);
	if (errorMsg.type) {
		return errorMsg;
	}

	BinomialHeap* tmp_2;
	errorMsg = create_binomial_heap(&tmp_2);
	if (errorMsg.type) {
		destroy_binomial_heap(tmp_1);
		return errorMsg;
	}

	counting_size_binomial_node(cur_max->brother, &(tmp_1->size));
	counting_size_binomial_node(cur_max->child, &(tmp_2->size));
	tmp_1->head = cur_max->brother;
	tmp_2->head = cur_max->child;
	binomialHeap->size = binomialHeap->size - tmp_1->size - tmp_2->size - 1;
	*application = cur_max->application;
	prev_max->brother = cur_max->brother;

	BinomialHeap *res1, *res2;
	errorMsg = merge_binomial_heap_without_destroy(tmp_1, binomialHeap, &res1);
	if (errorMsg.type) {
		destroy_binomial_heap(tmp_1);
		destroy_binomial_heap(tmp_2);
		return errorMsg;
	}

	errorMsg = merge_binomial_heap_without_destroy(tmp_2, res1, &res2);
	if (errorMsg.type) {
		destroy_binomial_heap(tmp_1);
		destroy_binomial_heap(tmp_2);
		destroy_binomial_heap(res1);
		return errorMsg;
	}

	destroy_binomial_heap(tmp_1);
	destroy_binomial_heap(tmp_2);
	destroy_binomial_heap(res1);
	delete_tree(binomialHeap->head);
	binomialHeap->head = res2->head;
	binomialHeap->size = res2->size;
	free(res2);
	free(cur_max);

	return (error_msg){SUCCESS, "", ""};
}
