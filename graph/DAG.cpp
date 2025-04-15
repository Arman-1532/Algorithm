#include <iostream>
#include <vector>
using namespace std;

#define NO_OF_CHARS 256  // Number of characters in the input alphabet

// Function to build the transition table (Finite Automaton)
void computeTransitionFunction(string pattern, int m, vector<vector<int>> &TF) {
    for (int q = 0; q <= m; q++) {
        for (int a = 0; a < NO_OF_CHARS; a++) {
            int k = min(m, q + 1);
            string Pq_a = pattern.substr(0, q) + (char)a;

            while (k > 0 && pattern.substr(0, k) != Pq_a.substr(q + 1 - k))
                k--;

            TF[q][a] = k;
        }
    }
}

// Finite Automaton String Matching Algorithm
void finiteAutomatonMatcher(string text, string pattern) {
    int m = pattern.length();
    int n = text.length();
    
    vector<vector<int>> TF(m + 1, vector<int>(NO_OF_CHARS, 0));
    computeTransitionFunction(pattern, m, TF);

    int q = 0;  // Initial state

    // Process the text
    for (int i = 0; i < n; i++) {
        q = TF[q][text[i]];  // Transition based on current character

        if (q == m) {  // If we reach the final state, pattern found
            cout << "Pattern found at index " << (i - m + 1) << endl;
        }
    }
}

int main() {
    string text = "abbaabbaabba";
    string pattern = "abba";

    finiteAutomatonMatcher(text, pattern);

    return 0;
}