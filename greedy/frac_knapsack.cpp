#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Structure to represent an item with weight, benefit, and value (benefit/weight)
struct Item {
    double weight;
    double benefit;
    double value; // benefit-to-weight ratio
};

// Comparator function to sort items based on their value in descending order
bool compareByValue(const Item& a, const Item& b) {
    return a.value > b.value;
}

// Function to calculate the fractional knapsack
double fractionalKnapsack(vector<Item>& items, double maxWeight) {
    // Sort items by value (benefit-to-weight ratio) in descending order
    sort(items.begin(), items.end(), compareByValue);

    double totalValue = 0.0; // Total value of the knapsack
    double currentWeight = 0.0; // Current weight of the knapsack

    for (const auto& item : items) {
        if (currentWeight + item.weight <= maxWeight) {
            // Take the entire item
            currentWeight += item.weight;
            totalValue += item.benefit;
        } else {
            // Take the fraction of the item
            double remainingWeight = maxWeight - currentWeight;
            totalValue += item.value * remainingWeight;
            break; // Knapsack is full
        }
    }

    return totalValue;
}

int main() {
    int n;
    double maxWeight;

    // Taking input for the number of items
    cout << "Enter the number of items: ";
    cin >> n;

    // Taking input for the maximum weight of the knapsack
    cout << "Enter the maximum weight of the knapsack: ";
    cin >> maxWeight;

    vector<Item> items(n);

    // Taking input for weight and benefit of each item
    cout << "Enter the weight and benefit of each item:" << endl;
    for (int i = 0; i < n; ++i) {
        cout << "Item " << i + 1 << " (weight, benefit): ";
        cin >> items[i].weight >> items[i].benefit;
        items[i].value = items[i].benefit / items[i].weight; // Calculate value (benefit-to-weight ratio)
    }

    // Calculate the maximum value that can be obtained
    double maxValue = fractionalKnapsack(items, maxWeight);

    // Print the result
    cout << "The maximum value of the knapsack is: " << maxValue << endl;

    return 0;
}
