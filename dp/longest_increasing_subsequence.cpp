#include <iostream>
#include <vector>
using namespace std;

// Function to find LIS using Naive DP
void LIS_Naive_DP(const vector<int>& X) {
    int n = X.size() - 1; // Size of the input (excluding the dummy 0 at the 0th index)
    vector<int> L(n + 1, 0);   // To store the length of LIS ending at each index (1-based)
    vector<int> prev(n + 1, -1); // To store the previous index in the LIS (1-based)

    int maxLength = 0;      // Largest value in L array
    int maxIndex = 0;       // Index of the largest value in L array

    for (int i = 1; i <= n; ++i) {
        L[i] = 1; // Each element is an LIS of length 1 by itself
        for (int j = 1; j < i; ++j) {
            if (X[j] < X[i] && L[j] + 1 > L[i]) {
                L[i] = L[j] + 1;
                prev[i] = j;
            }
        }
        if (L[i] > maxLength) {
            maxLength = L[i];
            maxIndex = i;
        }
    }

    // Print the LIS length
    cout << "Length of LIS: " << maxLength << endl;

    // Reconstruct the LIS
    vector<int> lis;
    for (int i = maxIndex; i != -1; i = prev[i]) {
        lis.push_back(X[i]);
    }

    // Print the LIS in correct order
    cout << "LIS: ";
    for (int i = lis.size() - 1; i >= 0; --i) {
        cout << lis[i] << " ";
    }
    cout << endl;
}

int main() {
    // Input array (1-based indexing with dummy 0 at index 0)
    vector<int> X = {0, 10, 22, 9, 33, 21, 50, 41, 60, 80};

    LIS_Naive_DP(X);

    return 0;
}
