#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

#define MAXV 15
#define INF 99999

typedef pair<string, int> si;
typedef multimap<string, si> msi;

msi adjList;

vector<string> v_names;

map<string, int> dist;

void bellman_ford(int V, string s) {
    dist[s] = 0;
    for (int i=1; i<V; i++) {
        for (vector<string>::iterator it = v_names.begin(); it != --v_names.end(); it++) {
            for(msi::iterator ti = adjList.lower_bound(*it); ti != adjList.upper_bound(*it); ti++) {
                si pair_s = ti->second;
                dist[pair_s.first] = min(dist[pair_s.first], dist[*it] + pair_s.second);
            }
        }
    }
}

void print_p(int V, string s) {
    for (vector<string>::iterator it = v_names.begin(); it != v_names.end(); it++) {
        cout << "SSSP(" << s << "," << *it << ") = " << dist[*it] << endl;
    }
}

bool verify_loop(int V) {
    for (vector<string>::iterator it = v_names.begin(); it != v_names.end(); it++) {
        for(msi::iterator ti = adjList.lower_bound(*it); ti != adjList.upper_bound(*it); ti++) {
            si pair_s = ti->second;
            if (dist[pair_s.first] = min(dist[pair_s.first], dist[*it] + pair_s.second)) {
                return true;
            }
        }
    }
    return false;
}

int main() {
    int V,E,Z;
    string X,Y;
    string IN, PATH;

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

    cin >> IN >> PATH;

    bellman_ford(V, IN);

    if (verify_loop(V)) {
        cout << "Possui loop negativo." << endl;
    } else {
        print_p(V, IN);
    }

    return 0;
}
