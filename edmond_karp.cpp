#include <iostream>
#include <iomanip>
#include <queue>
#include <map>

#define MAXV 15
#define INF 99999

using namespace std;

typedef pair<int, int> ii;
typedef vector<ii> vii;

vii adjList[MAXV];
//Matriz de adjacências utilizada para guardar capacidade residual
int adjMat[MAXV][MAXV];

map<int, int> p;

int max_flow = 0;
int f, s, t;

void augmentPath(int v, int minEdge) {
    if (v == s) {
        f = minEdge;
        return;
    } else if (p.count(v)) { //melhora se existe um caminho
        //Matriz de Adjacência para otimizar o acesso
        augmentPath(p[v], min(minEdge, adjMat[p[v]][v]));
        adjMat[p[v]][v] -= f; //arestas de avanço diminui
        adjMat[v][p[v]] += f; //arestas de retorno aumenta
    }
}

void edmond_karp() {
    while (1) {
        f = 0;

        queue<int> q;
        map<int, int> dist;
        q.push(s);
        dist[s] = 0;
        while (!q.empty()) {
            int u = q.front();
            q.pop();

            if (u == t) break;

            for(vii::iterator it = adjList[u].begin(); it != adjList[u].end(); it++) {
                if (adjMat[u][it->first] > 0 && !dist.count(it->first)) {
                    dist[it->first] = dist[u] + 1;
                    q.push(it->first);
                    p[it->first] = u;
                }
            }
        }

        augmentPath(t, INF);
        if (f == 0) break;
        max_flow += f;
    }
}

int main() {
    int V,E,X,Y,Z;

    cin >> V >> E;

    for (int i=0; i<E; i++) {
        cin >> X >> Y >> Z;

        adjList[X].push_back(make_pair(Y,Z));
        adjMat[X][Y] = Z;
    }

    cin >> s >> t;

    edmond_karp();

    cout << max_flow << endl;

    return 0;
}
