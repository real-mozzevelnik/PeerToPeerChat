#ifndef Configs_h
#define Configs_h

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <net/if.h>

#define DEFAULT_PORT 8888
#define MAX_NAME_LENGTH 50
#define MAX_IPv4_LENGTH 50
#define BUFFER_SIZE 512
#define MAX_MESSAGES 20
#define MAX_CLIENTS 20
#define TICK_PER_SECOND 10

#define PING_SKIP 10
#define SEND_PING_PAUSE 10

#endif