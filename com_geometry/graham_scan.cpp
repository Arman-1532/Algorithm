#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Define a Point structure
struct Point {
    int x, y;
};

// Helper function to find the orientation of the ordered triplet (p, q, r)
// 0 --> p, q, and r are collinear
// 1 --> Clockwise
// 2 --> Counterclockwise
int orientation(Point p, Point q, Point r) {
    int val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);
    if (val == 0) return 0;           // Collinear
    return (val > 0) ? 1 : 2;         // Clockwise or Counterclockwise
}

// Comparison function to sort points by polar angle with respect to the lowest point
bool compare(Point p1, Point p2) {
    return (p1.x < p2.x) || (p1.x == p2.x && p1.y < p2.y);
}

// Function to compute the convex hull using Graham's Scan algorithm
vector<Point> convexHull(vector<Point>& points) {
    int n = points.size();
    if (n < 3) return {};  // Convex hull is not possible with fewer than 3 points

    // Step 1: Find the bottom-most point (or leftmost if tie)
    int minYIndex = 0;
    for (int i = 1; i < n; i++)
        if (points[i].y < points[minYIndex].y || 
            (points[i].y == points[minYIndex].y && points[i].x < points[minYIndex].x))
            minYIndex = i;

    // Place the lowest point at the beginning
    swap(points[0], points[minYIndex]);

    // Step 2: Sort remaining points based on polar angle with respect to the pivot
    Point pivot = points[0];
    sort(points.begin() + 1, points.end(), [pivot](Point p1, Point p2) {
        int orient = orientation(pivot, p1, p2);
        if (orient == 0)  // If collinear, place closer point first
            return (p1.x - pivot.x) * (p1.x - pivot.x) + (p1.y - pivot.y) * (p1.y - pivot.y) <
                   (p2.x - pivot.x) * (p2.x - pivot.x) + (p2.y - pivot.y) * (p2.y - pivot.y);
        return (orient == 2); // Counterclockwise comes first
    });

    // Step 3: Build the convex hull using a stack
    vector<Point> hull;
    hull.push_back(points[0]);
    hull.push_back(points[1]);
    hull.push_back(points[2]);

    for (int i = 3; i < n; i++) {
        while (hull.size() > 1 && orientation(hull[hull.size() - 2], hull.back(), points[i]) != 2)
            hull.pop_back();  // Remove last point if it makes a clockwise turn
        hull.push_back(points[i]);
    }

    return hull;
}

// Driver function
int main() {
    vector<Point> points = {{0, 3}, {2, 2}, {1, 1}, {2, 1}, {3, 0}, {0, 0}, {3, 3}};
    
    vector<Point> hull = convexHull(points);

    cout << "Convex Hull Points: \n";
    for (auto p : hull)
        cout << "(" << p.x << ", " << p.y << ")\n";

    return 0;
}