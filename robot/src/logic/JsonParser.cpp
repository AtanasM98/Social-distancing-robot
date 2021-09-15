#include "../../../include/Socket.h"
#include "../../../include/JsonParser.h"

nlohmann::json JsonParser::Serialize(Order order) 
{
    nlohmann::json jsonObject = order;
    jsonObject.push_back(nlohmann::json::object_t::value_type("header", HEADER::PLACEORDER));

    return jsonObject;
}

nlohmann::json JsonParser::SerializeId(std::string identifier)
{
    nlohmann::json jsonObject;
    jsonObject.push_back(nlohmann::json::object_t::value_type("header", HEADER::ID));
    jsonObject.push_back(nlohmann::json::object_t::value_type("name", identifier));

    return jsonObject;
}

nlohmann::json JsonParser::SerializePlaceOrder(Order orderToPlace) 
{
    nlohmann::json jsonObject = orderToPlace;
    jsonObject.push_back(nlohmann::json::object_t::value_type("header", HEADER::PLACEORDER));

    return jsonObject;
}

nlohmann::json JsonParser::SerializeCancelOrder(int orderIDToCancel) 
{
    nlohmann::json jsonObject;
    jsonObject.push_back(nlohmann::json::object_t::value_type("header", HEADER::CANCELORDER));
    jsonObject.push_back(nlohmann::json::object_t::value_type("order_id", orderIDToCancel));

    return jsonObject;
}

nlohmann::json JsonParser::SerializeStartOrder(std::vector<Order> ordersToStart) 
{
    nlohmann::json jsonObject = ordersToStart;
    jsonObject.push_back(nlohmann::json::object_t::value_type("header", HEADER::STARTORDER));

    return jsonObject;
}

nlohmann::json JsonParser::SerializeEditOrder(Order orderToEdit) 
{
    nlohmann::json jsonObject = orderToEdit;
    jsonObject.push_back(nlohmann::json::object_t::value_type("header", HEADER::EDITORDER));

    return jsonObject;
}

nlohmann::json JsonParser::SerializeStatusUpdate(int orderID, int statusID) 
{
    nlohmann::json jsonObject;
    jsonObject.push_back(nlohmann::json::object_t::value_type("header", HEADER::STATUSUPDATE));
    jsonObject.push_back(nlohmann::json::object_t::value_type("order_id", orderID));
    jsonObject.push_back(nlohmann::json::object_t::value_type("status_id", statusID));

    return jsonObject;
}

nlohmann::json JsonParser::SerializeReturn() 
{
    nlohmann::json jsonObject;
    jsonObject.push_back(nlohmann::json::object_t::value_type("header", HEADER::RETURN));

    return jsonObject;
}

nlohmann::json JsonParser::SerializeResult(bool result, std::string message) 
{
    nlohmann::json jsonObject;
    jsonObject.push_back(nlohmann::json::object_t::value_type("header", HEADER::RETURN));
    jsonObject.push_back(nlohmann::json::object_t::value_type("result", result));
    jsonObject.push_back(nlohmann::json::object_t::value_type("message", message));

    return jsonObject;
}

int JsonParser::GetHeader(std::string message) 
{
    nlohmann::json json = nlohmann::json::parse(message);
    return json.at("header").get<int>();
}

Product JsonParser::DeserializeProduct(std::string message) 
{
    nlohmann::json json = nlohmann::json::parse(message);

    json.erase("header");
    Product product = json.get<Product>();
    return product;
}

OrderCollection JsonParser::DeserializeOrder(std::string message) 
{
    nlohmann::json json = nlohmann::json::parse(message);
    json.erase("header");
    OrderCollection collection = json.get<OrderCollection>();
    return collection;
}
