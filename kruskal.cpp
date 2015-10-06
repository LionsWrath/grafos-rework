#include <iostream>
#include <iomanip>
#include <queue>
#include <vector>

using namespace std;

typedef pair<int, int> ii;

priority_queue< pair<int, ii> > EdgeList; //ordem decrescente de peso
vector<int> pset(1000);

int mst_cost = 0;

void initSet(int _size) {
    pset.resize(_size);
    for (int i = 0; i <= _size - 1; i++) {
        pset[i] = i;
    }
}

int findSet(int i) { return (pset[i] == i) ? i : (pset[i] = findSet(pset[i])); } //Path compression

void unionSet(int i, int j) { pset[findSet(i)] = findSet(j); }

bool isSameSet(int i, int j) { return findSet(i) == findSet(j); }

void kruskal(int V) { 
    initSet(V); //verificar esse método

    while (!EdgeList.empty()) {
        pair<int, ii> front = EdgeList.top();
        EdgeList.pop();
        if (!isSameSet(front.second.first, front.second.second)) {
            mst_cost += (-front.first);
            unionSet(front.second.first, front.second.second);
        }
    }
}

int main() {
    int V,E,X,Y,Z;
    
    cin >> V >> E;

    for (int i=0; i < E; i++) {
        cin >> X >> Y >> Z;

        EdgeList.push(make_pair(-Z, make_pair(X,Y)));
    }

    kruskal(V);

    cout << mst_cost << endl;
    
    return 0;
}
