#include <iostream>

using namespace std;

struct Node{
    int val;
    Node * next;
};


class LList{
public:
    Node * head;

    LList(Node * p = nullptr): head(p) {};

    ~LList(){
        Node * pt = head;
        while(head != nullptr){
            head = head->next;
            delete pt;
            pt = head;
        }
        head = nullptr;
    }

    void appendEnd(int a){
        Node * q = new Node;
        q->val = a;
        q->next = nullptr;
        Node * new_head = head;
        if(head == nullptr)
            head = q;
        else{
            while(new_head->next != nullptr){
                new_head = new_head->next;
            }
            new_head->next = q;
        }
    }
    bool is_Empty() const{
        return head == nullptr;
    }

    void print_node(const Node * node) const{
        if(node == nullptr) return;
        else{
            cout << node << " " << node->val << " " << node->next << endl;
        }
    }

    void print_list(){
        Node * q = head;
        while(q != nullptr){
            print_node(q);
            //cout << q->val << endl;
            q = q->next;
        }
    }

    Node * findNode(int val){
        Node * new_head = head;
        while(new_head->next != nullptr && new_head->val != val){
            new_head = new_head->next;
        }
        if(new_head->val == val){
            return new_head;
        }
        throw -1;
    }

    Node * findPrev(Node * ptn){
        Node * new_head = head;
        while(new_head->next != nullptr && new_head->next != ptn){
            new_head = new_head ->next;
        }
        if(new_head->next == ptn){
            return new_head;
        }
        throw -1;
    }

    Node * findNext(Node * ptn){
        Node * new_head = head;
        while(new_head->next != nullptr && new_head != ptn){
            new_head = new_head ->next;
        }
        if(new_head == ptn){
            if(new_head->next == nullptr) throw -2;
            return new_head->next;
        }
        throw -1;
    }

    void insertNext(Node *p, int val){
        Node * q = new Node;
        q->val = val;
        q->next = p->next;
        p->next = q;
    }

    void insertPrev(Node * ptn, int val){
        Node * a = findPrev(ptn);
        insertNext(a, val);
    }

    void deleteNode(Node *ptn){
        Node * a = findPrev(ptn);
        a->next = ptn->next;
        delete ptn;
    }

};



int main(){
    try {
        LList q;
        q.appendEnd(1);
        q.appendEnd(2);
        q.appendEnd(3);
        q.appendEnd(4);
        q.appendEnd(5);
        q.print_list();
        Node * a = q.findNode(3);
        q.insertPrev(a, 10);
        q.print_list();
    }
    catch (int declaration) {
        switch (declaration) {
            case -1:
                cout << "Не найдено число" << endl;
            case -2:
                cout << "в find_next - последний элемент" << endl;

        }

    }
}