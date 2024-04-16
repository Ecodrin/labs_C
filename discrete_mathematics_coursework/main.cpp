#include <iostream>
#include <fstream>
#include <string>
#include <bits/stdc++.h>


using vi = std::vector<int>;
using graph = std::vector<std::vector<int>>;

graph a = {{}};
graph b = {{}};
std::set<int> sh;
std::stack<int> s;
int c = 0, k = 0;
int n;


void input_matrix(int count, char * arg[]){
    std::ifstream in(arg[1]);
    in >> n;
    for(int i = 0; i < n; ++i){
        vi q;
        a.push_back(q);

        for(int j = 0; j < n;++j){
            int x;
            in >> x;
            if(x){
                a[i + 1].push_back(j + 1);
            }
        }
    }
    in.close();
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
                // std::cout << i << std::endl;
            }
        }
        ++ii;
    }
}


void output(int count, char * arg[], graph & tree){
    std::wofstream out;
    out.imbue(std::locale(std::locale(), new std::codecvt_utf8<wchar_t, 0x10ffff, std::generate_header>));
    out.open(arg[2]);
    out << tree.size() << L'\n';
    for(std::vector<int>::size_type i = 0; i < tree.size(); ++i){
        for(std::vector<int>::size_type j = 0;j < tree[i].size(); ++j){
            out << tree[i][j] << " ";
        }
        out << L'\n';
    }
    // std::cout << c << " " << k << " " << n << std::endl;

    /*
    Зеленые вершины - шарниры
    Красные - блоки
    
    */
    std::wstring text = L"<Text>\nШарниры:\nЗеленые вершины - шарниры\nКрасные - блоки\n";
    int i = 0;
    for(int el : sh){
        text += std::to_wstring(i) + L": " + std::to_wstring(el - 1) + L'\n';
        i += 1;
    }
    text += L"Блоки:\n";
    for(std::vector<int>::size_type j = 1; j < b.size(); ++j){
        text += std::to_wstring(i) + L" = ";
        for(int el: b[j]){
            text += std::to_wstring(el - 1) +  L", ";
        }
        text += L'\n';
        i += 1;
    }
    out << text;
    std::wstring colors = L"<Vertex_Colors>\n";
    out << colors;
    for(std::vector<int>::size_type i = tree.size() - k; i < tree.size(); ++i){
        out << i << L" red" << L'\n';
    }
    out.close();
}



int main(int argc, char * argv[]){
    input_matrix(argc, argv);

    vi dnum(n + 1, 0);
    vi low(n + 1, 0);
    for (int i = 1; i <= n;++i){
        if(dnum[i] == 0){
            Blocks(dnum, low, i);
        }
    }
    graph tree(b.size() + sh.size() - 1, vi(b.size() + sh.size() - 1));
    bc_tree(tree);
    output(argc, argv, tree);
}