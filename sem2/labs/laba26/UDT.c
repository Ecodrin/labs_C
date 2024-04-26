#include "UDT.h"



void udt_create(udt *Udt, int len){
    Udt->len = len;
    Udt->mas = malloc(sizeof(value_type) * len);
    Udt->start = 0;
    Udt->depth = 0;

}
void udt_delete(udt * Udt){
    Udt->len = 0;
    Udt->depth = 0;
    Udt->start = 0;
    free(Udt->mas);
}

void udt_copy(udt* Udt, udt * new_Udt){
    if(new_Udt->len < Udt->depth){
        resize_udt(new_Udt, Udt->len);
    }
    for(int i = 0; i < Udt->depth; ++i){
        new_Udt->mas[i] = Udt->mas[(Udt->start + i) % Udt->len];
    }
    new_Udt->start = 0;
    new_Udt->depth = Udt->depth;
}

void resize_udt(udt * Udt, int l){
    udt new_Udt;
    udt_create(&new_Udt, l);
    udt_copy(Udt, &new_Udt);
    udt_delete(Udt);
    Udt->depth = new_Udt.depth;
    Udt->start = new_Udt.start;
    Udt->len = new_Udt.len;
    Udt->mas = new_Udt.mas;
}

bool udt_is_empty(udt * Udt){
    return Udt->depth == 0;
}

void udt_push_front(udt * Udt, value_type el){
    if(Udt->len == Udt->depth)
        resize_udt(Udt, Udt->len + 10);
    Udt->mas[Udt->depth % Udt->len] = el;
    Udt->depth += 1;
}

void udt_push_back(udt * Udt, value_type el){
    if(Udt->len == Udt->depth)
        resize_udt(Udt, Udt->len + 10);
    for(int i = Udt->depth; i > 0; --i){
        Udt->mas[(i + Udt->start) % Udt->len] = Udt->mas[(i + Udt->start - 1) % Udt->len];
    }
    Udt->mas[Udt->start] = el;
    Udt->depth += 1;
}

void udt_pop_back(udt * Udt){
    Udt->depth -= 1;
}

void udt_print(udt * Udt){
    for(int i = 0; i < Udt->depth; ++i){
        printf("%d ", Udt->mas[(i + Udt->start) % Udt->len]);
    }
    putchar('\n');
}

void udt_pop_front(udt * Udt){
    Udt->start  = (Udt->start + 1) % Udt->len;
    Udt->depth -= 1;
}

int udt_size(udt * Udt){
    return Udt->depth;
}
void swap(value_type * a, value_type * b){
    value_type * c = b;
    b = a;
    a = c;
}

void bubbleSort(udt * Udt){
    for(int i = 0;i < Udt->depth; ++i){
        for(int j = 0;j < Udt->depth; ++j){
            if (Udt->mas[(Udt->start + i) % Udt->len] < Udt->mas[(Udt->start + j) % Udt->len]){
                value_type c = Udt->mas[(Udt->start + i) % Udt->len] ;
                Udt->mas[(Udt->start + i) % Udt->len] = Udt->mas[(Udt->start + j) % Udt->len];
                Udt->mas[(Udt->start + j) % Udt->len] = c;
            }
        }
    }
}

