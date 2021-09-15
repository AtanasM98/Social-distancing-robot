#ifndef ORDERCOLLECTION_H
#define ORDERCOLLECTION_H

#include "Product.h"
#include "Order.h"
#include <vector>
#include "json.hpp"

class OrderCollection
{
    public:
        OrderCollection();
        std::vector<Order> GetOrders() const;
        void SetOrders(std::vector<Order> orders);
 
        private:
            std::vector<Order> orders;
};

inline void from_json(const nlohmann::json &j, OrderCollection &o)
{
    o.SetOrders(j.at("orders").get<std::vector<Order>>());
}

#endif //  ORDERCOLLECTION_H