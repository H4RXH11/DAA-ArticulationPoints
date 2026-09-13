//HARSHIT SAH 25/DA/032

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

vector<vector<int>> adj;
vector<int> disc, low, parent;
vector<bool> visited, articulation;
int timer = 0;

void dfs(int u) {
    visited[u] = true;
    disc[u] = low[u] = ++timer;

    int children = 0;

    for (int v : adj[u]) {
        if (!visited[v]) {
            parent[v] = u;
            children++;

            dfs(v);

            low[u] = min(low[u], low[v]);

            if (parent[u] == -1 && children > 1)
                articulation[u] = true;

            if (parent[u] != -1 && low[v] >= disc[u])
                articulation[u] = true;
        }
        else if (v != parent[u]) {
            low[u] = min(low[u], disc[v]);
        }
    }
}

int main() {
    int V, E;
    cin >> V >> E;

    adj.resize(V);
    disc.assign(V, -1);
    low.assign(V, -1);
    parent.assign(V, -1);
    visited.assign(V, false);
    articulation.assign(V, false);

    for (int i = 0; i < E; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    for (int i = 0; i < V; i++) {
        if (!visited[i])
            dfs(i);
    }

    cout << "The articulation points in the graph are: ";

    bool found = false;

    for (int i = 0; i < V; i++) {
        if (articulation[i]) {
            cout << i << " ";
            found = true;
        }
    }

    if (!found)
        cout << "There are no articulation points.";

    cout << endl;

    return 0;
}
