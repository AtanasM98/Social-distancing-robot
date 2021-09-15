#ifndef PRODUCT_H
#define PRODUCT_H

#include "json.hpp"

class Product
{
    public:
        Product();
        Product(int id, int quantity);

    int getId() const;
    void setId(int id);

    int getQuantity() const;
    void setQuantity(int quantity);

    private:
        int productId;
        int quantity;
};

inline void to_json(nlohmann::json &j, const Product &p)
{
    j["product_id"] = p.getId();
    j["quantity"] = p.getQuantity();
}

inline void from_json(const nlohmann::json &j, Product &p)
{
    p.setId(j.at("product_id").get<int>());
    p.setQuantity(j.at("quantity").get<int>());
}

#endif