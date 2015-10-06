#include <iostream>
#include <iomanip>
#include <stack>
#include <set>
#include <vector>
#include <map>

using namespace std;

#define WHITE 0

#define MAXV 15

typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef map<int, int> mii;

vii adjList[MAXV];

stack<int> dfs_scc;
set<int> in_stack;

mii dfs_num;
mii dfs_low;

int dfsNumberCounter;

void scc(int u) {
    dfs_low[u] = dfs_num[u] = dfsNumberCounter++;
    
    dfs_scc.push(u);
    in_stack.insert(u);

    for(vii::iterator it = adjList[u].begin(); it != adjList[u].end(); it++) {
        if (dfs_num[it->first] == WHITE) 
            scc(it->first);

        if (in_stack.find(it->first) != in_stack.end()) 
            dfs_low[u] = min(dfs_low[u], dfs_low[it->first]);

    }

    if (dfs_low[u] == dfs_num[u]) {
        cout <<"SCC: ";
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

int main () {
    int V,E,X,Y;
    int IN;

    cin >> V >> E;

    for (int i=0; i<E; i++) {
        cin >> X >> Y;

        adjList[X].push_back(make_pair(Y,0));
    }

    cin >> IN;

    scc(IN);

    return 0;
}
