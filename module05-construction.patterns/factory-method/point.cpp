#include <cmath>

struct Point {
    static Point newCartesian(double x, double y) {
        return {x, y};
    }

    static Point newPolar(double r, double theta) {
        return {r * cos(theta), r * sin(theta)};
    }

private:
    double x, y;
protected:
    Point(const double x, const double y) : x{x}, y{y} {}
};

int main() {

    auto p = Point::newPolar(5, M_PI_4);
    return 0;
}
