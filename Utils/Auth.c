#include "Interface.h"
#include "Auth.h"
#include "../Configs.h"

// asks user to enter name
void get_name(char *name)
{
    // clear name space
    memset(name, 0, MAX_NAME_LENGTH);
    printf("Enter your name: ");
    char * check = fgets(name, MAX_NAME_LENGTH, stdin);
    // check if name is valid
    if (check == NULL || strlen(name) == 1)
    {
        send_error("Not valid name");
    }
    // get rid of '\n' in name
    check = strchr(name, '\n');
    if (check) *check = '\0';
}

// asks user to enter local port
void get_user_port(int *user_port)
{
    char yes;
    char port[10];
    // Ask to change user port
    do
    {
        puts("Wanna set your port? (y/n)");
        yes = getchar(); getchar(); // clear \n symbol from stdin
    } 
    while (yes != 'y' && yes != 'Y' && yes != 'n' && yes != 'N');
    if (yes == 'y' || yes == 'Y')
    {
        puts("Enter port: ");
        fgets(port, 10, stdin);
        *user_port = atoi(port); // convert port from str to int
        if (*user_port == 0)
        {
            send_error("Incorrect user port");
        }
    }
}

// ask user for connection ip address and port
void get_connection_address(char *connect_ip, int *connect_port)
{
    char yes;
    char port[10];
    // clear ip space
    memset(connect_ip, 0, MAX_IPv4_LENGTH);
    // Ask to connect
    do
    {
        puts("Wanna connect to smbd? (y/n)");
        yes = getchar(); getchar(); // clear \n symbol from stdin
    } 
    while (yes != 'y' && yes != 'Y' && yes != 'n' && yes != 'N');
    if (yes == 'y' || yes == 'Y')
    {
        // ip address
        puts("Enter ip address to connect: ");
        char * check = fgets(connect_ip, MAX_IPv4_LENGTH, stdin);
        // check if ip is valid
        if (check == NULL || strlen(connect_ip) == 1)
        {
            send_error("Not valid ip address");
        }
        // port
        puts("Enter port: ");
        fgets(port, 10, stdin);
        *connect_port = atoi(port); // convert port from str to int
        // check if port is valid
        if (*connect_port == 0)
        {
            send_error("Incorrect connection port");
        }
        // get rid of '\n' in ip
        check = strchr(connect_ip, '\n');
        if (check) *check = '\0';
    }
}
