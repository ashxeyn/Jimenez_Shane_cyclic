#include <iostream>
using namespace std;

#define N 20

void printCycle(int parent[], int start, int end) {
    static int counter = 1;
    int cycle[N], idx = 0;
    int v = end;
    cycle[idx++] = v;
    while (v != start && v != -1) {
        v = parent[v];
        cycle[idx++] = v;
    }
    if (v == -1) return;
    cout << "Vertices in cycle " << counter++ << ": ";
    for (int i = idx - 1; i >= 0; --i) {
        cout << char('A' + cycle[i]) << " ";
    }
    cout << endl;
}

void dfs(int graph[N][N], int v, bool visited[], bool recStack[], int parent[], bool &foundCycle) {
    visited[v] = true;
    recStack[v] = true;
    for (int u = 0; u < N; ++u) {
        if (graph[v][u]) {
            if (!visited[u]) {
                parent[u] = v;
                dfs(graph, u, visited, recStack, parent, foundCycle);
            } else if (recStack[u]) {
                printCycle(parent, u, v);
                foundCycle = true;
            }
        }
    }
    recStack[v] = false;
}

int main() {
    int graph[N][N] = {
        {0,0,1,0,0,0,0},
        {0,0,1,0,0,0,0},
        {0,0,0,0,1,1,1},
        {1,0,0,0,1,0,0},
        {1,0,0,0,0,0,0},
        {0,1,0,0,0,0,0},
        {0,0,0,0,0,0,0}
    };
    bool visited[N] = {0};
    bool recStack[N] = {0};
    int parent[N];
    for (int i = 0; i < N; ++i) parent[i] = -1;
    bool foundCycle = false;
    for (int i = 0; i < N; ++i) {
        if (!visited[i]) {
            dfs(graph, i, visited, recStack, parent, foundCycle);
        }
    }
    if (foundCycle) {
        cout << "\nYazz queen yo graph is cyclic!" << endl;
    } else {
        cout << "Graph is not cyclic :(" << endl;
    }
    return 0;
} 