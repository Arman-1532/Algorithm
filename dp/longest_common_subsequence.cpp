#include <iostream>
#include <vector>
#include <string>
#include <algorithm> 
using namespace std;

// Function to find the LCS using dynamic programming
string findLCS(const string& X, const string& Y) {
    int m = X.size(), n = Y.size();
    vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));

    // Fill the dp table
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (X[i - 1] == Y[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
            } else {
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            }
        }
    }

    // Reconstruct the LCS
    string lcs;
    int i = m, j = n;
    while (i > 0 && j > 0) {
        if (X[i - 1] == Y[j - 1]) {
            lcs.push_back(X[i - 1]);
            i--;
            j--;
        } else if (dp[i - 1][j] > dp[i][j - 1]) {
            i--;
        } else {
            j--;
        }
    }

    // Reverse the LCS because we built it backwards
    reverse(lcs.begin(), lcs.end());
    return lcs;
}

int main() {
    string X, Y;
    cout << "Enter first string: ";
    cin >> X;
    cout << "Enter second string: ";
    cin >> Y;

    // Find and print the LCS
    string lcs = findLCS(X, Y);
    cout << "\nThe Length of Longest Common Subsequence is: " << lcs.length() << endl;
    cout << "The Longest Common Subsequence is: " << lcs << endl;

    return 0;
}
