#ifndef JSONPARSER_H
#define JSONPARSER_H

#include "Order.h"
#include "ISocket.h"
#include "OrderCollection.h"
#include <string>
#include <vector>

/** 
* Class for handling JSON serialization and deserialization.
*/
class JsonParser
{

    public:
        /**
        * Serializes the given order into a JSON string. 
        * @param order The order to serialize to JSON.
        * @return nlohmann::json
        */
        nlohmann::json Serialize(Order order);

        /**
        * Serializes the given robot identifier into a JSON string.
        * @param identifier The robot identifier.
        * @return nlohmann::json
        */
        nlohmann::json SerializeId(std::string identifier);

        nlohmann::json SerializePlaceOrder(Order orderToPlace);
        nlohmann::json SerializeCancelOrder(int orderIDToCancel);
        nlohmann::json SerializeStartOrder(std::vector<Order> ordersToStart);
        nlohmann::json SerializeEditOrder(Order orderToEdit);
        nlohmann::json SerializeStatusUpdate(int orderID, int statusID);
        nlohmann::json SerializeReturn();
        nlohmann::json SerializeResult(bool result, std::string message);

        /**
        * Extracts the header id from the given JSON string.
        * @param message The JSON string.
        * @return the header id as integer.
        */
        int GetHeader(std::string message);

        /**
        * Deserializes the given string into a new Order object.
        * @param message The JSON string.
        * @return The created order object.
        */
        OrderCollection DeserializeOrder(std::string message);
        Product DeserializeProduct(std::string message);
};


#endif