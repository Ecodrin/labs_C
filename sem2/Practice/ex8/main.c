#include <stdio.h>
#include <stdlib.h>
#include "linkedList.h"

/*
 Линейный список
 Тип: литерный
 линейный двунаправленный;

 */



int main() {
    Node * head = create_list();
    char c;
    while((c = getc(stdin)) != EOF){
        add(head, c);
    }

    print_list(head);
    printf("%d \n", len(head));
    delete_every_k_element(head, 3);
    print_list(head);
    delete_list(head);
    return 0;
}
