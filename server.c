#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <unistd.h>

#include "server.h"

#define MAX_KEY_LENGTH 256
#define MAX_VALUE_LENGTH 1024
#define MAX_MESSAGE_LENGTH 1280

log_entry database[1000];
int num_entries = 0;
char* option = "sequential consistency";
pthread_mutex_t log_lock = PTHREAD_MUTEX_INITIALIZER;
int primary_id = 0;
int server_port[] = {5000,5001,5002,5003,5004};

void send_message(char* dest_ip, int dest_port, char* message) {
    // create a socket for the sender
    int sender_socket = socket(AF_INET, SOCK_DGRAM, 0);
    if (sender_socket < 0) {
        perror("Error creating socket");
        exit(1);
    }

    // set the destination IP address and port number
    struct sockaddr_in dest_address;
    memset(&dest_address, 0, sizeof(dest_address));
    dest_address.sin_family = AF_INET;
    dest_address.sin_addr.s_addr = inet_addr(dest_ip);
    dest_address.sin_port = htons(dest_port);

    // send the message to the destination
    socklen_t dest_address_size = sizeof(dest_address);
    if (sendto(sender_socket, message, strlen(message), 0, (struct sockaddr*)&dest_address, dest_address_size) < 0) {
        perror("Error sending message");
        exit(1);
    }

    // close the sender socket
    close(sender_socket);
}

void handle_request(int socket_fd, struct sockaddr_in client_address) {
    // receive a message from the client
    char message[MAX_MESSAGE_LENGTH];
    memset(message, 0, MAX_MESSAGE_LENGTH);
    socklen_t client_address_size = sizeof(client_address);
    if (recvfrom(socket_fd, message, MAX_MESSAGE_LENGTH, 0, (struct sockaddr*)&client_address, &client_address_size) < 0) {
        perror("Error receiving message from client");
        exit(1);
    }
    message[MAX_MESSAGE_LENGTH-1] = '\0';
    // parse the message into a key and value： Segfault
    // char key[MAX_KEY_LENGTH];
    // char value[MAX_VALUE_LENGTH];
    // memset(key, 0, MAX_KEY_LENGTH);
    // memset(value, 0, MAX_VALUE_LENGTH);
    // if (sscanf(message, "%[^:]:%[^:]", key, value) != 2) {
    //     exit(1);
    // }

    // TODO: handling post, reply, read and choose

    // TODO: Update the string according to the strategy
    // // if (strcmp(option, "sequential consistency") == 0) {
    // //     sequential_local_update(&log_entry);
    // //     sequential_propagate(primary);
    // // }

    // // store the data in the database
    // strncpy(database[num_entries].title, key, MAX_KEY_LENGTH-1);
    // strncpy(database[num_entries].content, value, MAX_VALUE_LENGTH-1);
    // num_entries++;
    

    // send a response back to the client
    char response[MAX_MESSAGE_LENGTH];
    memset(response, 0, MAX_MESSAGE_LENGTH);
    strncpy(response, "OK", MAX_MESSAGE_LENGTH-1);
    if (sendto(socket_fd, response, strlen(response), 0, (struct sockaddr*)&client_address, client_address_size) < 0) {
        perror("Error sending message to client");
        exit(1);
    }
}

int main(int argc, char** argv) { // argv[1]: server_id
    // create a socket for the server
    int server_socket = socket(AF_INET, SOCK_DGRAM, 0);
    if (server_socket < 0) {
        perror("Error creating socket");
        exit(1);
    }

    // set the IP address and port number
    struct sockaddr_in server_address;
    memset(&server_address, 0, sizeof(server_address));
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = INADDR_ANY;

    // bind the socket to a port number between 5000 and 5004
    int server_port = 5000 + atoi(argv[1]);
    server_address.sin_port = htons(server_port);
    if (bind(server_socket, (struct sockaddr*)&server_address, sizeof(server_address)) < 0) {
        perror("Error binding socket");
        exit(1);
    }

    printf("Server %d is listening ...\n", atoi(argv[1]));

    while (1) {
        // receive a datagram from a client
        struct sockaddr_in client_address;
        handle_request(server_socket, client_address);
        for (int i = 0; i < num_entries; i ++) {
            printf("%s\n", database[i].title);
        }

        // receive a datagram from other server
        for (int i = 0; i < num_entries; i ++){
            if (i == atoi(argv[1])) {
                continue;
            }
            receive_message(5000 + atoi(argv[1]));
        }
    }

    // close the server socket
    close(server_socket);

    return 0;
}