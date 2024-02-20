#include <stdlib.h>

typedef struct Stack Stack;
struct Stack{
    int val;
    Stack * next;
};

#ifndef UNLITED_STACK_H
#define UNLITED_STACK_H
Stack * stack_create(){
    return NULL;
}

void stack_add(Stack ** s, int x){
    Stack *p = malloc(sizeof(Stack));
    p->val = x;
    p->next = *s;
    *s = p;
}

void stack_print(Stack * s){
    for(; s != NULL; s = s->next){
        printf("%d ", s->val);
    }
    putchar('\n');
}

void stack_destroy(Stack * s){
    Stack *p = s;
    s = s->next;
    for(; s != NULL; s = s->next){
        free(p);
        p = s;
    }
    free(p);
}

int stack_pop(Stack ** s){
    int x = (*s)->val;
    Stack *p = *s;
    *s = p->next;
    free(p);
    return x;
}

int stack_size(Stack *s){
    int i = 0;
    for(; s != NULL; s = s->next){
        ++i;
    }
    return i;
}

int stack_is_empty(Stack * s){
    return s == NULL;
}

#endif //UNLITED_STACK_H
