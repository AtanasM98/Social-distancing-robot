import socket
import os
from _thread import *
import json

ServerSocket = socket.socket()
host = '127.0.0.1'
port = 65432
ThreadCount = 0
filePath = "./Orders.txt"
robots = []
robotPort = 55544 # tmp

HEADERS = { 
    "PLACEORDER" : 0, 
    "CANCELORDER" : 1, 
    "STARTORDER" : 2,
    "EDITORDER" : 3,
    "STATUSUPDATE" : 4,
    "RETURN" : 5,
    "RESULT" : 6,
    "BILL" : 7,
    "ID" : 8,
    "GETOPENORDERS" : 9 
    }

try:
    ServerSocket.bind((host, port))
except socket.error as e:
    print(str(e))

print('Waiting for a Connection..')
ServerSocket.listen(5)

def GetOpenOrders( JsonString, conn ):
    fileObj = open( filePath, "r" )
    orders = fileObj.readlines()
    jstr = "{\"header\": 9, \"orders\": ["
    for order in orders:
        strippedOrder = order.strip("   \n")
        if not strippedOrder.endswith( " FINISHED" ) and len(strippedOrder) > 1:
            jstr = jstr + "{\"idx\": " + str(orders.index(order)) + ", " + strippedOrder[1:] + ", "
    jstr = jstr[:-2] + "]}"
    conn.sendall(str.encode(jstr))

def ReturnOrderList( tableNr ):
    fileObj = open( filePath, "r" )
    orders = fileObj.readlines()
    validOrders = "["
    for order in orders:
        if order.startswith( "{\"table\": " + str(tableNr) ):
            if order.endswith( " FINISHED" ):
                validOrders += order[:-10]
            else:
                validOrders += order[:-1] 
            validOrders += ","
    validOrders = validOrders[:-1] + "]"
    tmpStr = "{\"header\": " + str(HEADERS["BILL"]) +", \"orders\":"
    validOrders = tmpStr + validOrders + "}"
    validOrders = validOrders.replace("\\", "")
    return validOrders

def ReplyResult( conn, success, message = ""):
    jsonStr = "{\"header\": " + str(HEADERS["RESULT"]) + ", \"result\": " + json.dumps(success) + ", \"message\": \"" + str(message) + "\"}"
    return jsonStr

def ExtractHeader( JsonString ):
    obj = json.loads(JsonString)
    return obj["header"]

def SaveOrder( JsonString ):
    obj = json.loads(JsonString)
    header = obj["header"]
    idx = str(JsonString).find( str(header) )
    JsonString = b"{" + JsonString[idx+len(str(header)):]
    fileObj = open( filePath, "a+" )
    idx = len( fileObj.readlines() )
    fileObj.write( str(JsonString)[2:-1] + "\n" )
    fileObj.close()
    return idx
     
def SendOrdersList( JsonString, conn ):
    obj = json.loads(JsonString)
    tableNr = obj["table"]
    orders = ReturnOrderList( tableNr )
    conn.sendall(str.encode(orders))

def RegisterRobot( JsonString, conn ):
    obj = json.loads(JsonString)
    robotName = obj["name"]
    if robots:
        if not conn in robots[:][0]:
            robots.append( (conn, robotName) )
    else:
        robots.append( (conn, robotName) )

def sendMessage(soc, msg):
    sentTotal = 0
    while sentTotal < len(msg):
        sent = soc.send(msg[sentTotal:])
        if sent == 0:
            raise RuntimeError("could not send message (part)")
        sentTotal += sent
    data = soc.recv(1024)
    return data

def StartOrder( JsonString ):
    obj = json.loads( JsonString )
    orders = obj["orders"]
    idxs = []
    for order in orders:
        idxs.append( order["order_id"] )

    fileObj = open( filePath, "r" )
    orders = fileObj.readlines()
    for idx in idxs:
        order = orders[idx]
        if not order.strip("    \n").endswith("FINISHED"):
            orders[idx] = order.strip("   \n") + " FINISHED\n"
            continue
        return False
    fileObj.close()
    fileObj = open( filePath, "w" )
    for order in orders:
        print( order )
        fileObj.write( order )
    fileObj.close()

    robots[0][0].sendall(JsonString)
    return True

def ReturnRobot( JsonString ):
    robots[0][0].sendall(JsonString)

def HandleData( Header, JsonString, conn ):
    print( Header )
    if Header == HEADERS["PLACEORDER"]:
        return SaveOrder( JsonString )        
    elif Header == HEADERS["BILL"]:
        SendOrdersList( JsonString, conn )
    elif Header == HEADERS["ID"]:
        RegisterRobot( JsonString, conn )
    elif Header == HEADERS["STARTORDER"]:
        return StartOrder( JsonString )
    elif Header == HEADERS["RETURN"]:
        ReturnRobot( JsonString )
    elif Header == HEADERS["RESULT"]:
        pass # Nothing for now
    elif Header == HEADERS["GETOPENORDERS"]:
        GetOpenOrders( JsonString, conn )
        #return None
    else:
        print( str(JsonString) + "\n")
        return False
    return True

def threaded_client(connection, addr):
    global ThreadCount
    while True:
        data = connection.recv(2048)
        reply = ""
        if data:
            # handle data here
            status = HandleData( ExtractHeader( data ), data, connection )
            if isinstance( status, int ):
                reply = ReplyResult( connection, True, status )
            elif status is None:
                pass
            else:
                reply = ReplyResult( connection, status)  
            connection.sendall(str.encode(reply))          
        if not data:
            break
    ThreadCount-=1
    connection.close()

while True:
    Client, address = ServerSocket.accept()
    print('Connected to: ' + address[0] + ':' + str(address[1]))
    start_new_thread(threaded_client, (Client, address))
    ThreadCount += 1
    print('Thread Number: ' + str(ThreadCount))
ServerSocket.close()