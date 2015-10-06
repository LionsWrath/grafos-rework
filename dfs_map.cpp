#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <map>
#include <algorithm>

using namespace std;

#define WHITE 0
#define GRAY 1
#define BLACK 2

#define MAXV 15

typedef pair<string, int> si;
typedef multimap<string, si> msi;

msi adjList;

vector<string> v_names;

map<string, int> dfs_num;
map<string, string> dfs_parent;

map<string, int> dfs_d;
map<string, int> dfs_f;

int time_c = 0;

void dfs(string u) {
    dfs_num[u] = GRAY;
    dfs_d[u] = ++time_c;

    for(msi::iterator it = adjList.lower_bound(u); it != adjList.upper_bound(u); it++) {
        //Verificar dados
        si pair_s = it->second;
        if(dfs_num[pair_s.first] == WHITE) {
            dfs_parent[pair_s.first] = u;
            dfs(pair_s.first);
        } else if (dfs_num[pair_s.first] == GRAY) {
            if (pair_s.first != dfs_parent[u]) {
                //Encontrando Aresta de Retorno
            } else {
                //Aresta pai bidirecional
            }
        } else if (dfs_num[pair_s.first] == BLACK) {
            //Aresta de Cruzamento
        }
    }

    dfs_num[u] = BLACK;
    dfs_f[u] = ++time_c;
}

void printTree(int V) {
    for (vector<string>::iterator it = v_names.begin(); it != v_names.end(); it++) {
        cout << "Vértices: ";
        cout << setw(2) << *it << " Tempo de Descoberta: ";
        cout << setw(2) << dfs_d[*it] << " Tempo de Término: ";
        cout << setw(2) << dfs_f[*it] << " Predecessor: ";

        if(!(dfs_parent[*it].empty())) {
            cout << setw(3) << dfs_parent[*it] << endl;
        } else {
            cout << setw(3) << "NIL " << endl;
        }
    }
}

int main() {
    int V,E;
    string X,Y;
    string IN;

    cin >> V >> E;

    for (int i=0; i<E; i++) {
        cin >> X >> Y;

        if(find(v_names.begin(), v_names.end(), X) == v_names.end()) v_names.push_back(X);
        if(find(v_names.begin(), v_names.end(), Y) == v_names.end()) v_names.push_back(Y);

        adjList.insert(make_pair(X,make_pair(Y,0)));
    }

    cin >> IN;

    dfs(IN);

    printTree(V);
    
    return 0;
}
