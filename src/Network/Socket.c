#include "Socket.h"
#include "../Configs.h"
#include "../Utils/Interface.h"
#include <assert.h>

// create the socket and check success
int create_socket(void)
{
    int sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (sock == -1) 
        send_error("Error: creating the socket.");
    return sock;
}

// Binding the socket addr to given port
void bind_address(int sock, struct sockaddr_in *addr, int port, char *ip)
{
    // Clean addr
    memset((char*)addr, 0, sizeof(*addr));
    addr->sin_family = AF_INET; // Set the inet
    addr->sin_port = htons((unsigned short)port); // Set network byte order
    // !transform user ip to required byte order
    addr->sin_addr.s_addr = inet_addr(ip);

    // Binding the socket to local port
    int result = bind(sock, (struct sockaddr*)addr, sizeof(*addr)); // Binding the socket
    if (result == -1)
        send_error("Error: binding the socket.");
}

// non block flag for descriptor
void setNonblockFlag(int descriptor) 
{
    int flags = fcntl(descriptor, F_GETFL);
    flags |= O_NONBLOCK;
    fcntl(descriptor, F_SETFL, flags);
}

// write given parameteres in addr
void create_Addr(char *ip, int port, struct sockaddr_in *addr)
{
    addr->sin_family = AF_INET;
    addr->sin_addr.s_addr = inet_addr(ip);
    addr->sin_port = htons(port);
}

// read the message from socket and save sender address in given addr
// if there are no messages returns -1
int read_from_socket(int sock, char *buffer, struct sockaddr_in *addr, unsigned int *addr_len)
{
    int received_len = (int) recvfrom(sock, buffer, BUFFER_SIZE, 0, (struct sockaddr*)addr, addr_len);
    return received_len;
}

// Checks two clients addresses
int check_equal_addresses(struct sockaddr_in *first, struct sockaddr_in *second)
{
    return (first->sin_addr.s_addr == second->sin_addr.s_addr) && (first->sin_port == second->sin_port);
}

// send udp message
void send_udp(int sock, struct sockaddr_in *addr, char *buffer, int buffer_size)
{
    sendto(sock, buffer, buffer_size, 0, (struct sockaddr*)addr, sizeof(*addr));
}

// get local ip address
// creates new socket
// thats now the best way to do that, i think, but thats the one that works
// copied from stackoverflow
// https://stackoverflow.com/questions/212528/how-can-i-get-the-ip-address-of-a-linux-machine
void know_ip(char *buffer)
{
    size_t buflen = 30;
    int sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

    const char* kGoogleDnsIp = "8.8.8.8";
    uint16_t kDnsPort = 53;
    struct sockaddr_in serv;
    memset(&serv, 0, sizeof(serv));
    serv.sin_family = AF_INET;
    serv.sin_addr.s_addr = inet_addr(kGoogleDnsIp);
    serv.sin_port = htons(kDnsPort);

    int err = connect(sock, (struct sockaddr*) &serv, sizeof(serv));

    struct sockaddr_in name;
    socklen_t namelen = sizeof(name);
    err = getsockname(sock, (struct sockaddr*) &name, &namelen);


    const char* p = inet_ntop(AF_INET, &name.sin_addr, buffer, buflen);
    close(sock);
}

