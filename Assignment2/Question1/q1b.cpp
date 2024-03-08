// Recursive implementation for minimum cost convex polygon triangulation
#include <iostream>
#include<vector>
#include <cmath>
#define MAX 1000000.0
using namespace std;

// Structure of a point in 2D plane
struct Point
{
	double x, y;
    Point(double x = 0, double y = 0) : x(x), y(y) {}
};

// Utility function to find minimum of two double values
double min(double x, double y)
{
	return (x <= y)? x : y;
}

// A utility function to find distance between two points in a plane
double dist(Point p1, Point p2)
{
	return sqrt((p1.x - p2.x)*(p1.x - p2.x) +
				(p1.y - p2.y)*(p1.y - p2.y));
}

// A utility function to find cost of a triangle. The cost is considered
// as perimeter (sum of lengths of all edges) of the triangle
double cost(vector<Point> &points, int i, int j, int k)
{
	Point p1 = points[i], p2 = points[j], p3 = points[k];
	return dist(p1, p2) + dist(p2, p3) + dist(p3, p1);
}

// A recursive function to find minimum cost of polygon triangulation
// The polygon is represented by points[i..j].
double mTC(vector<Point> &points, int i, int j)
{
// There must be at least three points between i and j
// (including i and j)
if (j < i+2)
	return 0;

// Initialize result as infinite
double res = MAX;

// Find minimum triangulation by considering all
for (int k=i+1; k<j; k++)
		res = min(res, (mTC(points, i, k) + mTC(points, k, j) +
						cost(points, i, k, j)));
return res;
}

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

// Driver program to test above functions
int main()
{
    int n;
    double radius = 10.0;
    std::cout << "Enter the number of points for the circle: ";
    std::cin >> n;

    std::vector<Point> points = generateCirclePoints(n, radius);
	cout << mTC(points, 0, n-1);
	return 0;
}
