#include <iostream>
#include <vector>
#include <climits>

using namespace std;

// Function to print the optimal parenthesization
void printParenthesis(int i, int j, const vector<vector<int>>& split, const string& name) {
    if (i == j) {
        cout << name[i - 1];
        return;
    }
    cout << "(";
    printParenthesis(i, split[i][j], split, name);
    printParenthesis(split[i][j] + 1, j, split, name);
    cout << ")";
}

// Function to find the minimum number of scalar multiplications and track splits
int matrixChainMultiplication(vector<int>& dimensions, vector<vector<int>>& split) {
    int n = dimensions.size();
    vector<vector<int>> dp(n, vector<int>(n, 0));
    split = vector<vector<int>>(n, vector<int>(n, 0));

    for (int len = 2; len < n; ++len) {
        for (int i = 1; i < n - len + 1; ++i) {
            int j = i + len - 1;
            dp[i][j] = INT_MAX;
            for (int k = i; k < j; ++k) {
                int cost = dp[i][k] + dp[k + 1][j] + dimensions[i - 1] * dimensions[k] * dimensions[j];
                if (cost < dp[i][j]) {
                    dp[i][j] = cost;
                    split[i][j] = k;
                }
            }
        }
    }
    return dp[1][n - 1];
}

int main() {
    // 5 matrices: 10x20, 20x30, 30x40, 40x50, 50x60
    vector<int> dimensions = {10, 20, 30, 40, 50, 60};
    string matrixNames = "ABCDE"; // A1=A, A2=B, A3=C, A4=D, A5=E

    vector<vector<int>> split;
    int result = matrixChainMultiplication(dimensions, split);
    cout << "Minimum number of multiplications is: " << result << endl;

    cout << "Optimal parenthesization: ";
    printParenthesis(1, dimensions.size() - 1, split, matrixNames);
    cout << endl;

    return 0;
}