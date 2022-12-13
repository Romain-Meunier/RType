# **[R-TYPE] [EPITECH PROJECT][DOCUMENTATION]**

## **How to create enemy**

To do this you need to create a text file with the information of the enemies. You need information such as the sprite of the enemy, the initialization of the coordinates and its behaviour. 
For this you have to respect a specific nomenclature.
You must specify the names of the categories (Sprite, Init, Behaviour) 
For sprites, simply write the name of the sprite and its format (.png, .jpeg, ...)

❗ **You must specify the names of the categories (Sprite, Init, Behaviour) 
For sprites, simply write the name of the sprite and its format (.png, .jpeg...)** ❗ 

- **Example :**

![image](https://cdn.discordapp.com/attachments/1029370505565843466/1039938563501985912/image.png)
![image](https://cdn.discordapp.com/attachments/1029370505565843466/1039938591964528730/image.png)

> The init are the coordinates of the appearance of your enemy, it is not obligatory to put the category but it can contain nothing. If you want to define its coordinates then you have to put the coordinates X.Y, separated by a point and not by a space.

- **Example :**

![image](https://cdn.discordapp.com/attachments/1029370505565843466/1039939051140161556/image.png)
![image](https://cdn.discordapp.com/attachments/1029370505565843466/1039939075035123753/image.png)

> As for the behaviour of your enemy you can put line by line what you want your enemy to do. If you put two pieces of information on the same line they will be done at the same time. For the nomenclature you indicate the letter of the direction (U -> up, L -> left, R -> right, D -> down, S - >shot, SO ->shot directionnal) and with that you have to indicate either the number of moves for the movement, and for the shot you can indicate the angle in which your bullet will go.


![image](https://cdn.discordapp.com/attachments/1029370505565843466/1040299454349180990/Capture_decran_2022-11-10_a_5.18.31_PM.png)

![image](https://cdn.discordapp.com/attachments/1029370505565843466/1040298573729894462/Capture_decran_2022-11-10_a_5.15.04_PM.png)

### **Example of a mob file :**

![image](https://cdn.discordapp.com/attachments/1029370505565843466/1039939552204304495/image.png)

**Explications of mob file just above :** 

1. category Sprite
2. retrieved the name of the sprite
3. Category init
4. init on X = 0, Y = 0
5. Category Comprotement
6. move on diagonal donw rigth -> 100
7. pulls a bullet 45° upwards
8. move on diagonal donw rigth -> 50
9. pulls a bullet upwards
10. move on diagonal up left -> 50
11. pulls a bullet all right
12. move on diagonal up left -> 100