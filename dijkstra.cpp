#include <iostream>
#include <iomanip>
#include <vector>
#include <queue>
#include <functional>
#include <map>

using namespace std;

#define WHITE 0

#define MAXV 15
#define INF 99999

typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef map<int, int> mii;

vii adjList[MAXV];

map<int, int> dist;
map<int, int> parent;

void dijkstra(int s) {
    dist[s] = 0;
    priority_queue<ii, vector<ii>, greater<ii> > pq; 
    pq.push(ii(0,s));

    while(!pq.empty()) {
        ii top = pq.top();
        pq.pop();

        int d = top.first;
        int u = top.second;

        if (d == dist[u]) {
            for(vii::iterator it = adjList[u].begin(); it != adjList[u].end(); it++) {
                int v = it->first;
                int weight_uv = it->second;

                if (dist[u] + weight_uv < dist[v]) {
                    dist[v] = dist[u] + weight_uv;
                    parent[v] = u;
                    pq.push(ii(dist[v], v));
                }
            }
        }
    }
}

int calculate_d(int o, int v) {
    int aux;
    if (o == v) {
        return 0;
    } else if (parent[v] == -1) {
        return -INF;
    } else {
        aux = calculate_d(o, parent[v]);
        return ++aux;
    }
}

void print_p(int V, int root) {
    int d;
    for (int u = 1; u <= V; u++) {
        d = calculate_d(root, u);
        if (d >= 0) {
            cout << "Vertex: " << u << " Distance from " << root << ": " << d << endl;
        } else {
            cout << "Vertex: " << u << " Distance from " << root << ": NIL" << endl;
        }
    }
}

int main() {
    int V,E,X,Y,Z;
    int IN;

    cin >> V >> E;

    for (int i=1; i<=V; i++) {
        dist[i] = INF;
        parent[i] = -1;
    }

    for (int i=0; i<E; i++) {
        cin >> X >> Y >> Z;

        adjList[X].push_back(make_pair(Y,Z));
    }

    cin >> IN;

    dijkstra(IN);
    print_p(V,IN);

    return 0;
}
