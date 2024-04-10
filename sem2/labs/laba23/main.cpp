#include <iostream>
#include "tree.cpp"


int main() {
    Tree tree(0);
    tree.add(tree.root, tree.root, 1);
    tree.add(tree.root, tree.root, 3);
    Node * el = tree.find(tree.root, 3);
    tree.add(tree.root, tree.root->son, 11);
    tree.add(tree.root, el, 4);
    tree.add(tree.root, el, 5);
    tree.add(tree.root, el, 6);
    tree.add(tree.root, el, 7);
    Node * l = tree.find(tree.root, 6);
    tree.add(tree.root, l, 12);
    Node * r = tree.find(tree.root, 12);
    tree.add(tree.root, r, 15);
    // tree.delete_node(tree.find(tree.root, 12));
    tree.print(tree.root);
    std::cout << "Глубина макисмального элемента: " << tree.el_depth(tree.root, tree.max_el(tree.root)) << std::endl;
    return 0;
}
