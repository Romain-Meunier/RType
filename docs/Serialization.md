# **R-TYPE [EPITECH PROJECT] [DOCUMENTATION]**


# **Serialization** 

##  **1 - Type of snapshot** 

### **We send 2 type of snapshot :**

 - Game type
 - Info Type

#### **Game type will have this look:** 

```
GAME$PLAYER/1:1845.67|!1|\n 

KAMIKAZE/1:123.321|!2|\n 

B_BLASTER_ALLY/2:1*1456.678|2*45.98|\n 

B_ROCKET_MOB/1:1*128.1|\n 
```

#### **Where we have in order:**  

```
Snap_type$entity_type/id_of_entity:coord_x.coord_y|!dead(2)/alive(1)|\n 
```

**Entity starting with “B_” are the bullet lists. They have this syntax:** 

```
Bullet_vector_type/nb_of_bullet:coord_x.coord_y|coord_x.coord_y| . . . |\n 
```
 

#### **While Info type will look like this:** 

```
INFO$2\n 

Player:1/3|\n 

KAMIKAZE:2/2|\n 

Score:1800|\n 
``` 

#### **Where we have in order:** 

```
Snap_type$nb_of_entity\n 

entity_type:id_of_entity/life_left|\n 

...

Score:score_nbr|\n 
``` 

> “Game” type snapshot is sent while the game is running to update position of all the entity client side, and “Info” type snapshot will also be sent while the game is running and it will specifically be for updating the satate of entities (dead or alive). 

---

## **2 - Serializer and compressor protocole** 

> Those 2 types of snapshot are Serialized and Compressed befor being sent. We serialize those snapshot using this protocole: 

### **Each entity is 7 bytes:** 


- Entity type: 1 byte 

- Entity id : 1 byte 

- Entity coord x : 2 bytes

- Entity coord y : 2 bytes

- Entity state : 1 byte 
---

### **Each Bullet vector is 2 + (4 * nbr_of_bullet) bytes:** 

- Bullet_type : 1 byte 

- Number of bullet: 1 byte 

- Bullet coord x: 2 byte 

- Bullet coord y: 2 byte 

---

**Since we encode the type in 1 byte for both bullet vector and entity we have 256 type possible, Exemple below:**

 

    {"PLAYER", 1}, 

    {"KAMIKAZE", 2}, 

    {"TIEHunter", 3}, 

    {"SCORE", 4}, 

    {"B_BLASTER_ALLY", 5}, 

    {"B_ROCKET_MOB", 6}, 


> After serializing this data with this protocole we compress it using the LZ4 algorythm (using the library “LZ4”) 
