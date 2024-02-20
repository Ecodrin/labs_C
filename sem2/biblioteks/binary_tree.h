#include <stdlib.h>


#ifndef LABA23_TREE_H
#define LABA23_TREE_H

typedef struct Tree Tree;
struct Tree{
    int val;
    Tree * first;
    Tree * second;
};

Tree * tree_create(){
    return NULL;
}

void tree_add(Tree ** tree, int x){
    if(*tree == NULL){
        Tree * p = (Tree *)malloc(sizeof(Tree));
        p->val = x;
        p->first = p->second = NULL;
        *tree = p;
    }
    if((*tree)->val > x)tree_add(&((*tree)->first), x);
    if((*tree)->val < x) tree_add(&((*tree)->second), x);
}

void tree_print(Tree * tree){
    if (tree == NULL) return;
    tree_print(tree->first);
    printf("%d ", tree->val);
    tree_print(tree->second);
}


Tree * min(Tree * tree){
    if(tree->first == NULL)
        return tree;
    return min(tree->first);
}

Tree * tree_delete(Tree * tree, int x){
    if(tree == NULL) return tree;
    if(x > tree->val) tree->second = tree_delete(tree->second, x);
    else if(x < tree->val) tree->first = tree_delete(tree->first, x);
    else if(tree->first != NULL && tree->second != NULL){
        tree->val = min(tree->second)->val;
        tree->second = tree_delete(tree->second, tree->val);
    }
    else{
        if(tree->first != NULL || tree->second != NULL) {
            Tree * child = (tree->first) ? tree->first : tree->second;
            Tree * curr = tree;
            tree = child;
            free(curr);
        }
        else {
            tree = NULL;
        }
    }
    return tree;
}

void tree_destroy(Tree * tree){
    if(tree == NULL) return;
    tree_destroy(tree->first);
    tree_destroy(tree->second);
    free(tree);
}



#endif
