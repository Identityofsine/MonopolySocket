#include <stdio.h>
#include <vector>
#include "../game/game.h"
#include <sys/socket.h>
#include <netinet/in.h>


#define PORT 8337

namespace MonopolyServer {


    
    int server_fd, new_socket, valread;      // File descriptors and variable for storing bytes read
    const int max_clients = 24;
    const int max_per_game = 4;
    const int max_games = max_clients / max_per_game;
    int clients[max_clients];
    int sd;

    struct sockaddr_in address;              // Structure for storing the address information
    int opt = 1;                             // Option variable used for setting socket options
    int addrlen = sizeof(address);           // Length of the address
    char buffer[1024] = { 0x00 };            // Buffer for storing received data
    fd_set readfds;

    std::vector<Monopoly::MonopolyGame> games = std::vector<Monopoly::MonopolyGame>();
    
    // Function for initializing the socket
    bool startSocket() {

        for (int i = 0; i < max_clients; i++) {
            clients[i] = 0;
        }

        if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
            // If socket creation fails, display error message and return false
            perror("Socket Failed...");
            return false;
        }

        // Set the address family, IP address and port number for the connection
        address.sin_family = AF_INET;
        address.sin_addr.s_addr = htons(INADDR_ANY);
        address.sin_port = htons(PORT);

        // Return true if socket initialization is successful
        return true;
    }

    // Function for starting the connection
    bool startConnection() {
        // Bind the socket to the specified address and port
        if (bind(server_fd, (struct sockaddr*)&address, sizeof(address)) < 0) {
            // If binding fails, display error message and return false
            perror("bind failed");
            return false;
        }

        // Listen for incoming connections
        if (listen(server_fd, 1) < 0) {
            // If listening fails, display error message and return false
            perror("listen");
            return false;
        }

        // Loop continuously to handle incoming connections
        while (1) {
            FD_ZERO(&readfds);
            FD_SET(server_fd, &readfds);

            bool isExit = true; // Boolean flag to keep track of whether the connection has ended
            // Accept a new connection
            int new_socket = accept(server_fd, (struct sockaddr*)&address, (socklen_t*)&addrlen);
            if (new_socket > 0) {
                isExit = false;
            }

            // Receive data from the client and send a response back
            while (new_socket > 0 && !isExit) {

            }

        }
        return true;
    }


}