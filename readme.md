# Monopoly Socket Server

### Current State
- The game currently runs, and a lot of logic has been implemented:
- - Buying Property
- - Paying Rent to owned properties
- - Chance Cards (and their associated logic)
- - Game Flow Control
- - Engine Ticks
- A few other things need to get sorted out such as implementing a ignoreChanceCard function(where the script keeps track of what cards were pulled from the deck), more efficient game flow control such as building houses and trading.

### Theoretical Issues
Some of the issues we may face is that of multiple game instances running under one socket server. I believe that deadlock may be a problem if we don't manage locks properly. But at the same time if monopoly games run at either too slow of a tick or too fast, we may face a deadlock in sending requests and we'll get lag from the server; this isn't so important as a game of Monopoly does not need to be instantaneous but it could be a problem if a lot of games are running at once. 

I may look into options of a separate program that launches this program every time a game wants to be started (or if the program is running at maximum instances).

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
 

[^1]: [Lua 5.4.4](https://www.lua.org/ "https://www.lua.org/")

[^2]: [Nlohmann's JSON Repository](https://github.com/nlohmann/json "https://github.com/nlohmann/json")

[^3]: [Selene Repository](https://github.com/jeremyong/Selene "https://github.com/jeremyong/Selene")
