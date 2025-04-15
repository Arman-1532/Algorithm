#include <iostream>
#include <vector>
#include <limits>

using namespace std;

struct Edge {
    int u, v, w;
};

void bellmanFord(int V, int E, vector<Edge>& edges, int source) {
    vector<int> distance(V, numeric_limits<int>::max());
    distance[source] = 0;

    // Step 1: Relax all edges |V| - 1 times
    for (int i = 0; i < V - 1; i++) {
        for (const auto& edge : edges) {
            if (distance[edge.u] != numeric_limits<int>::max() && 
                distance[edge.u] + edge.w < distance[edge.v]) {
                distance[edge.v] = distance[edge.u] + edge.w;
            }
        }
    }

    // Step 2: Check for negative weight cycles
    for (const auto& edge : edges) {
        if (distance[edge.u] != numeric_limits<int>::max() && 
            distance[edge.u] + edge.w < distance[edge.v]) {
            cout << "Negative weight cycle detected!" << endl;
            return;
        }
    }

    // Print shortest distances
    cout << "Vertex distances from source " << source << ":" << endl;
    for (int i = 0; i < V; i++) {
        cout << "Vertex " << i << " : " << (distance[i] == numeric_limits<int>::max() ? "INF" : to_string(distance[i])) << endl;
    }
}

int main() {
    int V, E, source;
    cout << "Enter number of vertices and edges: ";
    cin >> V >> E;

    vector<Edge> edges(E);
    cout << "Enter edges (u v w):" << endl;
    for (int i = 0; i < E; i++) {
        cin >> edges[i].u >> edges[i].v >> edges[i].w;
    }

    cout << "Enter source vertex: ";
    cin >> source;

    bellmanFord(V, E, edges, source);

    return 0;
}
