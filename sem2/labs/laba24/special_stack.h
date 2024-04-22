//
// Created by matvey on 4/14/24.
//

#ifndef LABA24_SPECIAL_SpecialStack_H
#define LABA24_SPECIAL_SpecialStack_H


struct Node{
    char val;
    Node * left;
    Node * right;
    Node(char vl = 0, Node * lft = nullptr, Node * rght = nullptr){
        val = vl;
        left = lft;
        right = rght;
    }
};

#include <iostream>

using namespace std;


struct SpecialStack{
    int len;
    Node ** data;
    int top;
};

void resize(SpecialStack& , int l  = 10);
void SpecialStack_copy(SpecialStack &s, SpecialStack & new_s);


void delete_SpecialStack(SpecialStack &s){
    if(s.data != NULL) delete s.data;
    s.data = NULL;
    s.len = 0;
    s.top = -1;
}

bool SpecialStack_is_empty(const SpecialStack & s) {
    return s.top == -1;
}

void print_SpecialStack(SpecialStack & s){
    for(int i = 0; i < s.top; ++i){
        std::cout << s.data[i] << " ";
    }
    std::cout << std::endl;
}

void new_SpecialStack(SpecialStack & s1, int len){
    if(len < 0) throw -1;
    s1.len = len;
    s1.top = -1;
    if(len == 0) s1.data = NULL;
    else{
        s1.data = new Node *[len];
    }
}

SpecialStack new_SpecialStack(int l){
    if(l < 0) throw -1;
    SpecialStack res;
    new_SpecialStack(res, l);
    return res;
}

void push_SpecialStack(SpecialStack & s, Node * e){
    s.top++;
    if(s.top >= s.len) resize(s);
    s.data[s.top] = e;
}

Node * pull_SpecialStack(SpecialStack & s){
    if(SpecialStack_is_empty(s)) throw -1;
    s.top--;
    return s.data[s.top + 1];
}

Node * SpecialStack_top(SpecialStack s){
    if(SpecialStack_is_empty(s) ) throw -1;
    return s.data[s.top];
}

void SpecialStack_copy(SpecialStack &s, SpecialStack & new_s){
    if(s.top >= new_s.len)
        resize(new_s, s.top + 1 - new_s.len);
    for(int i = 0; i <= s.top; ++i){
        new_s.data[i] = s.data[i];
    }
    new_s.top = s.top;
}
void resize(SpecialStack & s, int l){
    SpecialStack res = new_SpecialStack(s.len + l);
    SpecialStack_copy(s, res);
    delete_SpecialStack(s);
    s = res;
}


#endif //LABA24_SPECIAL_SpecialStack_H

