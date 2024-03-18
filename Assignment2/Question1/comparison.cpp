#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <limits>
#define MAX 1000000.0
using namespace std;
struct Point {
    double x, y;
    Point(double x = 0, double y = 0) : x(x), y(y) {}
};

double distance(const Point& p1, const Point& p2) {
    return sqrt(pow(p2.x - p1.x, 2) + pow(p2.y - p1.y, 2));
}

double greedyMinimumCost(const std::vector<Point>& polygon) {
    double minCost = 0.0;
    std::vector<Point> vertices = polygon;
    int n = vertices.size();

    while (n > 3) {
        bool earFound = false;
        double minTriangleCost = std::numeric_limits<double>::max();
        int minTriangleIndex = -1;

        for (int i = 0; i < n; ++i) {
            int prev = (i + n - 1) % n;
            int next = (i + 1) % n;
            double side1 = distance(vertices[prev], vertices[i]);
            double side2 = distance(vertices[i], vertices[next]);
            double side3 = distance(vertices[next], vertices[prev]);
            double currentTriangleCost = side1 + side2 + side3;

            if (currentTriangleCost < minTriangleCost) {
                bool isEar = true;
                for (int j = 0; j < n; ++j) {
                    if (j != prev && j != i && j != next &&
                        distance(vertices[prev], vertices[i]) +
                            distance(vertices[i], vertices[next]) ==
                            distance(vertices[j], vertices[prev]) +
                            distance(vertices[j], vertices[next])) {
                        isEar = false;
                        break;
                    }
                }
                if (isEar) {
                    minTriangleCost = currentTriangleCost;
                    minTriangleIndex = i;
                    earFound = true;
                }
            }
        }
        if (earFound) {
            minCost += minTriangleCost;
            vertices.erase(vertices.begin() + minTriangleIndex);
            n--;
        } else {
            break;
        }
    }

    return minCost;
}
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
double mTCDP(vector<Point> &points, int n)
{
    if (n < 3) return 0;
    double table[n][n];
    for (int gap = 0; gap < n; gap++)
    {
        for (int i = 0, j = gap; j < n; i++, j++)
        {
            if (j < i+2)
                table[i][j] = 0.0;
            else
            {
                table[i][j] = MAX;
                for (int k = i+1; k < j; k++)
                {
                    double val = table[i][k] + table[k][j] + cost(points,i,j,k);
                    if (table[i][j] > val)
                        table[i][j] = val;
                }
            }
        }
    }
    return table[0][n-1];
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

int main() {
    double radius = 10.0;
    int n = 3;
    ofstream foutput("percentage-error.txt");

    while(n <= 100){
        std::vector<Point> polygon = generateCirclePoints(n, radius);
        float start_time = clock();
        cout<<"n : "<<n<<endl;
        double greedyCost = greedyMinimumCost(polygon);
        double dpCost = mTCDP(polygon,polygon.size());

        double percentageError = ((dpCost - greedyCost) / dpCost) * 100.0;
        foutput<<percentageError<<",\n";
        std::cout << "Greedy cost: " << greedyCost << std::endl;
        std::cout << "Dynamic programming cost: " << dpCost << std::endl;
        std::cout << "Percentage error: " << percentageError << "%" << std::endl;
        
        n++;
    }


    return 0;
}
