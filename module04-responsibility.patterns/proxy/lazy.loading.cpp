#include <iostream>
#include <memory>

typedef struct image {
    virtual void draw() = 0;
} image_t;

struct jpeg : image_t {
    const std::string &filename;

    jpeg(const std::string &filename) : filename(filename) {
        std::cout << "Loading image from " << filename << std::endl;
    }

    void draw() override {
        std::cout << "Drawing image " << filename << std::endl;
    }
};

struct lazy_image : public image_t {
    lazy_image(const std::string &filename) : filename(filename) {}

    void draw() override {
        if(jpeg_image.get() == nullptr)
            jpeg_image = std::make_shared<jpeg>(jpeg(filename));
        jpeg_image->draw();
    }
private:
    const std::string &filename;
    std::shared_ptr<jpeg> jpeg_image;
};

int main(){
    jpeg img1("photo1.png");
    jpeg img2("photo2.png");
    lazy_image img3("photo3.png");
    std::cout << "photo3.png is not loaded yet!" << std::endl;
    img3.draw();
    return 0;
}