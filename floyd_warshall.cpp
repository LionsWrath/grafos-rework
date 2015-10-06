#include <iostream>
#include <iomanip>
#include <algorithm>

#define MAXV 15
#define INF 99999

using namespace std;

int adjMat[MAXV][MAXV];
int parent[MAXV][MAXV];

void printPath(int i, int j) {
    if (i != j) printPath(i, parent[i][j]);
    cout << " " << j;
}

void floyd_warshall(int V) {
    
    for (int k=0; k<V; k++) {
        for (int i=0; i<V; i++) {
            for (int j=0; j<V; j++) {
                if (adjMat[i][j] > adjMat[i][k] + adjMat[k][j] ) { 
                    adjMat[i][j] = adjMat[i][k] + adjMat[k][j];
                    parent[i][j] = parent[k][j]; 
                }
            }
        }
    }
}

int main () {
    int V,E,X,Y,Z;

    cin >> V >> E;

    for (int i=0; i<V; i++) {
        for (int j=0; j<V; j++) {
            if (i == j) {
                adjMat[i][j] = 0;
            } else {
                adjMat[i][j] = INF;
            }
            parent[i][j] = -1;
        }
    }

    for (int i=0; i<E; i++) {
        cin >> X >> Y >> Z;

        adjMat[X][Y] = Z;
        parent[X][Y] = X;
    }

    floyd_warshall(V);

    for (int i=0; i<V; i++) {
        for (int j=0; j<V; j++) {
            cout << adjMat[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}
