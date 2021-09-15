# start order, OrderId
# return


import sys
import socket
import json
from collections import Counter
import time
import random

ipAdress = "127.0.0.1"
port = 65432

HEADERS = {
    "PLACEORDER": 0,
    "CANCELORDER": 1,
    "STARTORDER": 2,
    "EDITORDER": 3,
    "STATUSUPDATE": 4,
    "RETURN": 5,
    "RESULT": 6,
    "BILL": 7,
    "ID": 8,
    "GETOPENORDERS": 9}


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
    print(JsonString)
    obj = json.loads(JsonString)
    head = obj["header"]
    if head == HEADERS["RESULT"]:
        return head, obj["result"]
    elif (head == HEADERS["PLACEORDER"]):
        return head, Order(obj["header"], obj["table"], obj["totalPrice"], obj["products"])
    elif head == HEADERS["BILL"]:
        jsonOrdersObjList = obj["orders"]
        orderList = []
        print(jsonOrdersObjList)
        for item in jsonOrdersObjList:
            orderList.append(
                Order(HEADERS["PLACEORDER"], item["table"], item['totalPrice'], item['products']))

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
        return "My description is: \n {}".format(self.GenerateJSON())

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


def CreateOrderStartDict(order_id, orderComplete, table_id, tray_location):
    return {"order_id": order_id, "orderComplete": orderComplete, "table_id": table_id, "tray_location": tray_location}


def CreateStartOrderMessage(orderlist):
    header = 2
    orders = []
    for ord in orderlist:
        orders.append(ord)
    ret = "{{\"header\":{}, \"orders\":{} }}".format(
        json.dumps(header), json.dumps(orders))
    return ret


def requestBill(tableNumber):
    return "{{ \"header\": {}, \"table\": {} }}".format(HEADERS["BILL"], tableNumber)


def getOpenOrdersRequest():
    return "{{ \"header\": {} }}".format(HEADERS["GETOPENORDERS"])


if __name__ == "__main__":
    if len(sys.argv) > 1:
        ipAdress = sys.argv[1]
    ui = UI()
    ui.newOrder()

    #####
    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    sock.connect((ipAdress, port))
    print("Hello bartander, which table would you like options for")
    table = ui.getTable()
    while True:

        print("press 1 to start order \n press 2 to create a new order. \n press 3 to change the table \n press q to quit")
        put = input()
        if put == '1':
            data = sendMessage(sock, bytearray(
                getOpenOrdersRequest(), "utf-8"))
            print(data)
            js = json.loads(data)
            orders = js["orders"]
            for ord in orders:
                print("idx: {} entire order: {}".format(ord["idx"], ord))
            print("please select and index and press enter.")
            inp = int(input().strip())
            order = CreateOrderStartDict(inp, False, table, 0)

            sendMessage(sock, bytearray(
                CreateStartOrderMessage([order]), "utf-8"))
            print("sent to active")

        elif put == '2':
            ui.newOrder()
            price, products = ui.getDrinks()
            o = Order(HEADERS["PLACEORDER"], table, price, products)
            sendMessage(sock, bytearray(o.GenerateJSON(), "utf-8"))

        elif put == '3':
            table = ui.getTable()
        elif put == 'q':
            sock.close()
            print("bye bye")
            exit()

        # js = json.loads(data)
        # orderToFinish = js["orders"][0]
        # starordemsg = CreateOrderStartDict(100, False, table, 0)
        # starordemsg = CreateStartOrderMessage([starordemsg])
        # print(sendMessage(sock, bytearray(starordemsg, "utf-8")))

        # data = sendMessage(sock, bytearray(requestBill(table), "utf-8"))
        # sock.recv(1024)
        # ParseJSON(data)
        # print(data)

        print("Message sent!")
    sock.close()
    #####
