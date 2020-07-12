#include <boost/functional/hash.hpp>
#include <iostream>

typedef struct cacheable {
    virtual std::size_t hash_code() const = 0;
} cacheable_t;

typedef struct point : public cacheable_t {
    const int x, y;

    point(int x, int y) : x(x), y(y) {}

    std::size_t hash_code() const override {
        std::size_t seed = 0x725C686F;
        boost::hash_combine(seed, this->x);
        boost::hash_combine(seed, this->y);
        return seed;
    }
} point_t;


struct object_caching {
    static std::map<std::size_t, cacheable_t *> cache;
protected:
    object_caching() {
        static int instance_count{0};
        if (++instance_count > 1)
            throw "Cannot create multiple caches!";
    }

public:
    static object_caching &get_instance() {
        // thread-safe in C++11
        static object_caching instance;
        return instance;
    }

    object_caching(object_caching const &) = delete;

    object_caching(object_caching &&) = delete;

    object_caching &operator=(object_caching const &) = delete;

    object_caching &operator=(object_caching &&) = delete;
    cacheable_t* put(cacheable_t *obj) {
        size_t hash_code = obj->hash_code();
        const std::map<std::size_t, cacheable_t *>::iterator &found = cache.find(hash_code);
        if (found == cache.end()) {
            cache[hash_code] = obj;
            return obj;
        }
        delete obj;
        return found->second;
    }
};

std::map<std::size_t, cacheable_t *>  object_caching::cache;

int main() {
    auto &cache1 = object_caching::get_instance();
    auto &cache2 = object_caching::get_instance();
    point_t *p1 = new point_t {0, 0};
    point_t *p2 = new point_t {0, 0};
    std::cerr << "p1: " << std::hex << p1 << std::endl;
    std::cerr << "p2: " << std::hex << p2 << std::endl;
    p1 = dynamic_cast<point_t *>(cache1.put(p1));
    p2 = dynamic_cast<point_t *>(cache1.put(p2));
    std::cerr << "p1: " << std::hex << p1 << std::endl;
    std::cerr << "p2: " << std::hex << p2 << std::endl;
    return 0;
}