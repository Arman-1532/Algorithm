#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

int editDistance(const string& x, const string& y) {
    int m = x.size();
    int n = y.size();

    vector<vector<int> > dp(m + 1, vector<int>(n + 1, 0));

    for (int i = 0; i <= m; ++i) {
        for (int j = 0; j <= n; ++j) {
            if (i == 0) {
                dp[i][j] = j;
            } else if (j == 0) {
                dp[i][j] = i;
            } else if (x[i - 1] == y[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1];
            } else {
                dp[i][j] = 1 + min(dp[i - 1][j - 1], min( dp[i - 1][j], dp[i][j - 1]));  // Substitute // delete  // Insert
            }
        }
    }

    return dp[m][n];
}

int main() {
    string x = "kitten", y = "sitting";

    int result = editDistance(x, y);
    cout << "The Edit Distance between \"" << x << "\" and \"" << y << "\" is: " << result << endl;

    return 0;
}
   