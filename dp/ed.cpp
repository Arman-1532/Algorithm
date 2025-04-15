#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

// Function to compute Edit Distance and track operations
int editDistance(const string& x, const string& y, vector<vector<int>>& dp) {
    int m = x.size();
    int n = y.size();
    dp = vector<vector<int>>(m + 1, vector<int>(n + 1, 0));

    // Fill the DP table
    for (int i = 0; i <= m; ++i) {
        for (int j = 0; j <= n; ++j) {
            if (i == 0) {
                dp[i][j] = j; // Insert all characters of y
            } else if (j == 0) {
                dp[i][j] = i; // Delete all characters of x
            } else if (x[i - 1] == y[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1]; // No operation needed
            } else {
                dp[i][j] = 1 + min({dp[i - 1][j - 1], dp[i - 1][j], dp[i][j - 1]});
            }
        }
    }
    return dp[m][n];
}

// Function to reconstruct and print the sequence of operations
void printOperations(const string& x, const string& y, const vector<vector<int>>& dp) {
    int i = x.size(), j = y.size();
    cout << "Sequence of operations:\n";
    while (i > 0 || j > 0) {
        if (i > 0 && j > 0 && dp[i][j] == dp[i-1][j-1]) { //x[i - 1] == y[j - 1]
            // Characters match, no operation
            i--;
            j--;
        } else if (i > 0 && dp[i][j] == dp[i - 1][j] + 1) {
            cout << "Delete '" << x[i - 1] << "' from first string\n";
            i--;
        } else if (j > 0 && dp[i][j] == dp[i][j - 1] + 1) {
            cout << "Insert '" << y[j - 1] << "' into first string\n";
            j--;
        } else if (i > 0 && j > 0 && dp[i][j] == dp[i - 1][j - 1] + 1) {
            cout << "Substitute '" << x[i - 1] << "' with '" << y[j - 1] << "'\n";
            i--;
            j--;
        }
    }
}

int main() {
    string x, y;
    cout << "Enter the first string: ";
    cin >> x;
    cout << "Enter the second string: ";
    cin >> y;

    vector<vector<int>> dp;
    int result = editDistance(x, y, dp);
    cout << "The Edit Distance between \"" << x << "\" and \"" << y << "\" is: " << result << endl;
    
    // Print the sequence of operations
    printOperations(x, y, dp);

    return 0;
}