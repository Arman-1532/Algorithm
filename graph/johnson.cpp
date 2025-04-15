#include <iostream>
#include <vector>
#include <climits>
using namespace std;

#define INF INT_MAX

// Function to run Bellman-Ford algorithm from a new vertex s
vector<long long> bellmanFord(int V, vector<vector<int>>& graph, int s) {
    vector<long long> h(V + 1, INF); // Distances from s (V+1 to include s)
    h[s] = 0;

    // Relax edges V times
    for (int i = 0; i < V; i++) {
        for (int u = 0; u <= V; u++) {
            for (int v = 0; v <= V; v++) {
                if (graph[u][v] != INF && h[u] != INF && h[v] > h[u] + graph[u][v]) {
                    h[v] = h[u] + graph[u][v];
                }
            }
        }
    }

    // Check for negative cycles
    for (int u = 0; u <= V; u++) {
        for (int v = 0; v <= V; v++) {
            if (graph[u][v] != INF && h[u] != INF && h[v] > h[u] + graph[u][v]) {
                cout << "Graph contains a negative cycle!" << endl;
                return vector<long long>(); // Empty vector to indicate failure
            }
        }
    }

    return h;
}

// Simplified Dijkstra's algorithm (without priority queue)
vector<long long> dijkstra(int V, vector<vector<int>>& graph, int src) {
    vector<long long> dist(V, INF);
    vector<bool> visited(V, false);
    dist[src] = 0;

    // Run V iterations to find shortest paths
    for (int i = 0; i < V; i++) {
        // Find the unvisited vertex with minimum distance
        int u = -1;
        long long minDist = INF;
        for (int v = 0; v < V; v++) {
            if (!visited[v] && dist[v] < minDist) {
                minDist = dist[v];
                u = v;
            }
        }

        if (u == -1) break; // No more reachable vertices
        visited[u] = true;

        // Update distances to neighbors
        for (int v = 0; v < V; v++) {
            if (!visited[v] && graph[u][v] != INF && dist[v] > dist[u] + graph[u][v]) {
                dist[v] = dist[u] + graph[u][v];
            }
        }
    }

    return dist;
}

// Simplified Johnson's Algorithm
vector<vector<long long>> johnson(int V, vector<vector<int>>& graph) {
    // Step 1: Add a new vertex s (index V) with edges of weight 0 to all vertices
    vector<vector<int>> newGraph(V + 1, vector<int>(V + 1, INF));
    for (int u = 0; u < V; u++) {
        for (int v = 0; v < V; v++) {
            newGraph[u][v] = graph[u][v];
        }
    }
    for (int v = 0; v < V; v++) {
        newGraph[V][v] = 0; // Edge from s to v with weight 0
    }

    // Step 2: Run Bellman-Ford from s
    vector<long long> h = bellmanFord(V, newGraph, V);
    if (h.empty()) {
        return vector<vector<long long>>(); // Negative cycle detected
    }

    // Step 3: Reweight the graph
    vector<vector<int>> reweightedGraph(V, vector<int>(V, INF));
    for (int u = 0; u < V; u++) {
        for (int v = 0; v < V; v++) {
            if (graph[u][v] != INF) {
                reweightedGraph[u][v] = graph[u][v] + h[u] - h[v];
            }
        }
    }

    // Step 4: Run Dijkstra's algorithm for each vertex
    vector<vector<long long>> dist(V, vector<long long>(V, INF));
    for (int u = 0; u < V; u++) {
        vector<long long> d = dijkstra(V, reweightedGraph, u);
        for (int v = 0; v < V; v++) {
            if (d[v] == INF) {
                dist[u][v] = INF;
            } else {
                // Step 5: Adjust distances back to original weights
                dist[u][v] = d[v] - h[u] + h[v];
            }
        }
    }

    return dist;
}

int main() {
    int V;
    cout << "Enter the number of vertices: ";
    cin >> V;

    // Input the graph as an adjacency matrix
    vector<vector<int>> graph(V, vector<int>(V, INF));
    cout << "Enter the adjacency matrix (" << V << "x" << V << "):\n";
    cout << "Enter INF for no edge (e.g., 99999):\n";
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            int w;
            cin >> w;
            if (w == 99999) { // Use 99999 as INF for input
                graph[i][j] = INF;
            } else {
                graph[i][j] = w;
            }
        }
    }

    // Run Johnson's Algorithm
    vector<vector<long long>> dist = johnson(V, graph);

    // Print the result
    if (!dist.empty()) {
        cout << "\nShortest path distances between all pairs of vertices:\n";
        for (int u = 0; u < V; u++) {
            for (int v = 0; v < V; v++) {
                if (dist[u][v] == INF) {
                    cout << "INF\t";
                } else {
                    cout << dist[u][v] << "\t";
                }
            }
            cout << endl;
        }
    }

    return 0;
}