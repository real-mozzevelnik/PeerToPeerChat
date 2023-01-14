#ifndef Socket_h
#define Socket_h
#include "../Configs.h"

// create the socket and check success
int create_socket(void);

// Binding the socket addr to given port
void bind_address(int sock, struct sockaddr_in *addr, int port);

// non block flag for descriptor
void setNonblockFlag(int descriptor);

// write given parameteres in addr
void create_Addr(char *ip, int port, struct sockaddr_in *addr);

// read the message from socket and save sender address in given addr
// if there are no messages returns -1
int read_from_socket(int sock, char *buffer, struct sockaddr_in *addr, unsigned int *addr_len);

// Checks two clients addresses
int check_equal_addresses(struct sockaddr_in *first, struct sockaddr_in *second);

// send udp message
void send_udp(int sock, struct sockaddr_in *addr, char *buffer, int buffer_size);

#endif