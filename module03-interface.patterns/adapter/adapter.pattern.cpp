#include <vector>
#include <iostream>
#include <memory>

struct Point {
    int x, y;
};

struct Line {
    Point start, end;
};

struct Polygon {
    virtual std::vector<Line>::iterator begin() = 0;

    virtual std::vector<Line>::iterator end() = 0;
};

struct Rectangle : Polygon {
    Rectangle(int x, int y, int width, int height) {
        lines.emplace_back(Line{Point{x, y},
                                Point{x + width, y}});
        lines.emplace_back(Line{Point{x + width, y},
                                Point{x + width, y + height}});
        lines.emplace_back(Line{Point{x, y},
                                Point{x, y + height}});
        lines.emplace_back(Line{Point{x, y + height},
                                Point{x + width, y + height}});
    }

    std::vector<Line>::iterator begin() override {
        return lines.begin();
    }

    std::vector<Line>::iterator end() override {
        return lines.end();
    }

private:
    std::vector<Line> lines;
};

std::ostream &operator<<(std::ostream &out, const Point &point) {
    out << "Point[ x=" << point.x << ", y=" << point.y << " ]";
    return out;
}

void DrawPoints(std::vector<Point>::iterator start, std::vector<Point>::iterator end) {
    for (auto point = start; point != end; point++)
        std::cout << "Drawing " << *point << std::endl;
}

struct LineToPointAdapter {

    LineToPointAdapter(Line &line) {
        int left = std::min(line.start.x, line.end.x);
        int right = std::max(line.start.x, line.end.x);
        int top = std::min(line.start.y, line.end.y);
        int bottom = std::max(line.start.y, line.end.y);
        int dx = right - left;
        int dy = line.end.y - line.start.y;

        if (dx == 0) {
            for (int y = top; y <= bottom; ++y) {
                points.emplace_back(Point{left, y});
            }
        } else if (dy == 0) {
            for (int x = left; x <= right; ++x) {
                points.emplace_back(Point{x, top});
            }
        }
    }

    virtual std::vector<Point>::iterator begin() { return points.begin(); }

    virtual std::vector<Point>::iterator end() { return points.end(); }

private:
    std::vector<Point> points;
};

int main() {
    std::vector<std::shared_ptr<Rectangle>> rectangles{
            std::make_shared<Rectangle>(10, 10, 5, 5),
            std::make_shared<Rectangle>(20, 20, 10, 10)
    };
    for (auto &rec : rectangles) {
        for (auto &line: *rec) {
            LineToPointAdapter lpo{line};
            DrawPoints(lpo.begin(), lpo.end());
        }
    }

    return 0;
}