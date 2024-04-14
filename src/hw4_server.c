#include "hw4.h"

int main() {
    ChessGame game;
    int listenfd, connfd;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);

    // Create socket
    if ((listenfd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // Set options to reuse the IP address and IP port if either is already in use
    if (setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt))) {
        perror("setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt))");
        return -1;
    }
    if (setsockopt(listenfd, SOL_SOCKET, SO_REUSEPORT, &opt, sizeof(opt))) {
        perror("setsockopt(server_fd, SOL_SOCKET, SO_REUSEPORT, &opt, sizeof(opt))");
        return -1;
    }

    // Bind socket to port
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);
    if (bind(listenfd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    // Listen for incoming connections
    if (listen(listenfd, 1) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    INFO("Server listening on port %d", PORT);
    // Accept incoming connection
    if ((connfd = accept(listenfd, (struct sockaddr *)&address, (socklen_t *)&addrlen)) < 0) {
        perror("accept");
        exit(EXIT_FAILURE);
    }

    INFO("Server accepted connection");

    while (1) {
        char buffer[BUFFER_SIZE];
        int nbytes = read(connfd, buffer, BUFFER_SIZE);
        if(nbytes <= 0) {
            perror("[Server] read() failed.");
            exit(EXIT_FAILURE);
        }

        if(receive_command(&game, buffer, connfd, WHITE_PLAYER) == COMMAND_FORFEIT) {
            printf("terminating server\n");
            break;
        }

        int res;

        do {
            printf("[Server] Enter a command: ");
            fgets(buffer, BUFFER_SIZE, stdin);
            buffer[strlen(buffer)-1] = '\0'; //remove the \n char at the end;
            res = send_command(&game, buffer, connfd, WHITE_PLAYER);
        } while(res == COMMAND_ERROR || res == COMMAND_UNKNOWN);

        if(res == COMMAND_FORFEIT) {
            printf("terminating server\n");
            break;
        }
    }

    close(connfd);
    close(listenfd);
    return 0;
}
