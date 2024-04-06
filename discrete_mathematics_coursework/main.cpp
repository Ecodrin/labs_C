#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <set>

using vi = std::vector<int>;
using graph = std::vector<std::vector<int>>;

graph a = {{}};
graph b = {{}};
std::set<int> sh;
std::stack<int> s;
int c = 0, k = 0;
int n;


void input_matrix(){
    std::cin >> n;
    for(int i = 0; i < n; ++i){
        vi q;
        a.push_back(q);

        for(int j = 0; j < n;++j){
            int x;
            std::cin >> x;
            if(x){
                a[i + 1].push_back(j + 1);
            }
        }
    }
}


void newblock(int &y, int &x){
    k += 1;
    std::vector<int> q(0);
    b.push_back(q);
    b[k].push_back(x);
    int z;
    do{
        z = s.top();
        s.pop();
        if(std::find(b[k].begin(), b[k].end(), z) == std::end(b[k])){
            b[k].push_back(z);
        }
    }while(z != y);

}


void Blocks(vi &dnum , vi&low,  int &x){
    c += 1;
    dnum[x] = c;
    low[x] = c;
    s.push(x);
    for(int y : a[x]){
        if(dnum[y] == 0){
            Blocks(dnum, low,  y);
            low[x] = std::min(low[x], low[y]);
            if (low[y] == dnum[x]){
                newblock(y, x);
                //std::cout << "|" << dnum[x] << " " << x << "|\n";
                if(x != 1) sh.insert(x);
                else{
                    int sum = 0;
                    for(std::vector<int>::size_type i = 0; i < a[0].size(); ++i){
                        sum += a[0][i];
                    }
                    if (sum == 1){
                        sh.insert(x);
                    }
                }
            }
        }
        else{
            low[x] = std::min(low[x], dnum[y]);
        }
    }
}

void bc_tree(graph&tree){
    int ii = 0;
    for(int i: sh){
        for(std::vector<int>::size_type j = 1; j < b.size(); ++j){
            if(std::find(b[j].begin(), b[j].end(), i) != b[j].end()){
                tree[ii][sh.size() + j - 1] = 1;
            }
        }
        ++ii;
    }
}



int main(){
    input_matrix();

    vi dnum(n + 1, 0);
    vi low(n + 1, 0);
    for (int i = 1; i <= n;++i){
        if(dnum[i] == 0){
            Blocks(dnum, low, i);
        }
    }
    graph tree(b.size() + sh.size() - 1, vi(b.size() + sh.size() - 1));
    bc_tree(tree);
    for(std::vector<int>::size_type i = 0; i < tree.size(); ++i){
        for(std::vector<int>::size_type j = 0;j < tree[i].size(); ++j){
            std::cout << tree[i][j] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}