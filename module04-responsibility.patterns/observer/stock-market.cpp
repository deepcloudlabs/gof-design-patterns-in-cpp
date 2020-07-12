#include <iostream>
#include <vector>
#include <algorithm>

template<typename T>
struct observer {
    virtual void field_changed(T &source, const std::string &field_name) = 0;
};

template<typename T>
struct observable {
    void notify(T &source, const std::string &name) {
        for (auto &observer : observers)
            observer->field_changed(source, name);
    }

    void subscribe(observer<T> *f) { observers.push_back(f); }

    void unsubscribe(observer<T> *f) {
        auto end = std::remove(observers.begin(), observers.end(), f);
        observers.erase(end, observers.end());
    }

private:
    std::vector<observer<T> *> observers;
};

typedef struct stock : public observable<stock> {
    stock(const std::string &symbol, double price) : symbol(symbol), price(price) {}

    const std::string &getSymbol() const {
        return symbol;
    }

    double getPrice() const {
        return price;
    }

    void setPrice(double price) {
        stock::price = price;
        notify(*this, "price");
    }

private:
    const std::string symbol;
    double price;
} stock_t;


struct algotrader : observer<stock_t> {
    void field_changed(stock_t &source, const std::string &field_name) override {
        std::cout << "stock's " << field_name << " has changed to " << source.getPrice() << ".\n";
    }
};

int main() {
    stock orcl("orcl", 100.0);
    algotrader *pAlgotrader = new algotrader();
    orcl.subscribe(pAlgotrader);
    orcl.setPrice(100.2);
    orcl.setPrice(100.4);
    orcl.unsubscribe(pAlgotrader);
    orcl.setPrice(101.1);
    return 0;
}