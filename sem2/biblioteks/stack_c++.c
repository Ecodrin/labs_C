#include <iostream>

using namespace std;


struct Stack{
    int len;
    int * data;
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

void new_stack(Stack & s1, int len){
    if(len < 0) throw -1;
    s1.len = len;
    s1.top = -1;
    if(len == 0) s1.data = NULL;
    else{
        s1.data = new int[len];
    }
}

Stack new_stack(int l){
    if(l < 0) throw -1;
    Stack res;
    new_stack(res, l);
    return res;
}

void push_stack(Stack & s, int e){
    s.top++;
    if(s.top >= s.len) resize(s);
    s.data[s.top] = e;
}

int pull_stack(Stack & s){
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



int main(){
    Stack s = new_stack(1);
    push_stack(s, 12);
    push_stack(s, 3);
    Stack dopstack1 = new_stack(1);
    Stack dopstack2 = new_stack(1);
    cout << "S(было): ";
    while(! stack_is_empty(s)){
        push_stack(dopstack1, stack_top(s));
        cout << pull_stack(s) << " ";
    }
    cout <<"\nS(стало): ";
    while(! stack_is_empty(dopstack1)){
        push_stack(s, stack_top(dopstack1));
        push_stack(dopstack2, stack_top(dopstack1));
        cout << pull_stack(dopstack1) << " ";
    }
    cout << "\nS(вернулись): ";
    while(! stack_is_empty(s)){
        cout << pull_stack(s) << " ";
    }
    cout << "\ndopstek2: ";
    while(! stack_is_empty(dopstack2)){
        cout << pull_stack(dopstack2) << " ";
    }

    cout << "\n";

    //Stack ss = new_stack(-100);
    delete_Stack(s);
    delete_Stack(dopstack1);
    delete_Stack(dopstack2);
    return 0;
}
