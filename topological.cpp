#include <iostream>
#include <iomanip>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

#define WHITE 0
#define BLACK 1

#define MAXV 15

typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef map<int, int> mii;

vii adjList[MAXV];

vector<int> topologicalSort;

mii dfs_num;

void topo_visit(int u) {
    dfs_num[u] = BLACK;

    for(vii::iterator it = adjList[u].begin(); it != adjList[u].end(); it++) {
        if(dfs_num[it->first] == WHITE) {
            topo_visit(it->first);
        }
    }
    topologicalSort.push_back(u);
}

int main() {
    int V,E,X,Y;
    
    cin >> V >> E;

    for (int i=0; i< E; i++) {
        cin >> X >> Y;

        adjList[X].push_back(make_pair(Y,0));
    }

    for (int i=0; i<V; i++) { 
        if (dfs_num[i] == WHITE) {
            topo_visit(i);
        }
    }

    reverse(topologicalSort.begin(), topologicalSort.end());

    for (int i=0; i<topologicalSort.size() - 1; i++) {
        cout << topologicalSort[i] << " ";
    }
    cout << endl;

    return 0;
}   

