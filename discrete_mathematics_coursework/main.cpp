#include <bits/stdc++.h>


using vi = std::vector<int>;
using graph = std::vector<std::vector<int>>;

graph input_graph = {{}};
graph output_blocks = {{}};
std::set<int> hinges;
std::stack<int> stack;
int c = 0, count_blocks = 0;
int len_input_graph;


void input_matrix(int count, char * arg[]){
    std::ifstream in(arg[1]);
    in >> len_input_graph;
    for(int i = 0; i < len_input_graph; ++i){
        vi q;
        input_graph.push_back(q);

        for(int j = 0; j < len_input_graph;++j){
            int x;
            in >> x;
            if(x){
                input_graph[i + 1].push_back(j + 1);
            }
        }
    }
    in.close();
}

void newblock(int &y, int &x){
    count_blocks += 1;
    std::vector<int> q(0);
    output_blocks.push_back(q);
    output_blocks[count_blocks].push_back(x);
    int el;
    do{
        el = stack.top();
        stack.pop();
        if(std::find(output_blocks[count_blocks].begin(), output_blocks[count_blocks].end(), el) == std::end(output_blocks[count_blocks])){
            output_blocks[count_blocks].push_back(el);
        }
    }while(el != y);

}


void Blocks(vi & dnum , vi&low,  int &x){
    c += 1;
    dnum[x] = c;
    low[x] = c;
    stack.push(x);
    for(int y : input_graph[x]){
        if(dnum[y] == 0){
            Blocks(dnum, low,  y);
            low[x] = std::min(low[x], low[y]);
            if (low[y] == dnum[x]){
                newblock(y, x);
                //std::cout << "|" << dnum[x] << " " << x << "|\n";
                if(x != 1) hinges.insert(x);
                else{
                    int sum = 0;
                    for(std::vector<int>::size_type i = 0; i < input_graph[0].size(); ++i){
                        sum += input_graph[0][i];
                    }
                    if (sum == 1){
                        hinges.insert(x);
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
    int index_hinge = 0;
    for(int i: hinges){
        for(std::vector<int>::size_type j = 1; j  < output_blocks.size(); ++j){
            if(std::find(output_blocks[j].begin(), output_blocks[j].end(), i) != output_blocks[j].end()){
                tree[index_hinge][hinges.size() + j - 1] = 1;
                // std::cout << i << std::endl;
            }
        }
        ++index_hinge;
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
    for(int el : hinges){
        text += std::to_wstring(i) + L": " + std::to_wstring(el - 1) + L'\n';
        i += 1;
    }
    text += L"Блоки:\n";
    for(std::vector<int>::size_type j = 1; j < output_blocks.size(); ++j){
        text += std::to_wstring(i) + L" = ";
        for(int el: output_blocks[j]){
            text += std::to_wstring(el - 1) +  L", ";
        }
        text += L'\n';
        i += 1;
    }
    out << text;
    std::wstring colors = L"<Vertex_Colors>\n";
    out << colors;
    for(std::vector<int>::size_type i = tree.size() - count_blocks; i < tree.size(); ++i){
        out << i << L" red" << L'\n';
    }
    out.close();
}



int main(int argc, char * argv[]){
    input_matrix(argc, argv);

    vi dnum(len_input_graph + 1, 0);
    vi low(len_input_graph + 1, 0);
    for (int i = 1; i <= len_input_graph;++i){
        if(dnum[i] == 0){
            Blocks(dnum, low, i);
        }
    }
    graph tree(output_blocks.size() + hinges.size() - 1, vi(output_blocks.size() + hinges.size() - 1));
    bc_tree(tree);
    output(argc, argv, tree);
}
