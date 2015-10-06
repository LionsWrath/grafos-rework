#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <map>
#include <queue>
#include <algorithm>

using namespace std;

#define MAXV 15

typedef pair<string, int> si;
typedef multimap<string, si> msi;

msi adjList;

vector<string> v_names;

map<string, int> bfs_dist;
map<string, string> bfs_parent;

void bfs(string s) {
    queue<string> q;

    q.push(s);
    bfs_dist[s] = 0;

    while(!q.empty()) {
        string u = q.front();
        q.pop();

        for(msi::iterator it = adjList.lower_bound(u); it != adjList.upper_bound(u); it++) {
            si pair_s = it->second;
            if(!bfs_dist.count(pair_s.first)) {
                bfs_dist[pair_s.first] = bfs_dist[u] + 1;
                bfs_parent[pair_s.first] = u;
                q.push(pair_s.first);
            }
        }
    }
}

void printPath(string s, string v) {
    if (s == v) {
        cout << s << endl;
    } else if (bfs_parent.find(v) == bfs_parent.end()) {
        cout << " NIL" << endl;
    } else {
        cout << v << " >> ";
        printPath (s, bfs_parent[v]); 
    }
}

void print(int V, string root) {
    for (vector<string>::iterator it = v_names.begin(); it != v_names.end(); it++) {
        cout << "Vértice: ";
        cout << setw(2) << *it << " Predecessor: ";
        if (bfs_parent.find(*it) != bfs_parent.end()) {
            cout << setw(3) << bfs_parent[*it] << " Distância de ";
        } else {
            cout << setw(3) << "NIL " << " Distância de ";
        }
        cout << setw(2) << root << ": ";

        if (bfs_dist.find(*it) != bfs_dist.end()) {
            cout << setw(3) << bfs_dist[*it] << endl;
        } else {
            cout << setw(3) << "INF" << endl;
        }
    }
}

int main () {
    int V,E;
    string X,Y;
    string root;

    cin >> V >> E;

    for(int i=0; i<E; i++) {
        cin >> X >> Y;

        if(find(v_names.begin(), v_names.end(), X) == v_names.end()) v_names.push_back(X);
        if(find(v_names.begin(), v_names.end(), Y) == v_names.end()) v_names.push_back(Y);

        adjList.insert(make_pair(X,make_pair(Y,0)));
    }
    
    cin >> root;


    bfs(root);

    print(V, root);

    cin >> X >> Y;

    printPath(X,Y);

    return 0;
}
