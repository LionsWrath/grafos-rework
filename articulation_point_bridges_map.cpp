#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

#define WHITE 0

#define MAXV 15


typedef pair<string, int> si;
typedef multimap<string, si> msi;

msi adjList;

vector<string> v_names;

map<string, int> dfs_num;
map<string, int> dfs_low;
map<string, string> dfs_parent;

int dfsNumberCounter;
string dfsRoot;
int rootChildren;

map<string, bool> articulation_vertex;

void articulation(string u) {
    dfs_low[u] = dfs_num[u] = dfsNumberCounter++;

    for(msi::iterator it = adjList.lower_bound(u); it != adjList.upper_bound(u); it++) {
        si pair_s = it->second;
        
        if (dfs_num[pair_s.first] == WHITE) {
            dfs_parent[pair_s.first] = u;

            if (u == dfsRoot) 
                rootChildren++;

            articulation(pair_s.first);

            if (dfs_low[pair_s.first] >= dfs_num[u])
                articulation_vertex[u] = true;

            if (dfs_low[pair_s.first] > dfs_num[u]) 
                cout << "Bridge: (" << u << "," << pair_s.first << ") " << endl;

            dfs_low[u] = min(dfs_low[u], dfs_low[pair_s.first]);
        
        } else if (pair_s.first != dfs_parent[u]) {
            dfs_low[u] = min(dfs_low[u], dfs_num[pair_s.first]);
        }
    }
}

int main() {
    int V,E;
    string X,Y;
    
    cin >> V >> E;

    for (int i=0; i<E; i++) {
        cin >> X >> Y;

        if(find(v_names.begin(), v_names.end(), X) == v_names.end()) v_names.push_back(X);
        if(find(v_names.begin(), v_names.end(), Y) == v_names.end()) v_names.push_back(Y);
    
        adjList.insert(make_pair(X,make_pair(Y,0)));
        adjList.insert(make_pair(Y,make_pair(X,0)));
    }

    for (vector<string>::iterator it = v_names.begin(); it != v_names.end(); it++) {
        if (dfs_num[*it] == WHITE) {
            dfsRoot = *it;
            rootChildren = 0;
            articulation(*it);
            articulation_vertex[dfsRoot] = (rootChildren > 1);
        }
    }

    cout << "Articulation Points: " << endl;
    for (vector<string>::iterator it = v_names.begin(); it != v_names.end(); it++) {
        if (articulation_vertex[*it])
            cout << "Vertex: " << *it << endl;
    }

    return 0;
}
