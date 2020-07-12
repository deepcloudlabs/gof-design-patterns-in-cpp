#include <iostream>
#include <string>
#include <cstdint>

using namespace std;

#include <boost/bimap.hpp>
#include <boost/flyweight.hpp>
#include <boost/flyweight/key_value.hpp>

using namespace boost;
using namespace flyweights;

typedef uint32_t key;

struct user {
    user(const string &first_name, const string &last_name)
            : first_name{add(first_name)}, last_name{add(last_name)} {
    }

    const string &get_first_name() const {
        return names.left.find(last_name)->second;
    }

    const string &get_last_name() const {
        return names.left.find(last_name)->second;
    }

    static void info() {
        for (auto entry : names.left) {
            cout << "Key: " << entry.first << ", Value: " << entry.second << endl;
        }
    }

    friend ostream &operator<<(ostream &os, const user &obj) {
        return os << "first_name: " << obj.first_name << " " << obj.get_first_name()
                  << " last_name: " << obj.last_name << " " << obj.get_last_name();
    }

protected:
    static bimap<key, string> names;
    static unsigned int seed;

    static key add(const string &s) {
        auto it = names.right.find(s);
        if (it == names.right.end()) {
            // add it
            key id = ++seed;
            names.insert({seed, s});
            return id;
        }
        return it->second;
    }

    key first_name, last_name;
};

key user::seed = 0;
bimap<key, string> user::names{};

void naive_flyweight() {
    user john_doe{"John", "Doe"};
    user jane_doe{"Jane", "Doe"};

    cout << "John " << john_doe << endl;
    cout << "Jane " << jane_doe << endl;

    user::info();
}

struct user2 {
    flyweight<string> first_name, last_name;

    user2(const string &first_name, const string &last_name)
            : first_name(first_name),
              last_name(last_name) {}
};

void boost_flyweight() {
    user2 usr1{"John", "Smith"};
    user2 usr2{"Jane", "Smith"};

    cout << usr1.first_name << endl;

    cout << boolalpha
         << (&usr1.first_name.get() == &usr2.first_name.get()) << endl;
    cout << boolalpha
         << (&usr1.last_name.get() == &usr2.last_name.get()) << endl;
}

int main() {
    naive_flyweight();
    boost_flyweight();

    return 0;
}