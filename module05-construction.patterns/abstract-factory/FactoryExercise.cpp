#include <vector>
#include <string>

using namespace std;

struct Person {
    int id;
    string name;
};

class PersonFactory {
    int id{0};
public:
    Person create_person(const string &name) {
        return {id++, name};
    }
};

int main() {
    PersonFactory pf;
    auto p1 = pf.create_person("Jack");
    auto p2 = pf.create_person("Kate");

    return 0;
}