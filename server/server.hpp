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

    class ServerInstance {
    private:
        static ServerInstance* _instance;
        ServerInstance();
    public:
        static ServerInstance getInstance();
    };

    int server();
}