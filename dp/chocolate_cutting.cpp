#include <iostream>
#include <vector>
#include <climits> // For INT_MIN

using namespace std;

// Initialize memoization table
vector<vector<int>> C;

// Function for the recursive computation
int rec(int n, int r) {
    if (C[n][r] != INT_MIN) {
        return C[n][r]; // Return memoized result
    }
    if (r == 1) { // Base case 1
        C[n][r] = n;
    } else if (r == n || r == 0) { // Base case 2
        C[n][r] = 1;
    } else { // General case
        C[n][r] = rec(n - 1, r - 1) + rec(n - 1, r);
    }
    return C[n][r];
}

// Combination function
int Comb(int n, int r) {
    C = vector<vector<int>>(n + 1, vector<int>(r + 1, INT_MIN)); // Initialize all values to INT_MIN
    return rec(n, r);
}

int main() {
    int n, r;
    cout << "Enter values for n and r: ";
    cin >> n >> r;

    if (n < r || n < 0 || r < 0) {
        cout << "Invalid input! n must be >= r and both must be non-negative." << endl;
    } else {
        cout << "C(" << n << ", " << r << ") = " << Comb(n, r) << endl;
    }

    return 0;
}
