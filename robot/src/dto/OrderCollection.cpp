#include "../../../include/OrderCollection.h"

OrderCollection::OrderCollection() 
{
    
}

std::vector<Order> OrderCollection::GetOrders() const
{
    return this->orders;
}

void OrderCollection::SetOrders(std::vector<Order> orders) 
{
    this->orders = orders;
}