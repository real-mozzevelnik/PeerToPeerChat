#include "Configs.h"
#include "Auth.h"

#include <string.h>

int main(int argc, char **argv)
{
    // init user stats
    int user_port = DEFAULT_PORT;
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

    

    return 0;
}