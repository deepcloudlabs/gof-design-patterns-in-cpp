#include <cmath>

enum class PointType {
    cartesian,
    polar
};

class Point {
    // use a factory method
    Point(double x, double y) : x(x), y(y) {}

public:
    double x, y;

    friend class PointFactory;
};

class PointFactory {
    static Point NewCartesian(double x, double y) {
        return Point{x, y};
    }

    static Point NewPolar(float r, float theta) {
        return Point{r * cos(theta), r * sin(theta)};
    }
};

int main() {

}