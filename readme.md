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
As of now, I have changed this project to work with CMake so it is more user friendly to build for all platforms. The process for building is very simple, and in the future files will change but the build process will be the same. (Mostly).


#### Build Usage
First clone this repository, then cd into it.
```bash
#Make a new directory, build.
mkdir build
#cd into it
cd build
#then run cmake ..
cmake ..
#after completion (if all goes well) run make
make

#when the file is built you will see "Monopoly" in your file browser; to run this type:
./Monopoly
```

## Libraries/Dependencies Used

- Lua 5.4.4 [^1]
- Nlohmann's JSON library [^2]
- Selene [^3]
 

[^1]: [Lua 5.4.4](URL "https://www.lua.org/")

[^2]: [Nlohmann's JSON Repository](URL "https://github.com/nlohmann/json")

[^3]: [Selene Repository](URL "https://github.com/jeremyong/Selene")
