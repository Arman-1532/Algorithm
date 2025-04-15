#include <iostream>
#include <vector>
#include <queue>
#include <climits> // For INT_MAX
using namespace std;

// Struct to represent a graph edge
struct Edge {
    int to, weight;
};

// Function to implement Prim's Algorithmc
void primMST(int n, vector<vector<Edge>>& adj, int start = 0) {
    // Initialize vectors to store keys, parent nodes, and MST status
    vector<int> key(n, INT_MAX);    // Key values for vertices
    vector<int> parent(n, -1);     // Parent nodes in the MST
    vector<bool> inMST(n, false);  // To check if a vertex is in the MST

    // Priority queue to get the vertex with the smallest key
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
    key[start] = 0; // Start vertex's key is 0
    pq.push({0, start});

    while (!pq.empty()) {
        // Extract the vertex with the smallest key
        int u = pq.top().second;
        pq.pop();

        // If this vertex is already in MST, skip
        if (inMST[u]) continue;
        inMST[u] = true;

        // Traverse all adjacent vertices
        for (const Edge& edge : adj[u]) {
            int v = edge.to;
            int weight = edge.weight;

            // Update key and parent if a smaller weight edge is found
            if (!inMST[v] && weight < key[v]) {
                key[v] = weight;
                parent[v] = u;
                pq.push({key[v], v});
            }
        }
    }

    // Print the edges of the MST
    cout << "Edges in the Minimum Spanning Tree:\n";
    for (int i = 1; i < n; i++) { // Skip the start vertex (root)
        if (parent[i] != -1) {
            cout << parent[i] << " - " << i << " (weight: " << key[i] << ")\n";
        }
    }
}

int main() {
    int n, m;
    cout << "Enter the number of vertices and edges: ";
    cin >> n >> m;

    // Adjacency list representation of the graph
    vector<vector<Edge>> adj(n);

    cout << "Enter the edges (u, v, weight):\n";
    for (int i = 0; i < m; i++) {
        int u, v, weight;
        cin >> u >> v >> weight;
        adj[u].push_back({v, weight});
        adj[v].push_back({u, weight}); // For undirected graph
    }

    primMST(n, adj);

    return 0;
}
