#include <iostream>
#include <vector>
#include <cmath>

struct Point {
    double x, y;
    Point(double x = 0, double y = 0) : x(x), y(y) {}
};

std::vector<Point> generateCirclePoints(int n, double radius) {
    std::vector<Point> points;
    
    double angleIncrement = 2 * M_PI / n;
    
    // Generate points on the circle with increasing order of angles
    for (int i = 0; i < n; ++i) {
        double angle = i * angleIncrement;
        double x = radius * cos(angle);
        double y = radius * sin(angle);
        points.emplace_back(x, y);
    }
    
    return points;
}

int main() {
    int n;
    double radius = 10.0;
    std::cout << "Enter the number of points for the circle: ";
    std::cin >> n;

    std::vector<Point> circle_points = generateCirclePoints(n, radius);

    std::cout << "Circle Points:\n";
    for (int i = 0; i < n; ++i) {
        std::cout << circle_points[i].x << ", " << circle_points[i].y << "\n";
    }

    return 0;
}
