#include "../../../include/Order.h"

Order::Order() : Order(0, false, std::vector<Product>(), 0, 0)
{
    
}

Order::Order(int id, bool completed, std::vector<Product> products, int tableId, int totalPrice) 
{
    this->orderId = id;
    this->completed = completed;
    this->products = products;
    this->tableId = tableId;
    this->totalPrice = totalPrice;
}

std::vector<Product> Order::getProducts() const
{
    return this->products;
}

void Order::setProducts(std::vector<Product> products) 
{
    this->products = products;
}

int Order::getId() const
{
    return this->orderId;
}

void Order::setId(int id) 
{
    this->orderId = id;
}

bool Order::isCompleted() const
{
    return this->completed;
}

void Order::setComplete(bool state) 
{
    this->completed = state;
}

int Order::getTableId() const
{
    return this->tableId;
}

void Order::setTableId(int id) 
{
    this->tableId = id;
}

int Order::getPrice() const
{
    return this->totalPrice;
}

void Order::setTotalPrice(int price) 
{
    this->totalPrice = price;    
}

int Order::GetTrayPostion() const
{
    return this->trayPos;
}

void Order::SetTrayPosition(int pos) 
{
    this->trayPos = pos;
}
