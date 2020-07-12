#include <iostream>
#include <memory>

class rendering_service;

class shape {
protected:
    rendering_service &renderingService;
public:
    shape(rendering_service &renderingService) : renderingService(renderingService) {}

    virtual void draw() = 0;
};

class rendering_service {
public:
    virtual void render(const shape &s) = 0;
};

class raster_rendering : public rendering_service {
public:
    void render(const shape &s) override {
        std::cerr << "Raster rendering the " << typeid(s).name() << std::endl;
    }
};

class vector_rendering : public rendering_service {
public:
    void render(const shape &s) override {
        std::cerr << "Vector rendering the " << typeid(s).name() << std::endl;
    }
};

class circle : public shape {
private:
    double x, y, radius;
public:
    circle(rendering_service &renderingService, double x, double y, double radius) : shape(renderingService),
                                                                                     x(x), y(y), radius(radius) {}

    void draw() override {
        this->renderingService.render(*this);
    }
};

class rectangle : public shape {
private:
    double top_x, top_y;
    double width, height;
public:
    rectangle(rendering_service &renderingService, double topX, double topY, double width, double height) : shape(
            renderingService), top_x(topX), top_y(topY), width(width), height(height) {}

    void draw() override {
        this->renderingService.render(*this);
    }
};

int main() {
    vector_rendering vr;
    raster_rendering rr;
    circle vector_unit_circle(vr, 0, 0, 1);
    circle raster_unit_circle(rr, 0, 0, 1);
    vector_unit_circle.draw();
    raster_unit_circle.draw();
    rectangle vector_rect(vr, 0, 0, 10, 10);
    rectangle raster_rect(rr, 0, 0, 20, 30);
    vector_rect.draw();
    raster_rect.draw();
    return 0;
}