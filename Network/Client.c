#include "Client.h"
#include "Packet.h"
#include "Socket.h"
#include "../Utils/Interface.h"

// struct to save info about all clients in chat
struct Client clients[MAX_CLIENTS] = {0};

// send packet to request connection and wait to get accept answer
void connect_to_client(int sock, struct sockaddr_in *addr, char *name)
{
    // buffer for messages
    char buffer[100];
    // messages len
    int buffer_size = 0;

    while (1)
    {
        // create packet and get its size
        buffer_size = create_connect_request_packet((char*)buffer, name);
        // send the packet
        send_udp(sock, addr, buffer, buffer_size);
        sleep(2);

        // buffer for addr to save sender address
        struct sockaddr_in buffer_address = {0};
        unsigned int address_size = sizeof(struct sockaddr_in);
        // check messages in socket
        while ((buffer_size = read_from_socket(sock, (char*)&buffer, &buffer_address, &address_size)) != -1)
        {
            buffer[buffer_size] = '\0';
            int packet_id = get_packet_id((char*)&buffer);
            // if packet is connection accept and received addr equals to required addr
            if (packet_id == PACKET_CONNECT_ACCEPT && check_equal_addresses(addr, &buffer_address))
            {
                char buffer_name[MAX_NAME_LENGTH] = {0};
                // write client name
                strcpy((char*)&buffer_name, buffer + 1);
                // add new client to the array of clients
                add_client(&buffer_address, (char*)&buffer_name);
                // print message about connection
                sprintf((char*)&buffer, "Connected to %s", buffer_name);
                add_message((char*)&buffer);

                // send request to get all the clients
                buffer_size = create_simple_packet(PACKET_REQUEST_USERS, (char*)&buffer);
                send_udp(sock, addr, buffer, buffer_size);
                return;
            }

        }
    }
}

// add client in array of clients
void add_client(struct sockaddr_in *addr, char *name)
{
    // search for an empty space for new client
    for (int i = 0; i < MAX_CLIENTS; i++)
    {
        // if client is inactive or there is no client
        if (clients[i].active <= 0)
        {
            // copy address
            memcpy(&(clients[i].address), addr, sizeof(struct sockaddr_in));
            // copy name
            strcpy((char*)&(clients[i].name), name);
            // set activity
            clients[i].active = PING_SKIP;
            return;
        }
    }
}

// get pointer to client from clients array
struct Client * get_client(struct sockaddr_in *addr)
{
    for (int i = 0; i < MAX_CLIENTS; i++)
    {
        // check address is client is active
        if (clients[i].active > 0)
        {
            // if addresses are equal - return pointer to the client
            if (check_equal_addresses(addr, &(clients[i].address)))
            {
                return &(clients[i]);
            }
        }
    }
    // if client wasnt found - return NULL
    return NULL;
}

// check if client in clients array
int client_exists(struct sockaddr_in *addr)
{
    return get_client(addr) != NULL;
}

// send packet to all the clients
void send_to_every_one(int sock, char *buffer, int buffer_size)
{
    for (int i = 0; i < MAX_CLIENTS; i++)
    {
        if (clients[i].active > 0)
            send_udp(sock, &(clients[i].address), buffer, buffer_size);
    }
}