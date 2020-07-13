#include <cmath>

// do not need this for factory
enum class PointType {
    cartesian,
    polar
};

class Point {
    /*Point(float a, float b, PointType type = PointType::cartesian)
    {
    if (type == PointType::cartesian)
    {
    x = a; b = y;
    }
    else
    {
    x = a*cos(b);
    y = a*sin(b);
    }
    }*/

    // use a factory method
    Point(double x, double y) : x(x), y(y) {}

    class PointFactory {
        PointFactory() {}

    public:
        static Point NewCartesian(double x, double y) {
            return {x, y};
        }

        static Point NewPolar(double r, double theta) {
            return {r * cos(theta), r * sin(theta)};
        }
    };

public:
    double x, y;
    static PointFactory Factory;
};

int main() {
    // will not work
    // Point p{ 1,2 };

    // nope!
    // Point::PointFactory pf;

    // if factory is public, then
    //auto p = Point::PointFactory::NewCartesian(3, 4);

    // at any rate, use this
    auto pp = Point::Factory.NewCartesian(2, 3);

    return 0;
}