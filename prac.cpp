#include <iostream>
#include <vector>
using namespace std;

// Function to find minimum cost and print path
int minCostPath(vector<vector<int>>& grid, int m, int n) {
    // Create DP table
    vector<vector<int>> dp(m, vector<int>(n));
    
    // Initialize first cell
    dp[0][0] = grid[0][0];
    
    // Fill first row
    for(int j = 1; j < n; j++)
        dp[0][j] = dp[0][j-1] + grid[0][j];
    
    // Fill first column
    for(int i = 1; i < m; i++)
        dp[i][0] = dp[i-1][0] + grid[i][0];
    
    // Fill rest of the table
    for(int i = 1; i < m; i++) {
        for(int j = 1; j < n; j++) {
            dp[i][j] = min(dp[i-1][j], dp[i][j-1]) + grid[i][j];
        }
    }
    
    // Simple path reconstruction
    vector<pair<int,int>> path;
    int i = m-1, j = n-1;
    path.push_back({i,j});
    
    while(i > 0 || j > 0) {
        if(i == 0) {
            j--;
        }
        else if(j == 0) {
            i--;
        }
        else if(dp[i-1][j] < dp[i][j-1]) {
            i--;
        }
        else {
            j--;
        }
        path.push_back({i,j});
    }
    
    // Print path in correct order
    cout << "Path: ";
    for(int k = path.size()-1; k >= 0; k--) {
        cout << "(" << path[k].first << "," << path[k].second << ") ";
    }
    cout << endl;
    
    return dp[m-1][n-1];
}

int main() {
    int m, n;
    cout << "Enter rows (m): ";
    cin >> m;
    cout << "Enter columns (n): ";
    cin >> n;
    
    vector<vector<int>> grid(m, vector<int>(n));
    cout << "Enter grid elements:" << endl;
    for(int i = 0; i < m; i++) {
        for(int j = 0; j < n; j++) {
            cin >> grid[i][j];
        }
    }
    
    int result = minCostPath(grid, m, n);
    cout << "Minimum cost: " << result << endl;
    
    return 0;
}