#include <iostream>

using namespace std;


struct Stack{
    int len;
    char * data;
    int top;
};

void resize(Stack& , int l  = 10);
void stack_copy(Stack &s, Stack & new_s);


void delete_Stack(Stack &s){
    if(s.data != NULL) delete s.data;
    s.data = NULL;
    s.len = 0;
    s.top = -1;
}

bool stack_is_empty(const Stack & s) {
    return s.top == -1;
}

void print_stack(Stack & s){
    for(int i = 0; i <= s.top; ++i){
        std::cout << s.data[i] << " ";
    }
    std::cout << std::endl;
}

void new_stack(Stack & s1, int len){
    if(len < 0) throw -1;
    s1.len = len;
    s1.top = -1;
    if(len == 0) s1.data = NULL;
    else{
        s1.data = new char[len];
    }
}

Stack new_stack(int l){
    if(l < 0) throw -1;
    Stack res;
    new_stack(res, l);
    return res;
}

void push_stack(Stack & s, char e){
    s.top++;
    if(s.top >= s.len) resize(s);
    s.data[s.top] = e;
}

char pull_stack(Stack & s){
    if(stack_is_empty(s)) throw -1;
    s.top--;
    return s.data[s.top + 1];
}

int stack_top(Stack s){
    if(stack_is_empty(s) ) throw -1;
    return s.data[s.top];
}

void stack_copy(Stack &s, Stack & new_s){
    if(s.top >= new_s.len)
        resize(new_s, s.top + 1 - new_s.len);
    for(int i = 0; i <= s.top; ++i){
        new_s.data[i] = s.data[i];
    }
    new_s.top = s.top;
}
void resize(Stack & s, int l){
    Stack res = new_stack(s.len + l);
    stack_copy(s, res);
    delete_Stack(s);
    s = res;
}
