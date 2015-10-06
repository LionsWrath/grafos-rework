#include <iostream>
#include <vector>
#include <iomanip>
#include <map>
#include <queue> 

#define MAXV 15

using namespace std;

typedef pair<int, int> ii;
typedef vector<ii> vii;

vii adjList[MAXV];

map<int, int> bfs_dist;
map<int, int> bfs_parent;

void bfs(int s) {
    queue<int> q; 

    q.push(s);
    bfs_dist[s] = 0;

    while(!q.empty()) {
        int u = q.front();
        q.pop();

        for(vii::iterator it = adjList[u].begin(); it != adjList[u].end(); it++) {
            if (!bfs_dist.count(it->first)) {
                bfs_dist[it->first] = bfs_dist[u] + 1;
                bfs_parent[it->first] = u;
                q.push(it->first);
            }
        }
    }
}

void printPath(int s, int v) {
    if (s == v) {
        cout << s << endl;
    } else if (bfs_parent.find(v) == bfs_parent.end()) {
        cout << "No Path" << endl;
    } else {
        printPath (s,bfs_parent[v]);
        cout << v << endl;
    }
}

void print(int V, int root) {
    for (int i = 1; i <= V; i++) {
        cout << "Vértice: ";
        cout << setw(2) << i << " Predecessor: ";
        if (bfs_parent.find(i) != bfs_parent.end()) {
            cout << setw(3) << bfs_parent[i] << " Distância de ";
        } else {
            cout << setw(3) << "NIL " << " Distância de ";
        }
        cout << setw(2) << root << ": ";

        if (bfs_dist.find(i) != bfs_dist.end()) {
            cout << setw(3) << bfs_dist[i] << endl;
        } else {
            cout << setw(3) << "INF" << endl;
        }
    }
}

int main () {
    int V,E,X,Y;
    int root;

    cin >> V >> E;

    for (int i=0; i<E; i++) {
        cin >> X >> Y;

        adjList[X].push_back(make_pair(Y,0));
    }

    cin >> root;

    bfs(root);

    print(V, root);

    return 0;
}
