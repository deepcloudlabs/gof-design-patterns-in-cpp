#include <iostream>
#include <vector>
#include <memory>

using namespace std;

template<typename Self>
struct cell {
    template<typename T>
    void connect_to(T &other);

    template<typename T>
    T *begin();

    template<typename T>
    T *end();
};

struct neuron : cell<neuron> {
    vector<neuron *> in, out;
    uint32_t id;

    neuron() {
        static int id = 1;
        this->id = id++;
    }

    neuron *begin() { return this; }

    neuron *end() { return this + 1; }
};

struct neuron_layer : cell<neuron_layer> {
    vector<neuron> neurons;

    neuron_layer(int count) {
        while (count-- > 0)
            neurons.emplace_back(neuron{});
    }

    auto begin() { return neurons.begin(); }

    auto end() { return neurons.end(); }

};

template<typename Self>
template<typename T>
void cell<Self>::connect_to(T &other) {
    for (neuron &from : *static_cast<Self *>(this)) {
        for (neuron &to : other) {
            from.out.push_back(&to);
            to.in.push_back(&from);
        }
    }
}

template<typename Self>
ostream &operator<<(ostream &os, cell<Self> &object) {
    for (neuron &obj : *static_cast<Self *>(&object)) {
        for (neuron *n : obj.in)
            os << n->id << "\t-->\t[" << obj.id << "]" << endl;

        for (neuron *n : obj.out)
            os << "[" << obj.id << "]\t-->\t" << n->id << endl;
    }
    return os;
}

int main() {
    neuron n1, n2;
    neuron_layer l1{1}, l2{2};

    n1.connect_to(l1); // Scenario 1: neuron connects to Layer
    l2.connect_to(n2); // Scenario 2: Layer connects to neuron
    l1.connect_to(l2); // Scenario 3: Layer connects to Layer
    n1.connect_to(n2); // Scenario 4: neuron connects to neuron

    cout << "neuron " << n1.id << endl << n1 << endl;
    cout << "neuron " << n2.id << endl << n2 << endl;

    cout << "Layer " << endl << l1 << endl;
    cout << "Layer " << endl << l2 << endl;

    return 0;
}
