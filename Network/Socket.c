#include "Socket.h"
#include "../Configs.h"
#include "../Interface.h"

int create_socket(void)
{
    int sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (sock == -1) 
        send_error("Error: creating the socket.");
    return sock;
}

void bind_address(int sock, struct sockaddr_in *addr, int port)
{
    // Clean addr
    memset((char*)addr, 0, sizeof(*addr));
    addr->sin_family = AF_INET; // Set the inet
    addr->sin_port = htons((uint16_t)port); // Set  network byte order
    addr->sin_addr.s_addr = htonl(INADDR_LOOPBACK);

    // Binding the socket to local port
    int result = bind(sock, (struct sockaddr*)addr, sizeof(*addr)); // Bibding the socket
    if (result == -1)
        send_error("Error: binding the socket.");
}

// WTF
void setNonblockFlag(int descriptor) 
{
    int flags = fcntl(descriptor, F_GETFL);
    flags |= O_NONBLOCK;
    fcntl(descriptor, F_SETFL, flags);
}

void create_Addr(char *ip, int port, struct sockaddr_in *addr)
{
    addr->sin_family = AF_INET;
    addr->sin_addr.s_addr = inet_addr(ip);
    addr->sin_port = htons(port);
}
