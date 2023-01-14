#include "Packet.h"
#include "Client.h"
#include "../Configs.h"

// returns packet id from given message buffer
int get_packet_id(char *buffer)
{
    return buffer[0];
}

// create the packet to connect 
// creates char array with packet id and sender name
// returns len of array
int create_connect_request_packet(char *buffer, char *name)
{
    buffer[0] = PACKET_CONNECT_REQUEST;
    strcpy(buffer+1, name);
    return 1+strlen(name);
}

// create one byte packet that includes type of the packet
// returns 1 as the size of packet
int create_simple_packet(char type, char *buffer)
{
    buffer[0] = type;
    return 1;
}

// create packet to accept connection
int create_connect_accept_packet(char *buffer, char *name)
{
    buffer[0] = PACKET_CONNECT_ACCEPT;
    strcpy(buffer+1, name);
    return 1 + strlen(name);
}

// creates list of all available users to send it to requester
int create_list_of_users_packet(char *buffer)
{
    buffer[0] = PACKET_LIST_USERS;
    // number of clients
    buffer[1] = 0;
    // start position
    int pos = 2;
    for (int i = 0; i < MAX_CLIENTS; i++)
    {
        // if client is active
        if (clients[i].active > 0)
        {
            // write address of client into buffer
            buffer[1]++;
            memcpy(buffer+pos, &(clients->address), sizeof(struct sockaddr_in));
            pos += sizeof(struct sockaddr_in);
        }
    }
    return pos;
}
