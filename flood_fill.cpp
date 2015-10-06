#include <iostream>
#include <vector>
#include <iomanip>
#include <map>

using namespace std;

#define WHITE 0

#define MAXV 15

typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef map<int, int> mii;

vii adjList[MAXV];

mii dfs_num;

int numComponent;

void flood_fill(int u, int color) {
    dfs_num[u] = color;

    for(vii::iterator it = adjList[u].begin(); it != adjList[u].end(); it++) {
        if(dfs_num[it->first] == WHITE) {
            flood_fill(it->first, color);
        }
    }
}

int main() {
    int V,E,X,Y;

    cin >> V >> E;

    for (int i=0; i<E; i++) {
        cin >> X >> Y;

        adjList[X].push_back(make_pair(Y,0));
    }

    for (int i=1; i<=V; i++) {
        if (dfs_num[i] == WHITE) {
            flood_fill(i, ++numComponent);
        }
    }

    for (int i=1; i<=V; i++) {
        cout << "Vertex " << i << " has color " << dfs_num[i] << endl;
    }
}
