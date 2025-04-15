#include <iostream>
#include <vector>
#include <climits>
using namespace std;

int memoizedCutRodAux(const vector<int>& prices, int n, vector<int>& memo, vector<int>& cuts) {
    if (memo[n] >= 0)
        return memo[n];
    
    int q;
    if (n == 0)
        q = 0;
    else {
        q = INT_MIN;
        for (int i = 1; i <= n; ++i) {
            int current = prices[i] + memoizedCutRodAux(prices, n - i, memo, cuts);
            if (current > q) {
                q = current;
                cuts[n] = i; // Store the optimal cut size
            }
        }
    }
    memo[n] = q;
    return q;
}

void printCuts(const vector<int>& cuts, int n) {
    cout << "Optimal cuts: ";
    while (n > 0) {
        cout << cuts[n] << " ";
        n -= cuts[n];
    }
    cout << endl;
}

int memoizedCutRod(const vector<int>& prices, int n) {
    vector<int> memo(n + 1, INT_MIN);
    vector<int> cuts(n + 1, 0); // To store the cut sizes
    int maxProfit = memoizedCutRodAux(prices, n, memo, cuts);
    printCuts(cuts, n); // Print the cutting strategy
    return maxProfit;
}

int main() {
    int rodLength;
    cout << "Enter the length of the rod: ";
    cin >> rodLength;

    vector<int> prices(rodLength + 1);
    cout << "Enter the prices for rod lengths from 1 to " << rodLength << ":\n";
    for (int i = 1; i <= rodLength; ++i) {
        cout << "Price for length " << i << ": ";
        cin >> prices[i];
    }

    cout << "Maximum profit (Memoized): " << memoizedCutRod(prices, rodLength) << endl;

    return 0;
}