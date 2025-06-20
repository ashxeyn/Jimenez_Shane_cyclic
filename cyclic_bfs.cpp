#include <iostream>
using namespace std;

#define N 20

struct Queue {
    int items[N*N];
    int front, rear;
    Queue() { front = 0; rear = 0; }
    bool empty() { return front == rear; }
    void push(int x) { items[rear++] = x; }
    int pop() { return items[front++]; }
};

bool sameCycle(int a[], int lenA, int b[], int lenB) {
    if (lenA != lenB) return false;
    for (int shift = 0; shift < lenA; ++shift) {
        bool match = true;
        for (int i = 0; i < lenA; ++i) {
            if (a[i] != b[(i + shift) % lenA]) {
                match = false;
                break;
            }
        }
        if (match) return true;
    }
    return false;
}

void printCycle(int parent[], int start, int end) {
    static int foundCycles[N*N][N];
    static int foundLens[N*N];
    static int numCycles = 0;
    static int counter = 1;
    int cycle[N], idx = 0;
    int v = end;
    cycle[idx++] = v;
    while (v != start && v != -1) {
        v = parent[v];
        cycle[idx++] = v;
    }
    if (v == -1) return;
    for (int i = 0; i < idx / 2; ++i) {
        int tmp = cycle[i];
        cycle[i] = cycle[idx - 1 - i];
        cycle[idx - 1 - i] = tmp;
    }
    for (int i = 0; i < numCycles; ++i) {
        if (sameCycle(cycle, idx, foundCycles[i], foundLens[i]))
            return;
    }
    for (int i = 0; i < idx; ++i) foundCycles[numCycles][i] = cycle[i];
    foundLens[numCycles] = idx;
    numCycles++;
    cout << "Vertices in cycle " << counter++ << ": ";
    for (int i = 0; i < idx; ++i) {
        cout << char('A' + cycle[i]) << " ";
    }
    cout << endl;
}

void bfs(int graph[N][N], int start, bool &foundCycle) {
    bool visited[N] = {0};
    int parent[N];
    for (int i = 0; i < N; ++i) parent[i] = -1;
    Queue q;
    q.push(start);
    visited[start] = true;
    while (!q.empty()) {
        int v = q.pop();
        for (int u = 0; u < N; ++u) {
            if (graph[v][u]) {
                if (!visited[u]) {
                    visited[u] = true;
                    parent[u] = v;
                    q.push(u);
                } else if (parent[v] != u) { 
                    printCycle(parent, u, v);
                    foundCycle = true;
                }
            }
        }
    }
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
    bool foundCycle = false;
    for (int i = 0; i < N; ++i) {
        bfs(graph, i, foundCycle);
    }
    if (foundCycle) {
        cout << "\nYazz queen yo graph is cyclic!" << endl;
    } else {
        cout << "Graph is not cyclic :(" << endl;
    }
    return 0;
} 