#include <iostream>
#include <vector>
#include <limits>

using namespace std;

#define INF numeric_limits<int>::max() // Define Infinity

void floydWarshall(vector<vector<int>>& graph, int V) {
    vector<vector<int>> dist = graph; // Copy input graph to distance matrix

    // Run Floyd-Warshall Algorithm
    for (int k = 0; k < V; k++) {  // Intermediate vertex
        for (int i = 0; i < V; i++) {  // Source vertex
            for (int j = 0; j < V; j++) {  // Destination vertex
                // Ensure no overflow before updating distance
                if (dist[i][k] != INF && dist[k][j] != INF && 
                    dist[i][k] + dist[k][j] < dist[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }

    // Print the shortest distance matrix
    cout << "\nShortest distance matrix:\n";
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            if (dist[i][j] == INF) 
                cout << "INF\t";
            else 
                cout << dist[i][j] << "\t";
        }
        cout << endl;
    }
}

int main() {
    int V;
    cout << "Enter number of vertices: ";
    cin >> V;

    vector<vector<int>> graph(V, vector<int>(V));

    cout << "Enter adjacency matrix (use INF for no edge):\n";
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            string val;
            cin >> val;
            graph[i][j] = (val == "INF") ? INF : stoi(val);
        }
    }

    floydWarshall(graph, V);

    return 0;
}



//path o print kore nicher ta

// #include <iostream>
// #include <vector>
// #include <limits>

// using namespace std;

// #define INF numeric_limits<int>::max() // Define Infinity

// void printPath(vector<vector<int>>& P, int s, int t) {
//     if (P[s][t] == -1) {
//         cout << "No path";
//         return;
//     }
//     if (P[s][t] == s) {
//         cout << s << " -> ";
//     } else {
//         printPath(P, s, P[s][t]);
//         printPath(P, P[s][t], t);
//     }
// }

// void floydWarshall(vector<vector<int>>& graph, int V) {
//     vector<vector<int>> dist = graph;
//     vector<vector<int>> P(V, vector<int>(V, -1)); // Path reconstruction table

//     // Initialize Path Table
//     for (int i = 0; i < V; i++) {
//         for (int j = 0; j < V; j++) {
//             if (graph[i][j] != INF && i != j) {
//                 P[i][j] = i;
//             }
//         }
//     }

//     // Floyd-Warshall Algorithm
//     for (int k = 0; k < V; k++) {
//         for (int i = 0; i < V; i++) {
//             for (int j = 0; j < V; j++) {
//                 if (dist[i][k] != INF && dist[k][j] != INF && 
//                     dist[i][k] + dist[k][j] < dist[i][j]) {
//                     dist[i][j] = dist[i][k] + dist[k][j];
//                     P[i][j] = P[k][j]; // Update path table
//                 }
//             }
//         }
//     }

//     // Print Shortest Distance Matrix
//     cout << "\nShortest Distance Matrix:\n";
//     for (int i = 0; i < V; i++) {
//         for (int j = 0; j < V; j++) {
//             if (dist[i][j] == INF) cout << "INF\t";
//             else cout << dist[i][j] << "\t";
//         }
//         cout << endl;
//     }

//     // Print Shortest Paths
//     cout << "\nShortest Paths:\n";
//     for (int i = 0; i < V; i++) {
//         for (int j = 0; j < V; j++) {
//             if (i != j) {
//                 cout << "Path " << i << " to " << j << ": ";
//                 printPath(P, i, j);
//                 cout << j << endl;
//             }
//         }
//     }
// }

// int main() {
//     int V;
//     cout << "Enter number of vertices: ";
//     cin >> V;

//     vector<vector<int>> graph(V, vector<int>(V));

//     cout << "Enter adjacency matrix (use INF for no edge):\n";
//     for (int i = 0; i < V; i++) {
//         for (int j = 0; j < V; j++) {
//             string val;
//             cin >> val;
//             graph[i][j] = (val == "INF") ? INF : stoi(val);
//         }
//     }

//     floydWarshall(graph, V);

//     return 0;
// }
