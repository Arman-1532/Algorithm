#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Structure to represent an edge
struct Edge {
    int u, v, weight;
};

// Function to find the parent of a node (with path compression)
int findParent(int node, vector<int>& parent) {
    if (parent[node] == node)
        return node;
    return parent[node] = findParent(parent[node], parent);
}

// Function to union two sets
void unionSets(int u, int v, vector<int>& parent, vector<int>& rank) {
    int rootU = findParent(u, parent);
    int rootV = findParent(v, parent);

    if (rootU != rootV) {
        if (rank[rootU] > rank[rootV])
            parent[rootV] = rootU;
        else if (rank[rootU] < rank[rootV])
            parent[rootU] = rootV;
        else {
            parent[rootV] = rootU;
            rank[rootU]++;
        }
    }
}
bool comperator(const Edge & edge1, const Edge &edge2){
    return edge1.weight < edge2.weight;
}
// Kruskal's Algorithm
void kruskal(int n, vector<Edge>& edges) {
    // Sort edges by weight
    sort(edges.begin(), edges.end(), comperator);

    vector<int> parent(n), rank(n, 0);
    for (int i = 0; i < n; i++)
        parent[i] = i;

    vector<Edge> mst;
    for (Edge& edge : edges) {
        if (findParent(edge.u, parent) != findParent(edge.v, parent)) {
            mst.push_back(edge);
            unionSets(edge.u, edge.v, parent, rank);
        }
    }

    // Print the MST
    cout << "Edges in the Minimum Spanning Tree:\n";
    for (Edge& edge : mst) {
        cout << edge.u << " - " << edge.v << " (weight: " << edge.weight << ")\n";
    }
}

int main() {
    int n, m; // n = number of vertices, m = number of edges
    cout << "Enter the number of vertices and edges: ";
    cin >> n >> m;

    vector<Edge> edges(m);
    cout << "Enter the edges (u, v, weight):\n";
    for (int i = 0; i < m; i++) {
        cin >> edges[i].u >> edges[i].v >> edges[i].weight;
    }

    kruskal(n, edges);

    return 0;
}
