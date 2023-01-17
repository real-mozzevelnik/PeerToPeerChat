#ifndef Client_h
#define Client_h
#include "../Configs.h"

// struct to save client name, address and activity
struct Client
{
    int active;
    char name[MAX_NAME_LENGTH];
    struct sockaddr_in address;
};

// extern struct to use it in tne main file
extern struct Client clients[MAX_CLIENTS];

// send packet to request connection and wait to get accept answer
void connect_to_client(int sock, struct sockaddr_in *addr, char *name);

// add client in array of clients
void add_client(struct sockaddr_in *addr, char *name);

// get pointer to client from clients array
struct Client * get_client(struct sockaddr_in *addr);

// check if client in clients array
int client_exists(struct sockaddr_in *addr);

// send packet to all the clients
void send_to_every_one(int sock, char *buffer, int buffer_size);

// delete client by changing his active to 0
void delete_client(struct Client *client);

#endif
