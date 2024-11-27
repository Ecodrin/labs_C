#include "heaps/heaps.h"

//int main() {
//
//	Application * r;
//	String s;
//	create_string(&s, "sad");
//	Time t = {1, 2, 3, 4, 5, 6};
//	create_application(&r, t, 10, 2, &s);
//
//	Application * r2;
//	String s2;
//	create_string(&s2, "sad");
//	Time t2 = {1, 2, 3, 4, 5, 6};
//	create_application(&r2, t2, 12, 2, &s2);
//
//	Application * r3;
//	String s3;
//	create_string(&s3, "sad");
//	Time t3 = {1, 2, 3, 4, 5, 6};
//	create_application(&r3, t3, 12, 2, &s3);
//	Application *r4, *r5, *r6;
//	copy_application_new(r, &r4);
//	copy_application_new(r2, &r5);
//	copy_application_new(r3, &r6);
//
//	Queue q = {NULL, heaps_functions[1]};
//	q.v.create_heap(&(q.q));
//	q.v.insert_heap(q.q, r);
//	q.v.insert_heap(q.q, r2);
//	q.v.insert_heap(q.q, r3);
//
//	Queue q2 = {NULL, heaps_functions[1]};
//	q2.v.create_heap(&(q2.q));
//	q2.v.insert_heap(q2.q, r4);
//	q2.v.insert_heap(q2.q, r5);
//	q2.v.insert_heap(q2.q, r6);
//
//	Queue q3;
//	q.v.merge_heap_without_destroy(q.q, q2.q, &(q3.q));
//	q.v.destroy_heap(q.q);
//
////	FibonacciHeap * f;
////	error_msg errorMsg = create_fibonacci_heap(&f);
////	if(errorMsg.type){
////		return print_error(errorMsg);
////	}
////
////	errorMsg = insert_fibonacci_heap(f, r);
////	if(errorMsg.type){
////		return print_error(errorMsg);
////	}
////
////	errorMsg = insert_fibonacci_heap(f, r2);
////	if(errorMsg.type){
////		return print_error(errorMsg);
////	}
//
////
////	FibonacciHeap *res;
////	FibonacciHeap * f2;
////	errorMsg = create_fibonacci_heap(&f2);
////	if(errorMsg.type){
////		return print_error(errorMsg);
////	}
////
////	errorMsg = merge_fibonacci_heap_with_destroy(f2, f, &res);
////	if(errorMsg.type){
////		return print_error(errorMsg);
////	}
////
////	destroy_fibonacci_heap(res);
//	return 0;
//}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Предположим, что у нас есть следующие структуры и функции:
// Application, String, Time, create_string, create_application, copy_application_new, Queue, heaps_functions

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
	Queue q = {NULL, heaps_functions[0]};
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

	// Создаем 13 элементов для второй кучи
	Application *r14, *r15, *r16, *r17, *r18, *r19, *r20, *r21, *r22, *r23, *r24, *r25, *r26;
	String s14, s15, s16, s17, s18, s19, s20, s21, s22, s23, s24, s25, s26;
	Time t14 = {14, 15, 16, 17, 18, 19};
	Time t15 = {15, 16, 17, 18, 19, 20};
	Time t16 = {16, 17, 18, 19, 20, 21};
	Time t17 = {17, 18, 19, 20, 21, 22};
	Time t18 = {18, 19, 20, 21, 22, 23};
	Time t19 = {19, 20, 21, 22, 23, 24};
	Time t20 = {20, 21, 22, 44, 24, 25};
	Time t21 = {21, 22, 23, 24, 25, 26};
	Time t22 = {22, 23, 24, 25, 26, 27};
	Time t23 = {23, 24, 25, 26, 27, 28};
	Time t24 = {24, 25, 26, 27, 28, 29};
	Time t25 = {25, 26, 27, 28, 29, 30};
	Time t26 = {26, 27, 28, 29, 30, 31};

	create_string(&s14, "sad14");
	create_string(&s15, "sad15");
	create_string(&s16, "sad16");
	create_string(&s17, "sad17");
	create_string(&s18, "sad18");
	create_string(&s19, "sad19");
	create_string(&s20, "sad20");
	create_string(&s21, "sad21");
	create_string(&s22, "sad22");
	create_string(&s23, "sad23");
	create_string(&s24, "sad24");
	create_string(&s25, "sad25");
	create_string(&s26, "sad26");

	create_application(&r14, t14, 23, 2, &s14);
	create_application(&r15, t15, 24, 2, &s15);
	create_application(&r16, t16, 25, 2, &s16);
	create_application(&r17, t17, 26, 2, &s17);
	create_application(&r18, t18, 27, 2, &s18);
	create_application(&r19, t19, 36, 2, &s19);
	create_application(&r20, t20, 29, 2, &s20);
	create_application(&r21, t21, 30, 2, &s21);
	create_application(&r22, t22, 31, 2, &s22);
	create_application(&r23, t23, 32, 2, &s23);
	create_application(&r24, t24, 33, 2, &s24);
	create_application(&r25, t25, 34, 2, &s25);
	create_application(&r26, t26, 1, 2, &s26);

	// Создаем вторую кучу и добавляем элементы
	Queue q2 = {NULL, heaps_functions[0]};
	q2.v.create_heap(&(q2.q));
	q2.v.insert_heap(q2.q, r14);
	q2.v.insert_heap(q2.q, r15);
	q2.v.insert_heap(q2.q, r16);
	q2.v.insert_heap(q2.q, r17);
	q2.v.insert_heap(q2.q, r18);
	q2.v.insert_heap(q2.q, r19);
	q2.v.insert_heap(q2.q, r20);
	q2.v.insert_heap(q2.q, r21);
	q2.v.insert_heap(q2.q, r22);
	q2.v.insert_heap(q2.q, r23);
	q2.v.insert_heap(q2.q, r24);
	q2.v.insert_heap(q2.q, r25);
	q2.v.insert_heap(q2.q, r26);

	// Объединяем две кучи в третью
	Application *f;
	f = q.v.find_max_priority_elem(q.q);
	printf("%zu\n", f->priority);
	f = q.v.find_max_priority_elem(q2.q);
	printf("%zu\n", f->priority);
	Queue q3 = {NULL, heaps_functions[0]};
	error_msg errorMsg = q.v.merge_heap_without_destroy(q.q, q2.q, &(q3.q));
	if(errorMsg.type){
		return print_error(errorMsg);
	}
	f = q.v.find_max_priority_elem(q3.q);
	printf("%zu\n", f->priority);
	// Уничтожаем первую кучу
	q.v.destroy_heap(q.q);
	q.v.destroy_heap(q2.q);
	q.v.destroy_heap(q3.q);

	// Выводим сообщение о завершении
	printf("Heaps merged and first heap destroyed.\n");

	return 0;
}