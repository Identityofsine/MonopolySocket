#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <vector>
#include "../game/game.h"
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <thread>
namespace MonopolyServer {
    using namespace Monopoly;

    struct PlayerSocket{
        int socket;
        int gameid;
        Player player;
        PlayerSocket(int socket, int gameID){
            this->socket = socket;
            this->gameid = gameID;
            this->player = Player();
        }

        PlayerSocket(){
            this->socket = -1;
            this->gameid = -1;
            this->player = Player();
        }

    };

    class ServerInstance {
    private:
        static ServerInstance* _instance;
        std::vector<MonopolyGame*> gameVector = std::vector<MonopolyGame*>();
        ServerInstance();
    public:
        static ServerInstance getInstance();
        MonopolyGame getGame(int gameID);
        MonopolyGame addGame(MonopolyGame* game);
        MonopolyGame addPlayer(MonopolyGame* game, PlayerSocket* playerSocket);
    };

    int server();
}