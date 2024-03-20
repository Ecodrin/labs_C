#include <iostream>


typedef int Data;
using namespace std;



struct Node{
    Data val;
    Node * next;
    Node(Data v = 0, Node * x = nullptr): val(v), next(x){};
};

class LList{
public:
    friend Node;
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

    void appendEnd(Data a){
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

    Node * findNode(Data val){
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

    void insertNext(Node *p, Data val){
        Node * q = new Node;
        q->val = val;
        q->next = p->next;
        p->next = q;
    }

    void insertPrev(Node * ptn, Data val){
        Node * a = findPrev(ptn);
        insertNext(a, val);
    }

    void deleteNode(Node *ptn){
        Node * a = findPrev(ptn);
        a->next = ptn->next;
        delete ptn;
    }
    
    void swap(Node * prev, Node * next){
        int x = prev->val;
        prev->val = next->val;
        next->val = x;
        
    }
    
    void appendStart(Data x){
        Node * new_el = new Node(x, head->next);
        head = new_el;
    }

    void operator+=(int x){
        Node * q = new Node;
        q->val = x;
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
    LList& operator+(int x){
        Node * q = new Node;
        q->val = x;
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
        return *this;
    }

};


int main(){
    LList list;
    for(int i = 0; i < 10; i++){
        list += i;
    }

    Node * ptn;

    list.print_list();
    list.appendStart(12);
    Node * p = list.findNode(4);
    Node * n = list.findNode(6);
    list.swap(p, n);
    cout << "-----------------------------------" << endl;
    list.print_list();
    
}
