



#include "heaps/heaps.h"



int main() {
	// Создаем 13 элементов для первой кучи
	Application *r1, *r2, *r3, *r4, *r5, *r6, *r7, *r8, *r9, *r10, *r11, *r12, *r13;
	String s1, s2, s3, s4, s5, s6, s7, s8, s9, s10, s11, s12, s13;
	Time t1 = {1, 2, 3, 4, 5, 6};
	Time t2 = {2, 3, 4, 5, 6, 7};
	Time t3 = {3, 4, 5, 6, 7, 8};
	Time t4 = {4, 5, 6, 7, 8, 9};
	Time t5 = {5, 6, 7, 8, 9, 10};
	Time t6 = {6, 7, 8, 9, 10, 11};
	Time t7 = {7, 8, 9, 10, 11, 12};
	Time t8 = {8, 9, 10, 11, 12, 13};
	Time t9 = {9, 10, 11, 12, 13, 14};
	Time t10 = {10, 11, 12, 13, 14, 15};
	Time t11 = {11, 12, 13, 14, 15, 16};
	Time t12 = {12, 13, 14, 15, 16, 17};
	Time t13 = {13, 14, 15, 16, 17, 18};

	create_string(&s1, "sad1");
	create_string(&s2, "sad2");
	create_string(&s3, "sad3");
	create_string(&s4, "sad4");
	create_string(&s5, "sad5");
	create_string(&s6, "sad6");
	create_string(&s7, "sad7");
	create_string(&s8, "sad8");
	create_string(&s9, "sad9");
	create_string(&s10, "sad10");
	create_string(&s11, "sad11");
	create_string(&s12, "sad12");
	create_string(&s13, "sad13");

	create_application(&r1, t1, 10, 2, &s1);
	create_application(&r2, t2, 11, 2, &s2);
	create_application(&r3, t3, 12, 2, &s3);
	create_application(&r4, t4, 13, 2, &s4);
	create_application(&r5, t5, 14, 2, &s5);
	create_application(&r6, t6, 15, 2, &s6);
	create_application(&r7, t7, 40, 2, &s7);
	create_application(&r8, t8, 17, 2, &s8);
	create_application(&r9, t9, 18, 2, &s9);
	create_application(&r10, t10, 19, 2, &s10);
	create_application(&r11, t11, 20, 2, &s11);
	create_application(&r12, t12, 21, 2, &s12);
	create_application(&r13, t13, 22, 2, &s13);

	// Создаем первую кучу и добавляем элементы
	Queue q = {NULL, heaps_functions[5]};
	q.v.create_heap(&(q.q));
	q.v.insert_heap(q.q, r1);
	q.v.insert_heap(q.q, r2);
	q.v.insert_heap(q.q, r3);
	q.v.insert_heap(q.q, r4);
	q.v.insert_heap(q.q, r5);
	q.v.insert_heap(q.q, r6);
	q.v.insert_heap(q.q, r7);
	q.v.insert_heap(q.q, r8);
	q.v.insert_heap(q.q, r9);
	q.v.insert_heap(q.q, r10);
	q.v.insert_heap(q.q, r11);
	q.v.insert_heap(q.q, r12);
	q.v.insert_heap(q.q, r13);

	error_msg errorMsg;
	Application * f;

	f = q.v.find_max_priority_elem(q.q);
	printf("%zu\n", f->key);


	Application * find;
	errorMsg = q.v.delete_heap(q.q, &find);
	if(errorMsg.type){
		return print_error(errorMsg);
	}
	printf("%zu\n", find->key);
	destroy_application(find);



	errorMsg = q.v.delete_heap(q.q, &find);
	if(errorMsg.type){
		return print_error(errorMsg);
	}
	printf("%zu\n", find->key);

	destroy_application(find);
	q.v.destroy_heap(q.q);
	// Выводим сообщение о завершении
	printf("Heaps merged and first head destroyed.\n");

	return 0;
}