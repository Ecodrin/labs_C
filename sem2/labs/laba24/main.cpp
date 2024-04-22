#include "ExpTree.h"


int main(){
    Tree tree;
    add_tree_exr(tree);
    tree.print(tree.root);
    tree.print_exp(tree.root);
    std::cout << std::endl;
    while(!tree.is_simple(tree.root)){
        tree.simple(tree.root);
    }
    tree.print(tree.root);
    tree.print_exp(tree.root);
    std::cout << std::endl;
}
