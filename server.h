#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/times.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>
#include <pthread.h>

#include "utils.h"


// struct server_t {
//     int server_id;
//     int server_ip;
//     int server_port;
//     int server_socket;
//     int primary;
//     int reply_indexes[20];
// }

// struct server {
//     // Unique identifier of the server
//     int id;
//     // Local copy of the bulletin board               
//     log_entry* board;     
//     int is_primary;       // Flag indicating if this server is the primary server
//     int quorum_read = 0;  // Indicator for quorum consistency read/choose option
//     int quorum_write = 0; // Indicator for quorum consistency post/reply option
// };


// server <-> server
void send_message(char* dest_ip, int dest_port, char* message);
void receive_message(int listen_port);
// client <-> server
void handle_request(int socket_fd, struct sockaddr_in client_address);


// // client
// void print_reply(int index,int loop); //recursively print every reply
// void choose(char* title); // match titile then print content
// void read(int number);
// // server common
// int createClientSock(char name);
// void *connection_handler(void *client_socket, char option); //handler to deal with client request
// void post(int timestamp,char title,char content);
// int next_avaiable_index(void* array[]) //find next empty spot in an array
// void reply (int timestamp, char* content, char* title);
// // int broadcast(int* socket_list);

