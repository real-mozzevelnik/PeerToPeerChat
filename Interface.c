#include "Configs.h"
#include "Interface.h"

// func to send error and exit programm
void send_error(char *error_name)
{
    printf("Error\n");
    printf("%s\n", error_name);
    exit(EXIT_FAILURE);

}
