#include <iostream>
#include <vector>
#include <climits>

using namespace std;

int main() {
    // Example grid dimensions: n rows, m columns
    int n = 5; // Number of rows
    int m = 4; // Number of columns

    // Cost grid (c) - hardcoded for simplicity
    vector<vector<int>> c = {
        {4, 7, 1, 6},   // Row 1 (top)
        {5, 2, 4, 3},   // Row 2
        {3, 9, 2, 8},   // Row 3
        {6, 1, 5, 4},   // Row 4
        {8, 3, 7, 2}    // Row 5 (bottom)
    };

    // DP table (a) - initialized with large values
    vector<vector<int>> a(n + 1, vector<int>(m + 2, INT_MAX)); // 1-based indexing with padding

    // Initialize bottom row (row n) with costs from c
    for (int j = 1; j <= m; j++) {
        a[n][j] = c[n - 1][j - 1]; // Map 1-based a to 0-based c
    }

    // Fill padding columns with infinity to handle boundary cases
    for (int i = 0; i <= n; i++) {
        a[i][0] = INT_MAX;       // Left padding
        a[i][m + 1] = INT_MAX;   // Right padding
    }

    // DP computation from bottom to top
    for (int i = n - 1; i >= 1; i--) {
        for (int j = 1; j <= m; j++) {
            int middleMin = min(a[i + 1][j - 1], a[i + 1][j]); // Compare up-left and up
            a[i][j] = c[i - 1][j - 1] + min(middleMin, a[i + 1][j + 1]); // Add cost and min of 3 directions
        }
    }

    // Find minimum cost in the top row (row 1)
    int minimumCost = INT_MAX;
    for (int j = 1; j <= m; j++) {
        minimumCost = min(minimumCost, a[1][j]);
    }

    // Output the result
    cout << "The minimum cost is: " << minimumCost << endl;

    return 0;
}