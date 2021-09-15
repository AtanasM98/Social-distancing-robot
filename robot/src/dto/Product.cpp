#include "../../../include/Product.h"

Product::Product() : Product(0, 0)
{
    
}

Product::Product(int id, int quantity) 
{
    this->productId = id;
    this->quantity = quantity;
}

int Product::getId() const
{
    return this->productId;
}

void Product::setId(int id) 
{
    this->productId = id;
}

int Product::getQuantity() const
{
    return this->quantity;
}

void Product::setQuantity(int quantity) 
{
    this->quantity = quantity;
}
