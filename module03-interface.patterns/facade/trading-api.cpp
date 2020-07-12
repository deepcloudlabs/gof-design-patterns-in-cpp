#include <string>
#include <vector>

/**
 * Author: Binnur Kurt <binnur.kurt@gmail.com>
 */
enum hash_algo_enum {
    sha256, sha512
};

struct token_t {
    hash_algo_enum hash_algo;
    std::string token_data;
    std::string signature;

    token_t(hash_algo_enum hashAlgo, const std::string &tokenData, const std::string &signature) : hash_algo(hashAlgo),
                                                                                                   token_data(
                                                                                                           tokenData),
                                                                                                   signature(
                                                                                                           signature) {}
};

enum side_enum {
    bid, ask
};

typedef struct order {
    side_enum side;
    std::string symbol;
} order_t;

struct market_order : public order {
    double quantity;
};

typedef struct limit_order : public order {
    double price;
    double quantity;
} limit_order_t;

class authentication_service {
public:
    token_t get_token(std::string username, std::string password) const {
        return token_t(sha256, std::string("{'roles': ['customer']}"),
                       std::string("257121ce-c383-11ea-87d0-0242ac130003"));
    }
};

typedef struct level_info {
    int level;
    double price;
    double quantity;

    level_info(int level, double price, double quantity) : level(level), price(price), quantity(quantity) {}
} level_info_t;

typedef struct market {
    std::string symbol;
    std::vector<level_info_t> bids;
    std::vector<level_info_t> asks;

    market(const std::string &symbol, const std::vector<level_info_t> &bids, const std::vector<level_info_t> &asks)
            : symbol(symbol), bids(bids), asks(asks) {}

    level_info_t get_best_bid() { return bids[0]; }

    level_info_t get_best_ask() { return asks[0]; }
} market_t;

class market_data_service {
public:
    market_t get_market_data(const std::string symbol, int level) {
        return market_t(symbol, std::vector<level_info_t>{level_info_t(0, 100., 100.)},
                        std::vector<level_info_t>{level_info_t(0, 101., 100.)});
    }
};

class order_service {
public:
    void send_order(const token_t &token, const order_t &order) {}
};

class trading_facade {
    market_data_service &marketDataService;
    order_service &orderService;
    authentication_service &authenticationService;

public:
    trading_facade(market_data_service &marketDataService, order_service &orderService,
                   authentication_service &authenticationService) : marketDataService(marketDataService),
                                                                    orderService(orderService),
                                                                    authenticationService(authenticationService) {}

    void sell(const std::string &username, const std::string &password, const std::string &symbol, double quantity) {
        auto token = authenticationService.get_token(username, password);
        auto market = marketDataService.get_market_data(symbol, 10);
        limit_order sell_order;
        sell_order.price = market.get_best_ask().price;
        sell_order.quantity = quantity;
        orderService.send_order(token, sell_order);
    }
};

int main() {
    market_data_service marketDataService;
    order_service orderService;
    authentication_service authenticationService;
    trading_facade tradingFacade(marketDataService, orderService, authenticationService);
    tradingFacade.sell(std::string("orcl"), "jack", "secret", 100.);
    return 0;
}