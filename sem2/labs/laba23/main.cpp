#include <iostream>
#include "tree.h"


int main() {
    Tree tree(0);
    tree.add(tree.root, tree.root, 1);
    tree.add(tree.root, tree.root, 3);
    Node * el = tree.find(tree.root, 3);
    tree.add(tree.root, tree.root->son, 10);
    tree.add(tree.root, el, 4);
    tree.add(tree.root, el, 5);
    tree.add(tree.root, el, 6);
    tree.add(tree.root, el, 7);
    Node * l = tree.find(tree.root, 6);
    tree.add(tree.root, l, 12);
    tree.print();
    //std::cout << tree.max_depth(tree.root)<< std::endl;

    return 0;
}
