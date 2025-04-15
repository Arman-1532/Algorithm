#include <iostream>
#include <vector>
#include <string>
using namespace std;

// Function to compute the pi table (LPS array)
vector<int> computePiTable(string pattern) {
    int m = pattern.length();
    vector<int> pi(m, 0); // Initialize pi table with zeros
    int k = 0; // Length of the matching prefix

    // Start from the second character
    for (int i = 1; i < m; i++) {
        while (k > 0 && pattern[k] != pattern[i]) {
            k = pi[k - 1]; // Fall back to the previous prefix
        }
        if (pattern[k] == pattern[i]) {
            k++; // Extend the prefix
        }
        pi[i] = k; // Set the pi value
    }
    return pi;
}

// KMP algorithm as provided
void KMPSearch(string text, string pattern) {
    int n = text.length();
    int m = pattern.length();

    // Create LPS array (using computePiTable)
    vector<int> lps(m, 0);
    lps = computePiTable(pattern); // Assign the computed pi table to lps

    int i = 0; // Index for text
    int j = 0; // Index for pattern

    // Search for pattern in text
    while (i < n) {
        if (pattern[j] == text[i]) {
            i++;
            j++;
        }

        if (j == m) {
            // Pattern found, print the starting index
            cout << "Pattern found at index " << i - j << endl;
            // Move j to the previous LPS value to look for next occurrence
            j = lps[j - 1];
        } else if (i < n && pattern[j] != text[i]) {
            // Mismatch: Skip ahead using LPS
            if (j != 0) {
                j = lps[j - 1];
            } else {
                i++;
            }
        }
    }
}

int main() {
    string text, pattern;

    // Input text and pattern
    cout << "Enter the text: ";
    getline(cin, text);
    cout << "Enter the pattern: ";
    getline(cin, pattern);

    // Simple validation
    if (pattern.empty() || pattern.length() > text.length()) {
        cout << "Invalid pattern!" << endl;
        return 1;
    }

    // Run KMP algorithm
    cout << "Searching for \"" << pattern << "\" in \"" << text << "\":\n";
    KMPSearch(text, pattern);

    return 0;
}