#include "Configs.h"
#include "Utils/Auth.h"
#include "Utils/Interface.h"
#include "Network/Socket.h"
#include "Network/Packet.h"
#include "Network/Client.h"

int main(int argc, char **argv)
{
    // init user stats
    int user_port = DEFAULT_PORT;
    char *user_ip = NULL;
    int connect_port = DEFAULT_PORT;
    char connect_ip[MAX_IPv4_LENGTH] = {0};
    char name[MAX_NAME_LENGTH]; 

    // ask user to input name
    get_name(name);

    // ask user to input local port
    get_user_port(&user_port);

    // ask user to connect
    get_connection_address(connect_ip, &connect_port);

    fflush(stdin);
    system("clear");

    // Local socket address
    struct sockaddr_in local_address;

    // Socket to send/receive data
    struct sockaddr_in buffer_address;

    // Buffer for messages
    char buffer_read[BUFFER_SIZE] = {0};
    char buffer_send[BUFFER_SIZE] = {0};
    // Buffer for name
    char buffer_name[MAX_NAME_LENGTH] = {0};

    // Messages length
    int read_size = 0;
    int send_size = 0;

    // Creating the socket
    int sock = create_socket();
    // Binding the socket to the port
    bind_address(sock, &local_address, user_port);
    // Getting user ip address
    user_ip = inet_ntoa(local_address.sin_addr);

    // save_user_info(name, user_ip, user_port);
    init_ui(name, user_ip, user_port);

    // WTF
    setNonblockFlag(sock);
    setNonblockFlag(0);

    // If connect ip exists - try to connect
    if (connect_ip[0] != 0)
    {
        create_Addr(connect_ip, connect_port, &buffer_address);
        sprintf((char*)&buffer_send, "Connecting to %s:%d", connect_ip, connect_port);
        add_message((char*)buffer_send);
    }
    else
    {
        add_message("Waiting someone to connect...");
    }

    while (1)
    {
        // C )))
        // Need to pass struct size pointer
        unsigned int address_size = sizeof(local_address);
        while ((read_size = read_from_socket(sock, (char*)&buffer_read, &buffer_address, &address_size)) != -1) // while getting smth
        {
            // do not get our own packages
            if (check_equal_addresses(&local_address, &buffer_address))
                continue;

            int packet_id = get_packet_id((char*)&buffer_read);

            // struct Client *client = get_client(&buffer_address); // todo
        }
    }

    return 0;
}