#include <iostream>
#include <cstddef>

bool hasEnding(std::string const &fullString, std::string const &ending) {
    if (fullString.length() >= ending.length()) {
        return (0 == fullString.compare(fullString.length() - ending.length(), ending.length(), ending));
    } else {
        return false;
    }
}

enum color_enum {
    gray8, rgb24
};

struct image {
    int width;
    int height;
    color_enum color;
    std::byte *data;
};

struct image_reader {
    virtual image *load(const std::string &file_name) = 0;
};

struct reader_chain {
    reader_chain(image_reader *next_reader = nullptr) : next_reader(next_reader) {}

    image *next(const std::string &file_name) {
        if (this->next_reader == nullptr) throw std::string("cannot read the image!");
        return this->next_reader->load(file_name);
    }

private:
    image_reader *next_reader;
};

struct jpeg_reader : public image_reader, public reader_chain {
    jpeg_reader(image_reader *next_reader = nullptr) : reader_chain(next_reader) {}

    image *load(const std::string &file_name) {
        if (hasEnding(file_name, "jpg") || hasEnding(file_name, "jpeg")) {
            std::cout << "jpeg_reader loads the image" << std::endl;
            return new image;
        }
        return next(file_name);
    }
};

struct gif_reader : public image_reader, reader_chain {
    gif_reader(image_reader *next_reader = nullptr) : reader_chain(next_reader) {}

    image *load(const std::string &file_name) {
        if (hasEnding(file_name, "gif")) {
            std::cout << "gif_reader loads the image" << std::endl;
            return new image;
        }
        return next(file_name);
    }
};

struct png_reader : public image_reader, reader_chain {
    png_reader(image_reader *next_reader = nullptr) : reader_chain(next_reader) {}

    image *load(const std::string &file_name) {
        if (hasEnding(file_name, "png")) {
            std::cout << "png_reader loads the image" << std::endl;
            return new image;
        }
        return next(file_name);
    }
};

int main() {
    jpeg_reader reader(new gif_reader(new png_reader));
    try {
        reader.load("photo.gif");
        reader.load("photo.png");
        reader.load("photo.jpeg");
        reader.load("photo.jpg");
        reader.load("photo.tiff");
    } catch (std::string &msg) {
        std::cerr << msg << std::endl;
    }
    return 0;
}