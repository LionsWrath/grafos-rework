#include <iostream>
#include <iomanip>
#include <string>
#include <stack>
#include <set>
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

stack<string> dfs_scc;
set<string> in_stack;

map<string, int> dfs_num;
map<string, int> dfs_low;

int dfsNumberCounter;

void scc(string u) {
    dfs_low[u] = dfs_num[u] = dfsNumberCounter++;

    dfs_scc.push(u);
    in_stack.insert(u);

    for(msi::iterator it = adjList.lower_bound(u); it != adjList.upper_bound(u); it++) {
        si pair_s = it->second;
        if (dfs_num[pair_s.first] == WHITE) 
            scc(pair_s.first);

        if (in_stack.find(pair_s.first) != in_stack.end()) 
            dfs_low[u] = min(dfs_low[u], dfs_low[pair_s.first]);
    }

    if (dfs_low[u] == dfs_num[u]) {
        cout << "SCC: ";
        while (!dfs_scc.empty() && (dfs_scc.top() != u)) {
            cout << dfs_scc.top() << " ";
            in_stack.erase(dfs_scc.top());
            dfs_scc.pop();
        }
        cout << dfs_scc.top() << endl;
        in_stack.erase(dfs_scc.top());
        dfs_scc.pop();
    }
}

int main() {
    int V,E;
    string X,Y;
    string IN;

    cin >> V >> E;

    for (int i=0; i<E; i++) {
        cin >> X >> Y;

        if(find(v_names.begin(), v_names.end(), X) == v_names.end()) v_names.push_back(X);
        if(find(v_names.begin(), v_names.end(), Y) == v_names.end()) v_names.push_back(Y);
    
        adjList.insert(make_pair(X,make_pair(Y,0)));
    }

    cin >> IN;
    
    scc(IN);

    return 0;
}
