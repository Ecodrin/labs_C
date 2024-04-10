#include <iostream>

typedef int Data;
struct Node{
    Data val;
    Node * son;
    Node * brother;
    Node(Data vl=0, Node * sn= nullptr, Node * brthr= nullptr){
        val = vl;
        son = sn;
        brother = brthr;
    }
    ~Node(){
        val = 0;
        son = nullptr;
        brother = nullptr;
    }

};

class Tree{

private:

public:
    Node * root = nullptr;
    Tree(int v=0){
        root = new Node(v);
    };
    ~Tree(){
        deleteTree(root);
        root = nullptr;
    }
    void deleteTree(Node * node){
        if(node == nullptr) return;
        deleteTree(node->brother);
        deleteTree(node->son);
        delete node;

    }

    void add(Node * rt, Node * father, Data x){
        if(rt == nullptr) return;
        if(rt == father){
            Node * el = new Node(x);
            if(rt->son == nullptr){
                rt->son = el;
            }
            else {
                rt = rt->son;
                while (rt->brother != nullptr){
                    rt = rt->brother;
                }
                rt->brother = el;
            }
        }
        add(rt->brother, father, x);
        add(rt->son, father, x);
    }
    Node * find(Node * rt, Data x){
        if(rt == nullptr){
            return nullptr;
        }
        if(rt->val == x){
            return rt;
        }
        Node * q = find(rt->brother, x);
        q = std::max(find(rt->son, x), q);
        return q;
    }
    void delete_node(Node * node){
        Node * f = find_next(root, node);
        deleteTree(node);
        if(f->brother == node){
            f->brother = nullptr;
        }
        else{
            f->son = nullptr;
        }
    }

    Node * find_next(Node * rt, Node * x){
        if(rt == nullptr){
            return nullptr;
        }
        if(rt->son == x){
            return rt;
        }
        if(rt->brother == x){
            return rt;
        }
        Node * q = find_next(rt->brother, x);
        q = std::max(find_next(rt->son, x), q);
        return q;
    }


    int max_el(Node * rt){
        if(rt == nullptr){
            return 0;
        }
        Data a = max_el(rt->son);
        Data b = max_el(rt->brother);
        a = std::max(a, b);
        return std::max(rt->val, a);
    }

    int max_depth(Node * rt){
        if(rt == nullptr){
            return 0;
        }
        return std::max(max_depth(rt->brother), max_depth(rt->son) + 1);
    }

    int el_depth(Node * rt, Data el){
        if(rt == nullptr){
            return -100;
        }
        if(rt->val == el){
            return 1;
        }
        return std::max(el_depth(rt->son, el) + 1, el_depth(rt->brother, el));
    }


    void print(Node * rt){ ///??????????????????????????
        if(rt == nullptr)return;
        int d = el_depth(root, rt->val);
        for(int i = 0; i < d - 1; ++i)
            std::cout << "-";
        std::cout << rt->val << std::endl;
        print(rt->son);
        print(rt->brother);
    }
};
