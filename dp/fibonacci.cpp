#include <iostream>
#include <vector>
using namespace std;

// Initialize the memoization array with -1 (indicating uncomputed values)
vector<long long> F;

// Recursive function with memoization
long long Fib_rec(int n) {
    if (F[n] >= 0) {
        return F[n]; // Return the precomputed value if available
    }
    if (n <= 1) {
        F[n] = n; // Base cases: Fib(0) = 0, Fib(1) = 1
    } else {
        F[n] = Fib_rec(n - 1) + Fib_rec(n - 2); // Recursive computation
    }
    return F[n];
}

// Top-level function for memoized Fibonacci
long long Fib(int n) {
    F.assign(n + 1, -1); // Resize the array to fit n and initialize with -1
    return Fib_rec(n);   // Start the recursive calculation
}

int main() {
    int n;
    cout << "Enter the value of n: ";
    cin >> n;

    if (n < 0) {
        cout << "Fibonacci is not defined for negative numbers!" << endl;
        return 1;
    }

    long long result = Fib(n);
    cout << "Fib(" << n << ") = " << result << endl;

    return 0;
}
