#include "utils.h"
#define server_num 5
#define time_length 20

// int server_ports[server_num];
// int time_array[time_length];
// int time_index=0;
// int server_socks[5];
// int client_socks[5];
// int log_read = 0;
// struct log_entry logs[10];
// int server_sock; //socket to connect primary
// pthread_mutex_t log_lock = PTHREAD_MUTEX_INITIALIZER;

#define MAX_KEY_LENGTH 256
#define MAX_VALUE_LENGTH 1024
#define MAX_MESSAGE_LENGTH 1280

void receive_message(int listen_port) {
    // create a socket for the receiver
    int receiver_socket = socket(AF_INET, SOCK_DGRAM, 0);
    if (receiver_socket < 0) {
        perror("Error creating socket");
        exit(1);
    }

    // set the listening IP address and port number
    struct sockaddr_in listen_address;
    memset(&listen_address, 0, sizeof(listen_address));
    listen_address.sin_family = AF_INET;
    listen_address.sin_addr.s_addr = INADDR_ANY;
    listen_address.sin_port = htons(listen_port);

    // bind the receiver socket to the listening address and port number
    if (bind(receiver_socket, (struct sockaddr*)&listen_address, sizeof(listen_address)) < 0) {
        perror("Error binding socket");
        exit(1);
    }

    // receive a message from a sender
    char message[MAX_MESSAGE_LENGTH];
    memset(message, 0, MAX_MESSAGE_LENGTH);
    struct sockaddr_in sender_address;
    socklen_t sender_address_size = sizeof(sender_address);
    if (recvfrom(receiver_socket, message, MAX_MESSAGE_LENGTH, 0, (struct sockaddr*)&sender_address, &sender_address_size) < 0) {
        perror("Error receiving message");
        exit(1);
    }

    printf("Received message from %s:%d: %s\n", inet_ntoa(sender_address.sin_addr), ntohs(sender_address.sin_port), message);

    // close the receiver socket
    close(receiver_socket);
}


