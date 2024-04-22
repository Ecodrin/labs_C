#include "Reverse_Polish_notation.h"
#include "special_stack.h"
#include <iostream>

#ifndef LABA24_EXPTREE_H
#define LABA24_EXPTREE_H


class Tree{
public:
    Node * root = nullptr;
    Tree(){
        root = nullptr;
    }
    ~Tree(){
        delete_tree(root);
    }
    void print(Node * rt){
        if(rt == nullptr) return;
        print(rt->left);
        int d = depth(root, rt);
        for(int i = 0; i < d; ++i){
            std::cout << "==";
        }
        std::cout << rt->val << std::endl;
        print(rt->right);
    }

    int depth(Node * rt, Node * our, int k=0){
        if(rt == nullptr) return -1000;
        if(rt == our) return k;
        return std::max(depth(rt->left, our, k + 1), depth(rt->right, our, k + 1));
    }
    void add(char operation, SpecialStack & specialstack) {
        Node * r = pull_SpecialStack(specialstack);
        Node * l = pull_SpecialStack(specialstack);
        Node * rt = new Node(operation, r, l);
        push_SpecialStack(specialstack, rt);;
    }


    void print_exp(Node * rt){
        if (rt == nullptr)
            return;
        if(rt->right == nullptr and rt->left == nullptr){
            std::cout << rt->val;
            return;
        }
        else{
            std::cout << '(';

            print_exp(rt->right);
            std::cout << rt->val;
            print_exp(rt->left);
            std::cout << ')';
        }
    }

    void delete_tree(Node * rt){
        if(rt == nullptr) return;
        delete_tree(rt->left);
        delete_tree(rt->right);
        delete rt;
    }

    bool is_simple(Node * rt){
        if(rt == nullptr) return true;
        if(rt->val == '/' and (rt->left->val == '/' or rt->right->val == '/')) return false;

        return std::min(is_simple(rt->left), is_simple(rt->right));
    }
    void simple(Node * rt){
        if(rt == nullptr){
            return;
        }
        if( rt->val == '/' and rt->left->val == '/'){
            Node * r = new Node('*', rt->left->left, rt->right);
            rt->left = rt->left->right;
            rt->right = r;
        }
        if( rt->val == '/' and rt->right->val == '/'){
            Node * r = new Node('*', rt->right->left, rt->left);

            rt->right = rt->right->right;
            rt->left = r;
        }
        simple(rt->left);
        simple(rt->right);
    }


};

void add_tree_exr(Tree & tree){
    char result[100];
    to_reverse_polish_notation(result);
    std::cout << "Обратная польская запись: " << result << std::endl;
    SpecialStack specialstack = new_SpecialStack(1);
    for(int i = 0; result[i] != '\0'; ++i){
        if(is_alpha(result[i])){
            Node * el = new Node(result[i]);
            push_SpecialStack(specialstack, el);
        }
        else{
            tree.add(result[i], specialstack);
        }
    }
    tree.root = pull_SpecialStack(specialstack);
    delete_SpecialStack(specialstack);
}
#endif
