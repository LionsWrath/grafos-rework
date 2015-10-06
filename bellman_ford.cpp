#include <iostream>
#include <iomanip>
#include <vector>
#include <map>

using namespace std;

#define MAXV 15
#define INF 99999

typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef map<int, int> mii;

vii adjList[MAXV];

mii dist;

void bellman_ford(int V, int s) { 
    dist[s] = 0;
    for (int i=1; i<V; i++) {
        for (int u=1; u<V; u++) {
            for(vii::iterator it = adjList[u].begin(); it != adjList[u].end(); it++) {
                dist[it->first] = min(dist[it->first], dist[u] + it->second);
            }
        }
    }
}

void print_p(int V, int s) {
    for (int i=1; i<=V; i++) {
        cout << "SSSP(" << s << "," << i << ") = " << dist[i] << endl;
    }
}

bool verify_loop(int V) {
    for (int u=1; u<=V;  u++) {
        for (vii::iterator it = adjList[u].begin(); it != adjList[u].end(); it++) {
            if (dist[it->first] > dist[u] + it->second) {
                return true;
            }
        }
    }
    return false;
}

int main() {
    int V,E,X,Y,Z;
    int IN, PATH;

    cin >> V >> E;

    for (int i=1; i<=V; i++) {
        dist[i] = INF;
    }

    for (int i=0; i<E; i++) {
        cin >> X >> Y >> Z;

        adjList[X].push_back(make_pair(Y,Z));
    }

    cin >> IN >> PATH;

    bellman_ford(V,IN);
    
    if (verify_loop(V)) {
        cout << "Possui loop negativo." << endl;
    } else {
        print_p(V,IN);
    }

    return 0; 
}
