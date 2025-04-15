#include <iostream>
#include <vector>
using namespace std;

void MaxSumInterval(const vector<int>& A) {
    int n = A.size();
    int maxSum = A[0], currSum = A[0];
    int start = 0, end = 0, tempStart = 0;

    for (int i = 1; i < n; ++i) {
        // If current sum becomes negative, start a new subarray
        if (currSum < 0) {
            currSum = A[i];
            tempStart = i;
        } else {
            currSum += A[i];
        }

        // Update maxSum if currSum is greater
        if (currSum > maxSum) {
            maxSum = currSum;
            start = tempStart;
            end = i;
        }
    }

    // Handle case where maxSum is a single element
    if (maxSum < A[0]) {
        maxSum = A[0];
        start = 0;
        end = 0;
    }

    // Print the result
    cout << "Maximum sum: " << maxSum << endl;
    cout << "Subarray (1-based indices): ";
    for (int i = start; i <= end; ++i) {
        cout << A[i] << " ";
    }
    cout << endl;
}

int main() {
    vector<int> A = {9, -3, 1, 7, -15, 2, 3, -4, 2, -7, 6, -2, 8, 4, 9};
    MaxSumInterval(A);
    return 0;
}