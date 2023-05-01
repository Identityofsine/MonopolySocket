# Monopoly Socket Server

### Current State
- The game doesn't even work; no game instance exists yet and the only thing implemented is gameObjects like Player, Buyable, Landable, and a generic MonopolyObject base. 
- In a soon to be commit, a game instance will be created and the game will work (somehow).

### Goals 
- This project should be able to handle multiple games at once with a socket connection to multiple players. Players will be separated into games under one socket connection. This shouldn't be too hard as long as the right packets are sent to the client for each game instance.
- In its early stages (without a socket connection), the game should be able to be played in the console, each player will be able to dice roll, land on a property and be able to purchase or pay up to the owner.

### Obstacles 
- Logic. Game Logic will have to be carefully implemented to ensure an authentic Monopoly experience. Such things on my mind is landing on a property and paying the owner (depending on if the property has homes or the owner has all the properties in that specific color)

### Building
There isn't a build file ready yet, and it won't be until the program can actually play Monopoly. 

However, if you want to build this program please use clang or g++ in a linux environment. (This will work in Windows in Visual Studio -- just make sure you are building with WSL). This program must be built with C++11 as well.

#### Example Build Program
```bash
#This is very subject to change, files will be added and deleted...
g++ allmainfiles.cpp... -std=c+11 -o build.out

#As of 5/1/23 
--------------------------------
g++ main.cpp objects/player.cpp objects/gameobject.cpp -std=c+11 -o build.out
```