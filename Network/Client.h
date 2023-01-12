#ifndef Client_h
#define Client_h
#include "../Configs.h"

struct Client
{
    int active;
    char name[MAX_NAME_LENGTH];
    struct sockaddr_in address;
};

#endif
