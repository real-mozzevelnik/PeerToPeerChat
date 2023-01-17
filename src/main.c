#include "Configs.h"
#include "Utils/Auth.h"
#include "Utils/Interface.h"
#include "Network/Socket.h"
#include "Network/Packet.h"
#include "Network/Client.h"
#include <signal.h>

int main(int argc, char **argv)
{
    // init user stats
    int user_port = DEFAULT_PORT;
    char user_ip[30] = {0};
    int connect_port = DEFAULT_PORT;
    char connect_ip[MAX_IPv4_LENGTH] = {0};
    char name[MAX_NAME_LENGTH]; 

    // ask user to input name
    get_name(name);

    // ask user to input local port
    get_user_port(&user_port);

    // ask user to connect
    get_connection_address(connect_ip, &connect_port);

    // clear stdin buffer and init ui
    fflush(stdin);
    interface_init();

    // Local socket address for user
    struct sockaddr_in local_address;

    // Socket to send/receive data
    struct sockaddr_in buffer_address;

    // Buffer for messages
    char buffer_read[BUFFER_SIZE] = {0};
    char buffer_send[BUFFER_SIZE] = {0};
    // Buffer for name
    char buffer_name[MAX_NAME_LENGTH] = {0};

    // buffer for input messages
    static char buffer_input[100] = {0};
    // length of given input
    static int input_size = 0;

    // Messages length
    int read_size = 0;
    int send_size = 0;

    // Creating the socket
    int sock = create_socket();
    // !get user local ip
    know_ip(user_ip);

    // Binding the socket to the port
    bind_address(sock, &local_address, user_port, user_ip);

    // set user info
    update_info(name, user_ip, user_port);

    // non block the socket and stdin descriptors
    setNonblockFlag(sock);
    setNonblockFlag(0);

    // If connect ip exists - try to connect
    if (connect_ip[0] != 0)
    {
        // create ann address to connect and add messages
        create_Addr(connect_ip, connect_port, &buffer_address);
        // add message about connection
        sprintf((char*)&buffer_send, "Connecting to %s:%d", connect_ip, connect_port);
        add_message((char*)buffer_send);
        // send packets to connect and wait for acception
        connect_to_client(sock, &buffer_address, (char*)&name);
    }
    else
    {
        add_message("Waiting someone to connect...");
    }
    int time_to_send_ping = SEND_PING_PAUSE;
    // if user stops the programm using CTRL+C that function will catch it
    // and free memory allocated for ui windows
    signal(SIGINT, close_ui);

    while (1)
    {
        // Need to pass struct size pointer 
        unsigned int address_size = sizeof(local_address);
        // sleep(1);
        // while there are packets
        // writes address of sender in buffer_address
        while ((read_size = read_from_socket(sock, (char*)&buffer_read, &buffer_address, &address_size)) != -1) 
        {
            // do not get our own packages
            if (check_equal_addresses(&local_address, &buffer_address))
                continue;

            // to choose what to do with packet - need to now what is that packet for
            int packet_id = get_packet_id((char*)&buffer_read);
            // get the pointer to client struct of the sender
            struct Client *client = get_client(&buffer_address);

            // skip the client if he isnt authorized and thats not connection request or acception
            if (client == NULL && packet_id != PACKET_CONNECT_REQUEST && packet_id != PACKET_CONNECT_ACCEPT)
                continue;
            
            // send ping packet
            if (client != NULL)
            {
                if (packet_id != PACKET_PING)
                {
                    create_simple_packet(PACKET_PING, (char*)&buffer_send);
                    send_udp(sock, &buffer_address, (char*)&buffer_send, 1);
                }
            }

            // finish received message with \0
            buffer_read[read_size] = '\0';

            switch (packet_id)
            {
                case PACKET_CONNECT_REQUEST:
                    // if client do not already exists
                    if (!client_exists(&buffer_address))
                    {
                        // copy the name
                        strcpy((char*)&buffer_name, buffer_read+1);
                        // add new client
                        add_client(&buffer_address, (char*)&buffer_name);
                        // add message about connection
                        sprintf((char*)&buffer_send, "%s connected!", buffer_name);
                        add_message((char*)&buffer_send);
                    }
                    // send acception
                    // do even if client exists - user could be disconected recently and tries to connect again
                    send_size = create_connect_accept_packet((char*)&buffer_send, (char*)&name);
                    send_udp(sock, &buffer_address, (char*)&buffer_send, send_size);
                    break;

                case PACKET_CONNECT_ACCEPT:
                    // if client do not already exists
                    if (!client_exists(&buffer_address))
                    {
                        // copy the name
                        strcpy((char*)&buffer_name, buffer_read+1);
                        // add new client
                        add_client(&buffer_address, (char*)&buffer_name);
                        // add message about connection
                        sprintf((char*)&buffer_send, "Connected to %s!", buffer_name);
                        add_message((char*)&buffer_send);
                    }
                    break;

                case PACKET_PING:
                    // reload client activity
                    client->active = PING_SKIP;
                    break;

                case PACKET_TIMEOUT:
                    // if user was disconected - try to connect again
                    connect_to_client(sock, &buffer_address, (char*)name);
                    break;

                case PACKET_SEND_MESSAGE:
                    // print message and sender name
                    sprintf((char*)&buffer_send, "%s: %s", client->name, buffer_read+1);
                    add_message(buffer_send);
                    break;

                case PACKET_REQUEST_USERS:
                    // create list of available users and send it to requester
                    send_size = create_list_of_users_packet((char*)&buffer_send);
                    send_udp(sock, &buffer_address, (char*)&buffer_send, send_size);
                    break;

                case PACKET_LIST_USERS:
                    // create request packet to send
                    send_size = create_connect_request_packet((char*)&buffer_send, (char*)&name);
                    // number of users in the given list
                    int count = buffer_read[1];
                    // index of buffer_read to copy memory from
                    int pos = 2;
                    for (int i = 0; i < count; i++)
                    {
                        // copy address into buffer
                        memcpy(&buffer_address, buffer_read+pos, sizeof(struct sockaddr_in));
                        // send connection request
                        send_udp(sock, &buffer_address, (char*)&buffer_send, send_size);
                        // increase index
                        pos += sizeof(struct sockaddr_in);
                    }
                    break;
            }
        }

        while (read_input((char*)&buffer_input, &input_size) == 1)
        {
            // add message to user
            sprintf((char*)&buffer_send, "You: %s", buffer_input);
            add_message((char*)&buffer_send);
            // screate packet and message to all the clients
            create_message_packet((char*)&buffer_send, (char*)buffer_input, input_size);
            send_to_every_one(sock, (char*)&buffer_send, input_size + 1);
            // clear the buffer
            memset(buffer_input, 0, 100);
            input_size = 0;
        }

        // sending the ping
        time_to_send_ping--;
        if (time_to_send_ping <= 0)
        {
            for (int i = 0; i < MAX_CLIENTS; i++)
            // if client didnt send ping packets for a long time
            if (clients[i].active == 1)
            {
                // delete client
                create_simple_packet(PACKET_TIMEOUT, (char*)&buffer_send);
                send_udp(sock, &clients[i].address, buffer_send, 1);
                delete_client(&clients[i]);
                // add message about client removing
                sprintf((char*)&buffer_send, "%s disconected!", clients[i].name);
                add_message((char*)&buffer_send);
            }
            // if client is active
            else if(clients[i].active > 1)
            {
                // decrease his activity
                clients[i].active--;
                // send ping to every one
                create_simple_packet(PACKET_PING, (char*)&buffer_send);
                send_to_every_one(sock, (char*)&buffer_send, 1);
            }
            // update ping time
            time_to_send_ping = SEND_PING_PAUSE;
        } 

    }

    return 0;
}