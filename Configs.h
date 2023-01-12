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

#define DEFAULT_PORT 8888
#define MAX_NAME_LENGTH 50
#define MAX_IPv4_LENGTH 50
#define BUFFER_SIZE 256
#define MAX_MESSAGES 20
