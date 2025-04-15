#include <iostream>
#include <cassert>
#include <vector>

using namespace std;

int climbStairs(int n) {
    // Base cases
    if (n <= 0) return 0;
    if (n == 1) return 1;
    if (n == 2) return 2;
    
    // Initialize dp vector
    vector<int> dp(n + 1, 0);
    
    // Set base cases
    dp[1] = 1;  // 1 way to reach step 1
    dp[2] = 2;  // 2 ways to reach step 2
    
    // Fill dp array
    for (int i = 3; i <= n; i++) {
        dp[i] = dp[i-1] + dp[i-2];
    }
    
    return dp[n];
}

int main() {
    int n;
    
    // Get input from user
    cout << "Enter the number of stairs (1-45): ";
    cin >> n;
    
    // Validate input
    if (n <= 0 || n > 45) {
        cout << "Error: Please enter a number between 1 and 45" << endl;
        return 1;  // Return non-zero to indicate error
    }
    
    // Calculate and display result
    int result = climbStairs(n);
    cout << "Number of ways to climb " << n << " stairs: " << result << endl;
    
    return 0;
}