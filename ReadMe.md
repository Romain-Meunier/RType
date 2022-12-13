# **R-TYPE [EPITECH PROJECT] [DOCUMENTATION]**

<a href="https://img.shields.io/badge/MADE%20WITH-C%2B%2B-ff69b4" alt="C++">
        <img src="https://img.shields.io/badge/MADE%20WITH-C%2B%2B-ff69b4" /></a>
<a href="https://img.shields.io/badge/MADE%20WITH-CONAN-blueviolet" alt="Conan">
        <img src="https://img.shields.io/badge/MADE%20WITH-CONAN-blueviolet" /></a>
<a href="https://img.shields.io/badge/MADE%20WITH-CMAKE-red" alt="Cmake">
        <img src="https://img.shields.io/badge/MADE%20WITH-CMAKE-red" /></a>
<a href="https://img.shields.io/badge/MADE%20WITH-SFML-brightgreen" alt="SFML">
        <img src="https://img.shields.io/badge/MADE%20WITH-SFML-brightgreen" /></a>

![image](https://media.discordapp.net/attachments/820713881961627678/1039113134805364796/Capture_decran_2022-11-07_a_10.04.00_AM.png)
> This project is an advanced C++ project. Our R-Type will showcase network video game development. It integrates a multi-threaded server and a graphical client using a reusable game engine of our own design. The goal of this project is to create a network game for 1 to 4 players using a compulsory Server/Client architecture. There must be no local communication between 2 players.

[R-Type](https://fr.wikipedia.org/wiki/R-Type) is an Epitech project referring to the video games series "R-Type".

So the objective of this project is to make a side-scrolling [Shoot them up](https://fr.wikipedia.org/wiki/Shoot_%27em_up) game.

That means that the player plays a character who must detroy a large number of enemies using projectiles, as the levels progress, while dodging enemy projectiles to stay alive.

---

## **Subject** :

[B-CPP-500_rtype.pdf](https://github.com/EpitechPromo2025/B-CPP-500-MAR-5-1-rtype-claire.cival/blob/master/docs/B-CPP-500_rtype.pdf)

# **Prerequisites**

The following are the necessary prerequisites on the different OS before starting the project:

--- 

## **Linux / Ubuntu:**

#### **Conan :**

```
sudo apt-get install pip
sudo ./scripts/my_conan.sh
conan profile update settings.compiler.libcxx=libstdc++11 default
```

#### **Only for Ubuntu :**
```
sudo apt libudev-dev
```

> We install the pip command and then we install conan using a script and finally designate the good compiler c++ for conan.

#### **CMake :**

```
sudo apt update
sudo apt install cmake
cmake --version
```

> Looking for any updates to install CMake.
---
## **Fedora:**

#### **Conan :**

```
sudo dnf install pip
sudo ./scripts/my_conan.sh
conan profile update settings.compiler.libcxx=libstdc++11 default
sudo apt install systemd-devel
```

> We install the pip command and then we install conan using a script and finally designate the good compiler c++ for conan.

#### **CMake :**

```
sudo dnf update
sudo dnf install cmake
cmake --version
```

> Looking for any updates to install CMake.

---

## **Windows:**

### **Conan :**

```
sudo yum install pip
sudo ./scripts/my_conan.sh
conan profile update settings.compiler.libcxx=libstdc++11 default
```

> We install the pip command and then we install conan using a script and finally designate the good compiler c++ for conan.

### **CMake :**

> You can find all versions of CMake here : https://cmake.org/download/.

> Our version of CMake for this project : "cmake-3.24.2.zip"

### **Visual Studio Tools:**

> In order to use CMake we need to install Visual Studio Tools, you can download the Windows version here : https://visualstudio.microsoft.com/fr/downloads/

---
## **Mac:**

#### **Conan :**

```
sudo brew install ./scripts/my_conan.sh
conan profile update settings.compiler.libcxx=libc++
conan profile update settings.compiler.version=14
```

### **CMake :**

```
sudo brew update
sudo brew install cmake
cmake --version
```

---
# **Run Project:**

## **Windows :**

```
mkdir build
cd build
conan install ../scripts/conanfile.txt
cmake ..
cmake --build . --config=release
.\bin\r-type_server.exe [PORT]
.\bin\r-type_client.exe [IP] [PORT]
```

## **Ubuntu / Linux / Fedora :**

```
mkdir build
cd build
conan install ../scripts/conanfile.txt
cmake ..
cmake --build .
./bin/rtype_server [PORT]
./bin/rtype_client [IP] [PORT]
```

## **Mac:**

```
mkdir build
cd build
conan install ../scripts/conanfile.txt
cmake ..
cmake --build . --config release
./bin/rtype_server [PORT]
./bin/rtype_client [IP] [PORT]
```


---
## **Constraints:**

- **Cross-platform :** Conan & CMake on Linux/Fedora/Ubuntu and Windows at least
- **Build :** CMake [cf_CMake](https://cmake.org)
- **Dependencies :** We have to use one of the following depenencies -> [Git submodules](https://git-scm.com/book/en/v2/Git-Tools-Submodules), CMake [Fetch_Package](https://cmake.org/cmake/help/latest/module/FetchContent.html)/[External_Project](https://cmake.org/cmake/help/latest/module/ExternalProject.html) functionalities **or** a dedicated package manager -> [Conan](https://conan.io), [Vcpkg](https://vcpkg.io/en/index.html), etc.
- **Library :** SFML [cf_SFML](https://www.sfml-dev.org)

---
### **Gameplay:**

#### **Player commands :**
|**Input**|**Direction**|
|---:|:---|
***Arrow Up*** | Top
***Arrow Down*** | Down
***Arrow Left*** | Left
***Arrow Right*** | Right
***Space*** | Throw projectiles
***X*** | Change Weapon

---

## **Norme Commit:**

In order to keep our project organized, we want to follow some rules for commits to better understand the changes made.
Commit Explanations:
Every commit have to be in english
Each commit have to start with a square bracket enclosed to specify the reason of the commit.

### **Explanations :**

- **[ADD] :** If you add files, features and so on
- **[FIX] :** If you had worked and rectified a bug or any other default that you corrected
- **[DEL] :** if you removed files, features, assets and so on
- **[REFACTO] :** The source code is reworked, modified and supplemented
- **[DONE] :** Functional file, no mandatory changement require

> Every commit should be followed by some words to explain made changements.
Exemple : "[ADD] Fight system"

---

## **Quick Start Step**

> This part shows the location of the different entities present in our project so that it is much easier for everyone to make changes and thus go straight to the point.

If you want change the **Game Engine network :** `game_engine/src/Network/Network.cpp`

> And you can find here the documentation of our [Network protocol](https://github.com/EpitechPromo2025/B-CPP-500-MAR-5-1-rtype-claire.cival/blob/master/docs/Network_protocol.md).

- **Path Menu files :** `src/client/`
- **Bullet gestion :** `src/game/Bullet.cpp`
- **Mob/Kamikaze gestion :** 1. `src/game/Kamikaze.cpp` / 2. `src/game/Mob.cpp`

> Check our documentation about [mobs and ennemies](https://github.com/EpitechPromo2025/B-CPP-500-MAR-5-1-rtype-claire.cival/blob/master/docs/Ennemi_creation.md).
- **Player gestion :** `src/game/Player.cpp`
- **User Interface gestion :** `src/game/UI.cpp`
- **Deserializer :** `src/other/Deserializer.cpp`, you can also find the Serializer here -> `src/server/Serializer.cpp`

> If you want learn more about our Serialization, check the [Serializer documentation](https://github.com/EpitechPromo2025/B-CPP-500-MAR-5-1-rtype-claire.cival/blob/master/docs/Serialization.md) !

- **Gestion of room/lobby :** 1. `src/server/Lobby_session.cpp` / 2. `src/server/Room.cpp` / 3. `src/server/Logic.cpp`
- **Entity creation and gestion :** 1. `game_engine/src/create_entity.cpp` / 2. `game_engine/src/Entity.cpp`
- **Components directory :** `game_engine/src/Component`
- **Events system :** `game_engine/src/System/`
- **Main Game Engine :** `game_engine/src/Game_engine.cpp`
- **All includes of Game Engine :** `game_engine/includes/`

> here, more informations about Game Engine : [Game_Engine_Documentation](https://github.com/EpitechPromo2025/B-CPP-500-MAR-5-1-rtype-claire.cival/blob/master/docs/Game_Engine.md)

- **All includes of R-Type** (client, server, game, ...) : `includes/`

---

## **License used :**

GPL license : General Public license

This license makes our code accessible and reusable by as many people as possible. They benefit from a strong copyleft.
Several versions are available: GPL 2, GPL 3, the latest version being the most complete, because it solves the problem of tivoization (Creation of a system that includes free software).

---

### **Project realised by :**

- **[@Claire C.](https://github.com/claire-cival)**
- **[@Arthur V.](https://github.com/Aurathen)**
- **[@Clement D.](https://github.com/Clement23Dubois)**
- **[@Mateo M.](https://github.com/Drazib-Potion)**
- **[@Romain M.](https://github.com/Romain-Meunier)**