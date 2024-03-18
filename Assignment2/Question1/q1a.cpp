#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
using namespace std;

struct Point {
    double x, y;
    Point(double x = 0, double y = 0) : x(x), y(y) {}
};

std::vector<Point> generatePolygonPoints(int n, double radius) {
    std::vector<Point> points;
    
    double angleIncrement = 2 * M_PI / n;
    
    // Generate points different points of a convex polygon
    for (int i = 0; i < n; ++i) {
        double angle = i * angleIncrement;
        double x = radius * cos(angle);
        double y = radius * sin(angle);
        points.emplace_back(x, y);
    }
    
    return points;
}

int main() {

    double radius = 10.0;
    ofstream foutput("polygon_points.txt");

    

    for(int i = 3;i<=20;i++){
    std::vector<Point> circle_points = generatePolygonPoints(i, radius);
    for (int j = 0; j < i; ++j) {
        foutput << "(" << circle_points[j].x << ", " << circle_points[j].y << "),";
    }
    foutput<<"\n";
    }

    return 0;
}
