#ifndef __UTILS_H__
#define __UTILS_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>
#include <pthread.h>

#define PAGE_ENTRIES 10
#define INITIAL_PAGES 3
#define INITAL_CLIENTS 4
#define LISTEN_BACK 10
#define MAX_MSG_LEN 256   // Maximum length of a message
#define MAX_BOARD_LEN 100 // Maximum number of messages on the bulletin board

// define the server struct to hold information about each server
typedef struct {
    char* ip_address;
    int port_number;
    int socket_fd;
    pthread_t thread_id;
} server_t;

// database struct to hold the entry
typedef struct log_entry {
    int timestamp;
    int type;              //1 for article,0 for reply
    char* title;
    char* content;
    int reply_indexes[20];
} log_entry;

void receive_message(int listen_port);

#endif /* __COMMON_H__ */