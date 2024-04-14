
#include "stack.h"

#define pr4(c) (c == '^')
#define pr3(c) (c == '*' or c == '/')
#define pr2(c) (c == '+' or c == '-')
#define pr1(c) (c == '(' or c == ')')


bool is_alpha(char c){
    return (c >= 'a' and c <= 'z') or (c >= 0 and c <= 9);
}

bool is_operation(char c){
    return c == '+' or c == '-' or c == '*' or c == '/' or c == '^';
}

bool is_skobka(char c){
    return c == ')' or c == '(';
}

bool priorety(Stack & stack, char symbol){
    if(stack_is_empty(stack))
        return true;
    char c = stack_top(stack);
    if(pr4(c) and !pr4((symbol)))
        return false;
    if(pr3(c) and !pr3(symbol) and !pr4((symbol)))
        return false;
    if(pr2(c) and !pr4(symbol) and !pr3(symbol) and !pr2(symbol))
        return false;
    return true;
}

void opz(char * result){
    char symbol;
    int i = 0;
    Stack stack = new_stack(1);
    while ((symbol = getchar()) != '\n'){
        if(is_alpha(symbol)){
            result[i] = symbol;
            i += 1;
        }
        else if(is_operation(symbol)){
            if(stack_is_empty(stack)){
                push_stack(stack, symbol);
            }
            else{
                while (!priorety(stack, symbol)){
                    result[i] = pull_stack(stack);
                    i += 1;
                }
                push_stack(stack, symbol);
            }
        }
        else if(is_skobka(symbol)){
            if(symbol == '('){
                push_stack(stack, symbol);
            }
            else{
                char c;
                while(true){
                    c = pull_stack(stack);
                    if(c == '(')
                        break;
                    result[i] = c;
                    i += 1;
                }
            }
        }

    }
    while(!stack_is_empty(stack)){
        result[i] = pull_stack(stack);
        i += 1;
    }
    result[i] = '\0';
    delete_Stack(stack);
}