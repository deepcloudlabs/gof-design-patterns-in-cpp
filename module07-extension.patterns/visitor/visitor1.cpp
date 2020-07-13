#include <vector>
#include <typeinfo>
#include <iterator>
#include <iostream>
#include <functional>

using namespace std;

class Sensor;

struct Visitor {
    virtual void operator()(Sensor *sensor) = 0;
};

struct Sensor {
    virtual void visit(Visitor &visitor) = 0;

    virtual void visit(std::function<void(Sensor *)>) = 0;

    virtual double readSensorValue() = 0;
};

class Reporter : public Visitor {
public:
    void operator()(Sensor *sensor) {
        cout << "Reading sensor (" << typeid(*sensor).name() << ") value: " << sensor->readSensorValue() << endl;
    }
};

class Alarmer : public Visitor {
public:
    void accept(Sensor *sensor) {
        cout << "Reading sensor (" << typeid(*sensor).name() << ") value: " << sensor->readSensorValue() << endl;
    }
};

class Composite {
protected:
    vector<Sensor *> sensors;
public:
    virtual void visit(Visitor &visitor) = 0;

    virtual void visit(std::function<void(Sensor *)> visitor) = 0;

    void add(Sensor *sensor) {
        sensors.push_back(sensor);
    }
};

class TemperatureSensor : public Sensor {
private:
    double temperature;
public:
    TemperatureSensor(double temperature = 24.) : temperature(temperature) {}

    void visit(Visitor &visitor) {
        visitor(this);
    }

    void visit(std::function<void(Sensor *)> visitor) override {
        visitor(this);
    }

    double readSensorValue() {
        return temperature;
    }
};

class HumiditySensor : public Sensor {
private:
    double humidity;
public:
    HumiditySensor(double humidity = 6.) : humidity(humidity) {}

    void visit(Visitor &visitor) override {
        visitor(this);
    }

    void visit(std::function<void(Sensor *)> visitor) override {
        visitor(this);
    }

    double readSensorValue() {
        return humidity;
    }
};


class Room : public Composite {
public:
    void visit(Visitor &visitor) override {
        for (auto it = sensors.begin(); it != sensors.end(); ++it) {
            (*it)->visit(visitor);
        }
    }

    void visit(std::function<void(Sensor *)> visitor) override {
        for (auto it = sensors.begin(); it != sensors.end(); ++it) {
            (*it)->visit(visitor);
        }
    }
};

int main(int argc, char *argv[]) {
    Room roomA;
    TemperatureSensor ts1, ts2;
    HumiditySensor hs1, hs2;
    roomA.add(&ts1);
    roomA.add(&hs1);
    roomA.add(&ts1);
    roomA.add(&hs2);
    Reporter reporter;
    roomA.visit(reporter);
    roomA.visit([](Sensor *sensor) {
        cout << "Reading sensor (" << typeid(*sensor).name() << ") value: " << sensor->readSensorValue() << endl;
    });
    return 0;
}

