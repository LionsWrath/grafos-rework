#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
#include <queue>
#include <functional>
#include <map>
#include <algorithm>

using namespace std;

#define WHITE 0;

#define MAXV 15
#define INF 99999

typedef pair<string, int> si;
typedef pair<int, string> is;
typedef multimap<string, si> msi;

msi adjList;

vector<string> v_names;

map<string, int> dist;
map<string, string> parent;

void dijkstra(string s) {
    dist[s] = 0;
    priority_queue<is, vector<is>, greater<is> > pq;
    pq.push(is(0,s));

    while(!pq.empty()) {
        is top = pq.top();
        pq.pop();

        int d = top.first;
        string u = top.second;

        if (d == dist[u]) {
            for(msi::iterator it = adjList.lower_bound(u); it != adjList.upper_bound(u); it++) {
                si pair_s = it->second;
                string v = pair_s.first;
                int weight_uv = pair_s.second;

                if (dist[u] + weight_uv < dist[v]) {
                    dist[v] = dist[u] + weight_uv;
                    parent[v] = u;
                    pq.push(is(dist[v], v));
                }
            }
        }
    }
}

int calculate_d(string o, string v) {
    int aux;
    if (o == v) {
        return 0;
    } else if (parent[v].empty()) {
        return -INF;
    } else {
        aux = calculate_d(o, parent[v]);
        return ++aux;
    }
}

void print_p(int V, string root) {
    int d;
    for(vector<string>::iterator it = v_names.begin(); it != v_names.end(); it++) {
        d = calculate_d(root, *it);
        if(d >= 0) {
            cout << "Vertex: " << *it << " Distance from " << root << ": " << d << endl;
        } else {
            cout << "Vertex: " << *it << " Distance from " << root << ": NIL" << endl;
        }
    }
}

int main() {
    int V,E,Z;
    string X,Y;
    string IN;

    cin >> V >> E;

    for (int i=0; i<E; i++) {
        cin >> X >> Y >> Z;

        if(find(v_names.begin(), v_names.end(), X) == v_names.end()) v_names.push_back(X);
        if(find(v_names.begin(), v_names.end(), Y) == v_names.end()) v_names.push_back(Y);

        adjList.insert(make_pair(X,make_pair(Y,Z)));
    }

    for (vector<string>::iterator it = v_names.begin(); it != v_names.end(); it++) {
        dist[*it] = INF;
    }

    cin >> IN;

    dijkstra(IN);
    print_p(V, IN);

    return 0;
}
