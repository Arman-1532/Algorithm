#include <iostream>
#include <string>
#include <cmath>
using namespace std;

// Parameters for Rabin-Karp algorithm
const int d = 256; // Number of characters in the input alphabet (ASCII)
const int q = 101; // A prime number for modulo to reduce hash collisions

// Function to implement Rabin-Karp algorithm for string matching
void rabinKarp(string text, string pattern) {
    int n = text.length();    // Length of text
    int m = pattern.length(); // Length of pattern
    int i, j;
    int p = 0; // Hash value for pattern
    int t = 0; // Hash value for current text window
    int h = 1; // Used to compute rolling hash

    // Calculate h = pow(d, m-1) % q
    for (i = 0; i < m - 1; i++) {
        h = (h * d) % q;
    }

    // Calculate initial hash values for pattern and first text window
    for (i = 0; i < m; i++) {
        p = (d * p + pattern[i]) % q;
        t = (d * t + text[i]) % q;
    }

    // Slide the pattern over the text one by one
    for (i = 0; i <= n - m; i++) {
        // Check if hash values match
        if (p == t) {
            // Verify character by character to avoid hash collisions
            for (j = 0; j < m; j++) {
                if (pattern[j] != text[i + j]) {
                    break;
                }
            }
            if (j == m) {
                cout << "Pattern found at index " << i << endl;
            }
        }

        // Calculate hash value for the next window of text
        // Remove leading digit, add trailing digit
        if (i < n - m) {
            t = (d * (t - text[i] * h) + text[i + m]) % q;

            // If t becomes negative, adjust it to be positive
            if (t < 0) {
                t = t + q;
            }
        }
    }
}

int main() {
    string text, pattern;

    // Input text and pattern
    cout << "Enter the text: ";
    getline(cin, text);
    cout << "Enter the pattern to search: ";
    getline(cin, pattern);

    // Check if pattern length is valid
    if (pattern.length() > text.length()) {
        cout << "Pattern length cannot be greater than text length!" << endl;
        return 1;
    }

    // Call Rabin-Karp algorithm
    cout << "Searching for pattern \"" << pattern << "\" in text \"" << text << "\":\n";
    rabinKarp(text, pattern);

    return 0;
}

// hash(s) = (s[0] * d^(m-1) + s[1] * d^(m-2) + ... + s[m-2] * d^1 + s[m-1] * d^0) % q