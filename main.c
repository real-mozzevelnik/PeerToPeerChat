#include "Configs.h"
#include "Auth.h"
#include "Interface.h"
#include "Network/Socket.h"

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

    printf("\n\n%s\n%d\n%s\n%d\n", name, user_port, connect_ip, connect_port);

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

    user_info(name, user_ip, user_port);
    show_messages();

    // WTF
    setNonblockFlag(sock);
    setNonblockFlag(0);

    // If connect ip exists - try to connect
    if (connect_ip[0] != 0)
    {
        create_Addr(connect_ip, connect_port, &buffer_address);
        sprintf((char*)&buffer_send, "Connecting to %s:%d", connect_ip, connect_port);
    }


    

    return 0;
}