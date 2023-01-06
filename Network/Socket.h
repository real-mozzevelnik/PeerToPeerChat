#ifndef Socket_h
#define Socket_h
#include "../Configs.h"

// Creating empty socket
int create_socket(void);

// Binding the socket addr to given port
void bind_address(int sock, struct sockaddr_in *addr, int port);

// WTF
void setNonblockFlag(int descriptor);

void create_Addr(char *ip, int port, struct sockaddr_in *addr);

#endif