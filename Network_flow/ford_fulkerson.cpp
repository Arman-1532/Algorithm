#include <iostream>
#include <vector>
#include <queue>
#include <climits>
using namespace std;

// Function to perform BFS and find an augmenting path
bool bfs(vector<vector<int>>& residualGraph, int source, int sink, int V, vector<int>& parent) {
    vector<bool> visited(V, false);
    queue<int> q;
    
    q.push(source);
    visited[source] = true;
    parent[source] = -1;

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (int v = 0; v < V; v++) {
            if (!visited[v] && residualGraph[u][v] > 0) {
                q.push(v);
                visited[v] = true;
                parent[v] = u;
                if (v == sink) {
                    return true; // Found an augmenting path to sink
                }
            }
        }
    }
    return false; // No augmenting path found
}

// Ford-Fulkerson algorithm using BFS (Edmonds-Karp variant)
int fordFulkerson(vector<vector<int>>& graph, int source, int sink, int V) {
    vector<vector<int>> residualGraph = graph; // Copy graph to residual graph
    vector<int> parent(V); // To store the augmenting path
    int maxFlow = 0;

    // Find augmenting paths and update residual graph
    while (bfs(residualGraph, source, sink, V, parent)) {
        int pathFlow = INT_MAX;

        // Find the minimum residual capacity along the path
        for (int v = sink; v != source; v = parent[v]) {
            int u = parent[v];
            pathFlow = min(pathFlow, residualGraph[u][v]);
        }

        // Update residual capacities
        for (int v = sink; v != source; v = parent[v]) {
            int u = parent[v];
            residualGraph[u][v] -= pathFlow; // Reduce forward edge capacity
            residualGraph[v][u] += pathFlow; // Increase reverse edge capacity
        }

        maxFlow += pathFlow;
    }

    return maxFlow;
}

int main() {
    int V; // Number of vertices
    cout << "Enter the number of vertices: ";
    cin >> V;

    // Input the capacity graph as an adjacency matrix
    vector<vector<int>> graph(V, vector<int>(V, 0));
    cout << "Enter the capacity matrix (" << V << "x" << V << "):\n";
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            cin >> graph[i][j];
        }
    }

    int source, sink;
    cout << "Enter the source vertex (0 to " << V-1 << "): ";
    cin >> source;
    cout << "Enter the sink vertex (0 to " << V-1 << "): ";
    cin >> sink;

    // Compute and print the maximum flow
    int maxFlow = fordFulkerson(graph, source, sink, V);
    cout << "The maximum flow from " << source << " to " << sink << " is: " << maxFlow << endl;

    return 0;
}