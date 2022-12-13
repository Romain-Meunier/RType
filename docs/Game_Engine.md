# **[R-TYPE] [EPITECH PROJECT][DOCUMENTATION]**

## **Game Engine**

The Game Engine is based on the ECS (Entity Component System) technique, which is an architecture regularly used in video game development.
Follow [this link](https://en.wikipedia.org/wiki/ECS) for more information.

The game engine is divided into three parts:

---

## **I - System :**

We have created systems that use our entities to make the game work.

We have four systems:
- **I_Rendersystem :** this is the system that allows the display of all entities

- **I_Soundsystem :** is the system that allows you to play music and sound effects.

- **I_Eventsystem :** it is the system that manages the various keyboard inputs as well as the mouse.

- **Network:** it is a different system from the others since it must be changed according to the game, it is not part of the game engine, it allows the connection to a server.

Each interface (`I_Rendersystem`, `I_Soundsystem`, `I_Eventsystem`) must be overloaded to code your own system usage, otherwise you can use the supplied systems that work with the SFML library.

---

## **II - Entity**

Entities are all elements of the game, players, monsters, text etc..
you need them created throughout your game using an entity list (`std:vector<Entity *>`) that must be provided for the game engine builder, and then you can add them to the list at your will.

To create entities we provide you with a file c++ `create_entity.cpp"  which are functions that will create a specific Entity with the components it needs.
You are free to use the same format to create your own create entity functions.

---

## **III - Component**

Components are classes, grouping together information and methods for modifying this information.

Entities are composed of components, they may contain 
as much as desired.

All components must be built with a configuration structure that is sent in `void *`.
In config_compo.cpp we have all the configuration structures to build each component.