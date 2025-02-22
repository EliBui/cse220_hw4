#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include "hw4.h"

#define PORT 8080
#define BUFFER_SIZE 1024

int main() {
    ChessGame game;
    int connfd = 0;
    struct sockaddr_in serv_addr;

    // Connect to the server
    if ((connfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
        perror("Invalid address/ Address not supported");
        exit(EXIT_FAILURE);
    }

    if (connect(connfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        perror("connect failed");
        exit(EXIT_FAILURE);
    }

    initialize_game(&game);
    display_chessboard(&game);

    while (1) {
        char buffer[BUFFER_SIZE];
        memset(buffer, '\0', BUFFER_SIZE);
        int res;

        do {
            printf("[Client] Enter a command: ");
            fgets(buffer, BUFFER_SIZE, stdin);
            buffer[strlen(buffer)-1] = '\0'; //remove the \n char at the end;
            // printf("sending from client to server: %s\n", buffer);
            res = send_command(&game, buffer, connfd, true);
        } while(res == COMMAND_ERROR || res == COMMAND_UNKNOWN || res == COMMAND_SAVE);

        if(res == COMMAND_FORFEIT) {
            // printf("terminating client\n");
            break;
        }

        memset(buffer, '\0', BUFFER_SIZE);

        int nbytes = read(connfd, buffer, BUFFER_SIZE);
        if(nbytes <= 0) {
            perror("[Server] read() failed.");
            exit(EXIT_FAILURE);
        }

        // printf("client receiving from server: %s\n", buffer);

        if(receive_command(&game, buffer, connfd, true) == COMMAND_FORFEIT) {
            // printf("terminating client\n");
            break;
        }
        memset(buffer, '\0', BUFFER_SIZE);
    }

    // Please ensure that the following lines of code execute just before your program terminates.
    // If necessary, copy and paste it to other parts of your code where you terminate your program.
    FILE *temp = fopen("./fen.txt", "w");
    char fen[200];
    chessboard_to_fen(fen, &game);
    fprintf(temp, "%s", fen);
    fclose(temp);
    close(connfd);
    return 0;
}
