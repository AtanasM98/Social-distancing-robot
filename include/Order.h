#ifndef ORDER_H
#define ORDER_H

#include "Product.h"
#include <vector>
#include "json.hpp"

class Order
{

    public:
        Order();
        Order(int id, bool completed, std::vector<Product> products, int tableId, int totalPrice);

        std::vector<Product> getProducts() const;
        void setProducts(std::vector<Product> products);

        int getId() const;
        void setId(int id);

        bool isCompleted() const;
        void setComplete(bool state);

        int getTableId() const;
        void setTableId(int id);

        int getPrice() const;
        void setTotalPrice(int price);

        int GetTrayPostion() const;
        void SetTrayPosition(int pos);

        private:
            int orderId;
            bool completed;
            std::vector<Product> products;
            int tableId;
            int totalPrice;
            int trayPos;
};

inline void to_json(nlohmann::json &j, const Order &o)
{
    j["order_id"] = o.getId();
    j["order_complete"] = o.isCompleted();
    j["products"] = o.getProducts();
    j["table"] = o.getTableId();
    j["totalPrice"] = o.getPrice();
}

inline void from_json(const nlohmann::json &j, Order &o)
{
    o.setId(j.at("order_id").get<int>());
    o.setComplete(j.at("orderComplete").get<bool>());
    o.setTableId(j.at("table_id").get<int>());
    o.SetTrayPosition(j.at("tray_location").get<int>());
    // o.setTotalPrice(j.at("totalPrice").get<int>());
    // o.setProducts(j.at("products").get<std::vector<Product>>());
}

#endif