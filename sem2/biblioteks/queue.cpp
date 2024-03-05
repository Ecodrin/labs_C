#include <iostream>


using namespace std;


class Queue{
public:
    int len;
    int *data;
    int start;
    int depth;

    Queue(int l = 1): len(l), data(new int [l]), start(0), depth(0) {};

    ~Queue(){
        if(len != 0) delete [] data;
        data = nullptr;
        depth = 0;
        start = 0;
        len = 0;
    }

    void push(int x){
        if(depth == len){
            int * new_data = new int [len + 10];
            for(int i = 0; i < depth; ++i){
                new_data[i] = data[(start + i) % len];
            }
            delete [] data;
            data = new int [len + 10];
            for(int i = 0; i < depth; ++i){
                data[i] = new_data[(start + i) % (len + 10)];
            }
            delete [] new_data;
            len += 10;
        }
        data[(start + depth) % len] = x;
        depth += 1;
    }
    int pop_front(){
        start += 1;
        depth -= 1;
        return data[start - 1];
    }

    void display() const{
        for(int i = 0; i < depth; ++i){
            cout << data[(i + start) % len] << " ";
        }
        cout << '\n';
    }

    int pop_back(){
        depth -= 1;

        return data[depth];
    }

};
