#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <unistd.h>

#define MAX_KEY_LENGTH 256
#define MAX_VALUE_LENGTH 1024
#define MAX_MESSAGE_LENGTH 1280

void send_request(char* server_ip, int server_port, char* message) {
    // create a socket for the client
    int client_socket = socket(AF_INET, SOCK_DGRAM, 0);
    if (client_socket < 0) {
        perror("Error creating socket");
        exit(1);
    }

    // set the IP address and port number for the server
    struct sockaddr_in server_address;
    memset(&server_address, 0, sizeof(server_address));
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = inet_addr(server_ip);
    server_address.sin_port = htons(server_port);

    // send a message to the server
    socklen_t server_address_size = sizeof(server_address);
    if (sendto(client_socket, message, strlen(message), 0, (struct sockaddr*)&server_address, server_address_size) < 0) {
        perror("Error sending message to server");
        exit(1);
    }

    // receive a response from the server
    char response[MAX_MESSAGE_LENGTH];
    memset(response, 0, MAX_MESSAGE_LENGTH);
    if (recvfrom(client_socket, response, MAX_MESSAGE_LENGTH, 0, (struct sockaddr*)&server_address, &server_address_size) < 0) {
        perror("Error receiving message from server");
        exit(1);
    }

    printf("Server response: %s\n", response);

    // close the client socket
    close(client_socket);
}

int main(int argc, char** argv) { // ip port key value
    // read the server IP address and port number from the command-line arguments
    char* server_ip = argv[1];
    int server_port = atoi(argv[2]);

    // read the key and value from the command-line arguments
    char* key = argv[3];
    char* value = argv[4];

    // send a PUT request to the specified server
    char message[MAX_MESSAGE_LENGTH];
    memset(message, 0, MAX_MESSAGE_LENGTH);
    snprintf(message, MAX_MESSAGE_LENGTH-1, "%s:%s", key, value);
    send_request(server_ip, server_port, message);

    return 0;
}
