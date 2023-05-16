#include "server.hpp"

#define PORT 2337
#define MAX_PLAYERS 24
namespace MonopolyServer {




void sendMessageToPlayerGroup(PlayerSocket players[], int gameID, const char* message){
    for(int i = 0; i < MAX_PLAYERS; i++) {
        int socket_connection = players[i].gameid;
        if(players[i].gameid == gameID){
            send(socket_connection, message, strlen(message), 0);
            break;
        }
    }
}

int server(){
    int sockfd, ret;
    struct sockaddr_in serverAddr;

    int newSocket;
    struct sockaddr_in newAddr;

    const int config_max_player = MAX_PLAYERS;
    PlayerSocket clientSocket[config_max_player];
    int curClient = 0;

    char buffer[1024];
    pid_t childpid;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd < 0) {
        printf("[SERVER]Error establishing a socket...\n");
        exit(1);
    }
    printf("[SERVER]Socket Created...\n");

    memset(&serverAddr, '\0', sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(PORT);
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    ret = bind(sockfd, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
    if(ret < 0){
        printf("[SERVER]Error binding to Socket...\n");
        exit(1);
    }
    
    if(listen(sockfd, 10) == 0) {
        printf("[SERVER]Listening...\n");

    } else{
        printf("[SERVER]Error binding to Socket...\n");
        exit(1);
    }

    while(1){
        socklen_t len = sizeof(newAddr);
        newSocket = accept(sockfd, (struct sockaddr*)&newAddr, &len);
        if(newSocket < 0){
            printf("[SERVER]Connection Failed");
            continue;
        }

        printf("[SERVER]Connection Accepted from %s:%d.\n", inet_ntoa(newAddr.sin_addr), newAddr.sin_port);
        
        clientSocket[curClient++].socket = newSocket;
        clientSocket[curClient++].gameid = 0; //unassigned;
        const char* welcomeMessage = "Joining GAME!\n";
        send(newSocket, welcomeMessage, strlen(welcomeMessage), 0);

        std::thread recv_thread([newSocket, clientSocket, curClient]() {
            char local_buffer[1024];
            int bytesRead;
            bool clientDisconnected = false;
            while(!clientDisconnected && (bytesRead = recv(newSocket, local_buffer, sizeof(local_buffer), 0)) > 0) {
                local_buffer[bytesRead] = '\0';
                printf("[SERVER]Message Recieved from a client: %s", local_buffer);

                if(strcmp(local_buffer, ":exit") == 0) {
                    clientDisconnected = true;
                } else {
                    //?? LOGIC
                }

            }
            
            printf("[SERVER]A Client disconnected\n");
            
        });

        recv_thread.detach();

    }
    return close(newSocket);

}


}