#include <iostream>
#include <vector>
#include <cmath>
#include <limits>
using namespace std;

pair<int, int> getCoordinates(char key) {
    if (key == '*') return {3, 0};
    if (key == '0') return {3, 1};
    if (key == '#') return {3, 2};
    int num = key - '1';
    return {num / 3, num % 3};
}

double calculateDistance(char from, char to) {
    auto [x1, y1] = getCoordinates(from);
    auto [x2, y2] = getCoordinates(to);
    double dx = abs(x1 - x2);
    double dy = abs(y1 - y2);
    if (dx + dy == 1) return 1.0;
    if (dx == 1 && dy == 1) return 1.5;
    return dx + dy;
}

double solve(string &number, int index, char finger1, char finger2, vector<vector<vector<double>>> &dp) {
    if (index == number.size()) return 0;

    int f1 = finger1 == '*' ? 10 : (finger1 == '#' ? 11 : (finger1 - '0'));
    int f2 = finger2 == '*' ? 10 : (finger2 == '#' ? 11 : (finger2 - '0'));
    if (dp[index][f1][f2] != -1.0) {
        return dp[index][f1][f2];
    }

    char nextKey = number[index];

    double option1 = calculateDistance(finger1, nextKey) + solve(number, index + 1, nextKey, finger2, dp);
    double option2 = calculateDistance(finger2, nextKey) + solve(number, index + 1, finger1, nextKey, dp);

    return dp[index][f1][f2] = min(option1, option2);
}

int main() {
    string number;
    cout << "Enter the number to dial: ";
    cin >> number;

    vector<vector<vector<double>>> dp(number.size(), vector<vector<double>>(12, vector<double>(12, -1.0)));

    char finger1 = '*';
    char finger2 = '#';

    double result = solve(number, 0, finger1, finger2, dp);
    cout << "Minimum effort required to dial the number: " << result << endl;

    return 0;
}
