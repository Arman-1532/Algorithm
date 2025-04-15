#include <iostream>
#include <vector>
#include <iomanip>
#include <limits>
#include <cmath>
#include <bits/stdc++.h>

using namespace std;

typedef vector<vector<double>> Matrix;

double fraction(double num) {
    return round(num * 100) / 100; // Limit precision
}

void printTable(const Matrix &table, const vector<int> &B, const vector<double> &cb) {
    cout << "B \tCB \tXB \ty1 \ty2 \ty3 \ty4" << endl;
    for (size_t i = 0; i < table.size(); i++) {
        cout << "x" << B[i] + 1 << "\t" << fraction(cb[i]) << "\t";
        for (double val : table[i]) {
            cout << fraction(val) << "\t";
        }
        cout << endl;
    }
    cout << endl;
}

int main() {
    cout << "\n                 ****SiMplex Algorithm ****\n\n";

    Matrix A = {{1, 1, 0, 1}, {2, 1, 1, 0}};
    vector<double> b = {8, 10};
    vector<double> c = {1, 1, 0, 0};

    vector<int> B = {3, 2}; // Basic variables
    vector<double> cb = {c[3], c[2]};
    Matrix table = {
        {b[0], A[0][0], A[0][1], A[0][2], A[0][3]},
        {b[1], A[1][0], A[1][1], A[1][2], A[1][3]}
    };

    bool optimal = false;
    int iter = 1;

    while (!optimal) {
        cout << "Iteration: " << iter++ << endl;
        printTable(table, B, cb);

        vector<double> relProfit(4, 0);
        for (int i = 0; i < 4; i++) {
            for (size_t j = 0; j < B.size(); j++) {
                relProfit[i] += cb[j] * table[j][i + 1];
            }
            relProfit[i] = c[i] - relProfit[i];
        }

        int enteringVar = max_element(relProfit.begin(), relProfit.end()) - relProfit.begin();
        if (*max_element(relProfit.begin(), relProfit.end()) <= 0) {
            cout << "Optimality reached!" << endl;
            break;
        }

        double minRatio = numeric_limits<double>::max();
        int leavingVar = -1;
        for (size_t i = 0; i < B.size(); i++) {
            if (table[i][enteringVar + 1] > 0) {
                double ratio = table[i][0] / table[i][enteringVar + 1];
                if (ratio < minRatio) {
                    minRatio = ratio;
                    leavingVar = i;
                }
            }
        }
        if (leavingVar == -1) {
            cout << "Unbounded Solution!" << endl;
            return 0;
        }

        B[leavingVar] = enteringVar;
        cb[leavingVar] = c[enteringVar];

        double pivot = table[leavingVar][enteringVar + 1];
        for (double &val : table[leavingVar]) val /= pivot;
        for (size_t i = 0; i < table.size(); i++) {
            if (i != leavingVar) {
                double factor = table[i][enteringVar + 1];
                for (size_t j = 0; j < table[i].size(); j++) {
                    table[i][j] -= factor * table[leavingVar][j];
                }
            }
        }
    }
    return 0;
}