#include <iostream>
#include <vector>
#include <iomanip>
#include <map>

using namespace std;

#define WHITE 0
#define GRAY 1
#define BLACK 2

#define MAXV 15

typedef pair<int, int> ii; // v, peso
typedef vector<ii> vii;
typedef map<int, int> mii;

vii adjList[MAXV]; //Lista de Adjacência

mii dfs_num; 
mii dfs_parent; //Vetor de pais

mii dfs_d;
mii dfs_f;

int time_c = 0;

void dfs(int u) {
    dfs_num[u] = GRAY;
    dfs_d[u] = ++time_c;

    for(vii::iterator it = adjList[u].begin(); it != adjList[u].end(); it++) {
        //Encontrando Arestas de Árvore
        if (dfs_num[it->first] == WHITE) {
            dfs_parent[it->first] = u;
            dfs(it->first);
        } else if (dfs_num[it->first] == GRAY) {    
            if (it->first != dfs_parent[u]) {
                //Encontrando Aresta de Retorno
            } else {
                //Aresta pai bidirecional
            }
        } else if (dfs_num[it->first] == BLACK) {
            //Aresta de Cruzamento
        }
    }

    dfs_num[u] = BLACK;
    dfs_f[u] = ++time_c;
}

void printTree(int V) {
    for (int i = 1; i <= V; i++) {
        cout << "Vértices: ";
        cout << setw(2) << i << " Tempo de Descoberta: ";
        cout << setw(2) << dfs_d[i] << " Tempo de Término: ";
        cout << setw(2) << dfs_f[i] << " Predecessor: ";

        if (dfs_parent[i] >= 0) {
            cout << setw(3) << dfs_parent[i] << endl;
        } else {
            cout << setw(3) << "NIL " << endl;
        }
    }
}

int main() {
    int V,E,X,Y;
    int IN;

    cin >> V >> E;

    for (int i=0; i<E; i++) {
        cin >> X >> Y;

        adjList[X].push_back(make_pair(Y,0));
    }

    cin >> IN;

    dfs(IN);

    printTree(V);

    return 0;
}
