#include <iostream>
#include <vector>
#include <queue>

using namespace std;

void dijkstra(int src, vector<vector<pair<int, int>>>& g, vector<int>& d) {
    int n = g.size();
    d.assign(n, INT_MAX);
    d[src] = 0;

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
    pq.push({0, src});

    while (!pq.empty()) {
        int u = pq.top().second;
        int dist = pq.top().first;
        pq.pop();

        if (dist > d[u]) continue;

        for (auto e : g[u]) {
            int v = e.first;
            int w = e.second;
            if (d[u] + w < d[v]) {
                d[v] = d[u] + w;
                pq.push({d[v], v});
            }
        }
    }
}

int main() {
    int n, m;
    cout << "Vertices and edges: ";
    cin >> n >> m;

    vector<vector<pair<int, int>>> g(n);
    cout << "Edges (u v w):\n";
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        g[u].push_back({v, w});
    }

    int src;
    cout << "Source: ";
    cin >> src;

    vector<int> d(n);
    dijkstra(src, g, d);

    cout << "Distances from " << src << ":\n";
    for (int i = 0; i < n; i++) {
        if (d[i] == INT_MAX) cout << i << ": INF\n";
        else cout << i << ": " << d[i] << "\n";
    }

    return 0;
}