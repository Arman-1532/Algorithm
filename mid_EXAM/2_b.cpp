#include <iostream>
#include<vector>
using namespace std;

int main() {
    int s = 11;
    vector<int> coins = {1, 3, 5};
    vector<int> dp(s + 1, INT_MAX);
    dp[0] = 0; 


    for (int i = 1; i <= s; ++i) {
        for (int coin : coins) {
            if (i >= coin && dp[i - coin] != INT_MAX) {
                dp[i] = min(dp[i], dp[i - coin] + 1);
            }
        }
    }

    if (dp[s] != INT_MAX) {
        cout << "Minimum number of coins required: " << dp[s] << endl;
    } else {
        cout << "Cannot make the target sum with the given coins." << endl;
    }

    return 0;
}