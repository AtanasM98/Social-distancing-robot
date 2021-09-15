import sys
import socket
import json
from collections import Counter
import time
import random

ipAdress = "127.0.0.1"
port = 65432


def sendMessage(soc, msg):
    sentTotal = 0
    while sentTotal < len(msg):
        sent = soc.send(msg[sentTotal:])
        if sent == 0:
            raise RuntimeError("could not send message (part)")
        sentTotal += sent
    data = soc.recv(1024)
    return data


def ParseJSON(JsonString):

    obj = json.loads(JsonString)
    head = obj["header"]
    if head == "RESULT":
        return head, obj["result"]
    elif (head == "PLACEORDER"):
        return head, Order(obj["header"], obj["table"], obj["totalPrice"], obj["products"])
    elif head == "BILL":
        jsonOrdersObjList = obj["orders"]
        orderList = []
        print(jsonOrdersObjList)
        for item in jsonOrdersObjList:
            orderList.append(
                Order("PLACEORDER", item["table"], item['totalPrice'], item['products']))

        print(orderList[0])
        return head, jsonOrdersObjList
    else:
        raise NotImplementedError()


# {"header": "BILL",
#  "orders": [
#      "{" table ": 69, " totalPrice ": 21.0, " product ": {" 2 ": 3}}",
#      "{" table ": 69, " totalPrice ": 21.0, " product ": {" 2 ": 3}}",
#      "{"table": 69, "totalPrice": 21.0, "product": {"2": 3}}"]}'


# class BILL:
#     products = []
#     price = 0
#     table = 0

#     def __init__(self, products, price, table):
#         self.table = table
#         self.products = products
#         self.price = price

#     def GenerateJSON(self):
#         string = json.dumps(self.__dict__)
#         string = string.replace("\\", '')
#         return string


class Order:
    Header = ""
    table = 0
    price = 0.0

    products = dict()

    def SetOrder(self, header, tableidx, totalPrice, products, productsIsFrequencyList=False):
        self.header = header
        self.table = tableidx
        self.totalPrice = totalPrice
        if productsIsFrequencyList:
            self.products = products
        else:
            self.products = Counter(products)

    def __init__(self, header, tableidx, totalPrice, products):
        self.SetOrder(header, tableidx, totalPrice, products)

    def __str__(self):
        return " HIII my description is: \n {}".format(self.GenerateJSON())

    def GenerateJSON(self):
        string = json.dumps(self.__dict__)
        string = string.replace("\\", '')
        return string


class UI:
    drinks = {0: "Coke", 1: "Coffee", 2: "Beer"}
    prices = {0: 2.5, 1: 2.0, 2: 7.0}
    Products = []
    price = 0

    def newOrder(self):
        Products = []
        price = 0

    def showDrinkSelection(self):
        print("your current order is: {} ".format(self.Products))
        for i in range(len(list(self.drinks.keys()))):
            print("press {} to order 1 {}".format(
                list(self.drinks.keys())[i], list(self.drinks.values())[i]))
        print()
        print("press c to complete order")


# returns whether order the order is valid

    def getDrinks(self):
        self.showDrinkSelection()
        ipt = ""
        ipt = input()
        if ipt == "":
            print("you cant order nothing")
            self.showDrinkSelection()
            return None, None

        ipt = ipt.split(" ")
        ipt = ipt[0]
        ipt = ipt.strip()
        if ipt == 'c':
            return self.price, self.Products
        ipt = int(ipt)
        if not ipt in list(self.drinks.keys()):
            print("item: {} not available".format(ipt))
            self.getDrinks()
        else:
            print("please input the amount")
            amount = int(input().split()[0].strip())
            for _ in range(amount):
                self.Products.append(ipt)
                self.price += list(self.prices.values())[ipt]
            self.getDrinks()
            return self.price, self.Products

            # print("item: {} added to order".format(
            #     list(self.drinks.values())[item]))
            # self.Products.append(item)
            # self.price += list(self.prices.values())[item]

    def getTable(self):
        print("please input the table number followed by an enter")
        inpt = input()
        inpt = inpt.split(" ")
        return int(inpt[0])


def requestBill(tableNumber):
    return "{{ \"header\": \"BILL\", \"table\": {} }}".format(tableNumber)


if __name__ == "__main__":
    if len(sys.argv) > 1:
        ipAdress = sys.argv[1]
    TableNumber = random.randrange(0, 100)
    ui = UI()
    ui.newOrder()
    table = TableNumber
    price, Products = ui.getDrinks()
    o = Order("PLACEORDER", table, price, Products)
    #####
    # print(str(o))
    #####

    #####
    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    sock.connect((ipAdress, port))
    sendMessage(sock, bytearray(o.GenerateJSON(), "utf-8"))
    sendMessage(sock, bytearray(o.GenerateJSON(), "utf-8"))
    sendMessage(sock, bytearray(o.GenerateJSON(), "utf-8"))
    data = sendMessage(sock, bytearray(requestBill(TableNumber), "utf-8"))
    ParseJSON(data)

    sendMessage(sock, bytearray(o.GenerateJSON(), "utf-8"))

    print("Message sent!")
    sock.close()
    #####
