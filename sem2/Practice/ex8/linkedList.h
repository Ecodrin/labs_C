#include <stdlib.h>
#include <errno.h>


#ifndef EX8_LINKEDLIST_H
#define EX8_LINKEDLIST_H

typedef char Data;
typedef struct Node Node;

struct Node{
    Data val;
    Node * next;
    Node * prev;
};

Node * create_list(){
    Node * head = malloc(sizeof(Node));
    head->next = NULL;
    head->prev = NULL;
    return head;
}

void add(Node * head, Data x){
    Node * el = malloc(sizeof(Node));
    el->val = x;
    while (head->next != NULL){
        head = head->next;
    }
    head->next = el;
    el->prev = head;
}

void print_list(Node * head){
    while(head->next != NULL){
        head = head->next;
        printf("%c", head->val);
    }
    putchar('\n');
}

void delete_list(Node * head){
    while (head->next != NULL){
        head = head->next;
        free(head->prev);
    }
    free(head);
}


int len(Node * head){
    int k = 0;
    while (head->next != NULL){
        k += 1;
        head = head->next;
    }
    return k;
}

void delete_node(Node * head, Data x){
    while (head->val != x){
        if (head->next == NULL ){
            perror("Нет элемента в списке");
        }
        head = head->next;
    }
    head->prev->next = head->next;
    if(head->next != NULL){
        head->next->prev = head->prev;
    }
    free(head);
}

void delete_every_k_element(Node * head, int k){
    int  i = 0;
    Node * q = head->next;
    while(q->next != NULL){
        q = q->next;
        if(i % k == 0){
            delete_node(head,  q->prev->val);
        }
        ++i;
    }
    if(i % k == 0){
        delete_node(head,  q->val);
    }
}

#endif
