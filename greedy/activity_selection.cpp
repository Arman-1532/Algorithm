#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Function to implement the Greedy Activity Selector
vector<int> GREEDY_ACTIVITY_SELECTOR(const vector<int>& start, const vector<int>& finish) {
    int n = start.size();
    vector<int> selected; // To store selected activities
    
    // First activity is always selected
    selected.push_back(0);
    int k = 0; // Index of the last selected activity
    
    for (int m = 1; m < n; ++m) {
        // Check if the current activity is compatible with the last selected one
        if (start[m] >= finish[k]) {
            selected.push_back(m);
            k = m;
        }
    }
    return selected;
}

int main() {
    int n;
    
    // Taking input for the number of activities
    cout << "Enter the number of activities: ";
    cin >> n;

    vector<int> start(n), finish(n);

    // Taking input for start and finish times
    cout << "Enter the start times of the activities: ";
    for (int i = 0; i < n; ++i) {
        cin >> start[i];
    }

    cout << "Enter the finish times of the activities: ";
    for (int i = 0; i < n; ++i) {
        cin >> finish[i];
    }

    // Sorting activities by their finish times
    vector<pair<int, int>> activities;
    for (int i = 0; i < n; ++i) {
        activities.push_back({finish[i], start[i]});
    }
    sort(activities.begin(), activities.end());

    // Extracting sorted start and finish times
    for (int i = 0; i < n; ++i) {
        finish[i] = activities[i].first;
        start[i] = activities[i].second;
    }

    // Calling the GREEDY_ACTIVITY_SELECTOR
    vector<int> result = GREEDY_ACTIVITY_SELECTOR(start, finish);

    // Output the number and sequence of selected activities
    cout << "Number of selected activities: " << result.size() << endl;
    cout << "Sequence of selected activities (indices): ";
    for (int i : result) {
        cout << i + 1 << " "; // Adding 1 to convert 0-based index to 1-based
    }
    cout << endl;

    return 0;
}
