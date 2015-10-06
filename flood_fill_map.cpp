#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
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

int numComponent;

void flood_fill(string u, int color) {
    dfs_num[u] = color;

    for(msi::iterator it = adjList.lower_bound(u); it != adjList.upper_bound(u); it++) {
        si pair_s = it->second;

        if(dfs_num[pair_s.first] == WHITE){
            flood_fill(pair_s.first, color);
        }
    }
}

int main() {
    int V,E;
    string X,Y;

    cin >> V >> E;

    for (int i=0; i<E; i++){
        cin >> X >> Y;

        if(find(v_names.begin(), v_names.end(), X) == v_names.end()) v_names.push_back(X);
        if(find(v_names.begin(), v_names.end(), Y) == v_names.end()) v_names.push_back(Y);

        adjList.insert(make_pair(X,make_pair(Y,0)));
    }

    for (vector<string>::iterator it = v_names.begin(); it != v_names.end();it++) {
        if (dfs_num[*it] == WHITE) {
            flood_fill(*it, ++numComponent);
        }
    }

    for (vector<string>::iterator it = v_names.begin(); it != v_names.end();it++) {
        cout << "Vertex " << *it << " has color " << dfs_num[*it] << endl; 
    }
}
