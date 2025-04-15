#include <iostream>
#include <vector>

using namespace std;

// Function to solve the 0-1 Knapsack problem
void knapsack(int W, const vector<int>& weights, const vector<int>& values, int n) {
    // Create a 2D vector for storing results of subproblems
    vector<vector<int>> dp(n + 1, vector<int>(W + 1, 0));

    // Build the DP table
    for (int i = 1; i <= n; ++i) {
        for (int w = 1; w <= W; ++w) {
            if (weights[i - 1] <= w) {
                dp[i][w] = max(dp[i - 1][w], dp[i - 1][w - weights[i - 1]] + values[i - 1]);
            } else {
                dp[i][w] = dp[i - 1][w];
            }
        }
    }

    // Maximum profit
    int maxProfit = dp[n][W];
    cout << "Maximum Profit: " << maxProfit << endl;

    // Trace back to find selected items
    cout << "Items taken (1-indexed): ";
    int w = W;
    vector<int> selectedItems;
    for (int i = n; i > 0 && maxProfit > 0; --i) {
        if (maxProfit != dp[i - 1][w]) {
            selectedItems.push_back(i); // Item i is included
            maxProfit -= values[i - 1];
            w -= weights[i - 1];
        }
    }

    // Print selected items
    for (int i = selectedItems.size() - 1; i >= 0; --i) {
        cout << selectedItems[i] << " ";
    }
    cout << endl;
}

int main() {
    int n; // Number of items
    int W; // Maximum weight of the knapsack

    cout << "Enter the number of items: ";
    cin >> n;

    vector<int> weights(n), values(n);
    cout << "Enter the weights of the items: ";
    for (int i = 0; i < n; ++i) {
        cin >> weights[i];
    }

    cout << "Enter the values of the items: ";
    for (int i = 0; i < n; ++i) {
        cin >> values[i];
    }

    cout << "Enter the maximum weight capacity of the knapsack: ";
    cin >> W;

    knapsack(W, weights, values, n);

    return 0;
}
