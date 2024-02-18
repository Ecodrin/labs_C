#include <stdio.h>
#include <stdlib.h>

#ifndef UNLITED_QUEUE_H
#define UNLITED_QUEUE_H

typedef struct Queue Queue;
struct Queue {
    int val;
    Queue * next;
};

//Реализованы функции
int queue_is_empty(Queue * p);
Queue * queue_create();
void queue_push(Queue ** q, int x);
int queue_pop(Queue ** q);
void queue_print(Queue ** q);
void queue_destroy(Queue ** q);




// Сама реализация
int queue_is_empty(Queue * p){
    return p == NULL;
}

Queue * queue_create(){
    return NULL;
}

void queue_push(Queue ** q, int x){
    Queue * p = malloc(sizeof(Queue));
    p->val = x;
    p->next = *q;
    *q = p;
}

int queue_pop(Queue ** q){
    Queue * i;
    for(i = (*q)->next; i->next->next != NULL; i = i->next);
    int m = i->next->val;
    free(i->next);
    i->next = NULL;
    return m;
}

void queue_print(Queue ** q){
    for(Queue * i = *q; i != NULL;i = i->next) printf("%d ", i->val);
    putchar('\n');
}

void queue_destroy(Queue ** q){
    if(q == NULL) return;
    Queue * p = *q;
    Queue * s = p;
    p = p -> next;
    for(; p != NULL; p = p->next){
        free(s);
        s = p;
    }
    free(s);
    *q = NULL;
}
#endif //UNLITED_QUEUE_H
