#include <iostream>
#include <vector>
#include <string>
using namespace std;

// Function to build the alphabet Σ (unique characters from T and P)
vector<char> buildAlphabet(string T, string P) {
    vector<char> alphabet;
    vector<bool> present(256, false); // Assuming ASCII characters (0-255)

    // Collect unique characters from T
    for (char c : T) {
        if (!present[c]) {
            present[c] = true;
            alphabet.push_back(c);
        }
    }

    // Collect unique characters from P
    for (char c : P) {
        if (!present[c]) {
            present[c] = true;
            alphabet.push_back(c);
        }
    }

    return alphabet;
}

// Function to compute the transition function δ(q, a)
vector<vector<int>> ComputeTransitionFunction(string P, vector<char>& sigma) {
    int m = P.length();
    int alphabetSize = sigma.size();

    // Create the transition table δ: rows = states (0 to m), columns = characters in Σ
    vector<vector<int>> delta(m + 1, vector<int>(alphabetSize, 0));

    // For each state q and character a
    for (int q = 0; q <= m; q++) {
        for (int a = 0; a < alphabetSize; a++) {
            char ch = sigma[a];
            // Compute P_q (first q characters of P)
            string Pq = (q == 0) ? "" : P.substr(0, q);
            Pq += ch; // Append character a to P_q

            // Find the largest k such that P_k is a suffix of P_q
            int k = min(m + 1, q + 2); // k can be at most q+1, but capped at m+1
            do {
                k--;
                string Pk = (k == 0) ? "" : P.substr(0, k);
                // Check if P_k is a suffix of P_q
                if (Pq.length() >= Pk.length()) {
                    string suffix = Pq.substr(Pq.length() - Pk.length());
                    if (suffix == Pk) {
                        break;
                    }
                }
            } while (k > 0);

            delta[q][a] = k; // δ(q, a) = k
        }
    }

    return delta;
}

// Function to implement Finite Automaton Matcher
void FiniteAutomatonMatcher(string T, string P, vector<char>& sigma) {
    int n = T.length();
    int m = P.length();

    // Compute the transition function
    vector<vector<int>> delta = ComputeTransitionFunction(P, sigma);

    // Finite Automaton Matcher
    int q = 0; // Initial state
    for (int i = 0; i < n; i++) {
        // Find the index of T[i] in the alphabet
        int a = -1;
        for (int j = 0; j < sigma.size(); j++) {
            if (T[i] == sigma[j]) {
                a = j;
                break;
            }
        }
        if (a == -1) {
            cout << "Character " << T[i] << " not in alphabet!\n";
            return;
        }

        // Transition to the next state
        q = delta[q][a];

        // If we reach state m, a match is found
        if (q == m) {
            int s = i - m + 1;
            cout << "Pattern occurs with shift " << s << endl;
        }
    }
}

int main() {
    string T, P;

    // Input text and pattern
    cout << "Enter the text: ";
    getline(cin, T);
    cout << "Enter the pattern: ";
    getline(cin, P);

    // Validate input
    if (P.empty() || P.length() > T.length()) {
        cout << "Invalid pattern!" << endl;
        return 1;
    }

    // Build the alphabet Σ (all unique characters in T and P)
    vector<char> sigma = buildAlphabet(T, P);

    // Run Finite Automaton Matcher
    cout << "Searching for \"" << P << "\" in \"" << T << "\":\n";
    FiniteAutomatonMatcher(T, P, sigma);

    return 0;
}



// #include <iostream>
// #include <vector>
// using namespace std;

// #define NO_OF_CHARS 256  // Number of characters in the input alphabet

// // Function to build the transition table (Finite Automaton)
// void computeTransitionFunction(string pattern, int m, vector<vector<int>> &TF) {
//     for (int q = 0; q <= m; q++) {
//         for (int a = 0; a < NO_OF_CHARS; a++) {
//             int k = min(m, q + 1);
//             string Pq_a = pattern.substr(0, q) + (char)a;

//             while (k > 0 && pattern.substr(0, k) != Pq_a.substr(q + 1 - k))
//                 k--;

//             TF[q][a] = k;
//         }
//     }
// }

// // Finite Automaton String Matching Algorithm
// void finiteAutomatonMatcher(string text, string pattern) {
//     int m = pattern.length();
//     int n = text.length();
    
//     vector<vector<int>> TF(m + 1, vector<int>(NO_OF_CHARS, 0));
//     computeTransitionFunction(pattern, m, TF);

//     int q = 0;  // Initial state

//     // Process the text
//     for (int i = 0; i < n; i++) {
//         q = TF[q][text[i]];  // Transition based on current character

//         if (q == m) {  // If we reach the final state, pattern found
//             cout << "Pattern found at index " << (i - m + 1) << endl;
//         }
//     }
// }

// int main() {
//     string text = "abbaabbaabba";
//     string pattern = "abba";

//     finiteAutomatonMatcher(text, pattern);

//     return 0;
// }