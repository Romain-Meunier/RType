# **R-TYPE [EPITECH PROJECT] [DOCUMENTATION]**

# **Network Protocol**

## **I – Network**

In this project, the network is divided into two parts, the UDP and the TCP as we can see in the following diagram that represents the architecture of our network structure:

![image](https://cdn.discordapp.com/attachments/1029370505565843466/1039921918159114250/image.png)


### **A - TCP :**

The TCP is used here as a means of exchange of important information essential to the proper functioning of the project.
We have chosen to transfer part of the fields of one of our structures according to needs.

---

### **B - UDP :**

The UDP, meanwhile, allows a simpler and faster exchange much less safe about packet loss. It intervenes in situations where information is not vital and can be provided later.

Exchanges via this channel during the game phase will take place at the rate of **20 exchanges/s** from the server to the client.
The client will send a message to each necessary information.

---

## **II – Network protocol**

To fully understand the protocol, we need to look at the command enum, which has all of our types of data transactions.

### **A - TCP :**

#### **1 - CLIENT :**

- `DISCONNECT :` The command is sent in TCP by the client to announce its disconnection
- `JOIN_ROOM :` The order is sent to announce that the customer wishes to join the room "NAME" which will be filled in the MSG field of the structure

- `CREATE_ROOM :` The order is sent to announce that the customer wants to create a room under the name “NAME”. This name will be completed in the MSG field of the requestMessage structure

---

### **2 - SERVER :**

- `SERVER_GIVE_ROOM_PORT :` The server responds with this command which transmits the room port to the client when it creates/joins the room.

---

### **B - UDP :**

- `CLIENT_GIVE_IP :` The Client will send a message in udp to the server so that it can recover its IP address

- `GIVE_NBR_TO_CLI :` The Server will inform the client of its identidy with an id transmitted as a parameter.

- `GAME_INIT :` The Server will send a snapshot of the initial positions of the entities present.

- `GAME_UPDATE :` The Server will send a snapshot of the updated positions of each entity present.

- `PLAYER_INPUT :` This type of command will be sent when the client wishes to transmit an action from its client to the server.
---
## **III – Implementation details**

![image](https://cdn.discordapp.com/attachments/1029370505565843466/1039925958129491968/image.png)

1. Connection & room choice (create or join)
2. Server response positive and transfers to one of the Rooms
3. Discussions with clients and Room + Update

---

## **IV – Type of sending data**

### **A - TCP :**

![image](https://cdn.discordapp.com/attachments/1029370505565843466/1039927671410393189/image.png)

The requestMessage is the packet that will pass between the server and the client, in both directions.

The CMD will contain the different types of commands to inform the server and the client of the state in which the other is and to process the msg that will follow in the right way.

> (see protocol section to see the different types of messages)

**The package:** First, it contains the size of the following message.
The message will have several functions such as having the name of the ROOM it wants to join, etc.
Finally, it has the port and addr fields that will be useful when choosing the ROOM so that it can recognize the client.

---

### **B - UDP :**

![image](https://cdn.discordapp.com/attachments/1029370505565843466/1039928563907952802/image.png)

The GameMessage is the structure that passes between the server and the client. (On both sides)

It contains a packet and two fields that are only useful for Serialization/Deserialization

---

### **C - Containt of UDP package:**

The CMD, like that of the TCP, it will inform the server and the client of the state in which the other is located as well as to process the msg that will follow in the right way.

The msg contains the serialized SNAPSHOT. You will therefore have to give the package to the deserializer to recover the information. (Only for the game)
In the Room messages in msg will be non-serialized.

---

## **V – Sending order:**

We’ll have to connect first.

When this is done, the cmd type `CREATE_ROOM` must be sent in TCP and the message contains the room name, or `JOIN_ROOM` with also the room name.

If the action was not successful, the server will return a TCP packet with the command `ACCESS_DENIED`. Otherwise the server will send the CMD `SERVER_GIVE_ROOM_PORT`. The latter will contain the ROOM IP port and address.

Following this, the Customer must send a CMD `CLIENT_GIVE_IP' in UDP so that the ROOM can know who you are.

Then the ROOM will send you your player ID with the CMD `ROOM_PLAYER_` and the number of people in the ROOM with the CMD `GIVE_NBR_TO_CLI`.

To launch the game, you must send the CMD `LUNCH_GAME`.

The ROOM will send you the GAME INIT CMD to initialize the players and their positions.
The ROOM will then send the snapshot with the CMD `GAME_UPDATE`.

When you want to send the INPUTS, you must put the CMD `INPUT_` and the input type (`UP`, `DOWN`, `RIGHT`, `LEFT`, `SPACE`) in the update message.

---
## **VI – Vocabulary**

- **UDP :** `User Datagram Protocol`
- **TCP :**  TCP is a network protocol that allows two hosts to connect and exchange data
- **Packets:** information passing between clients and server, and vice versa
- **Snapshot :** Message containing all the information useful for the proper functioning of the game