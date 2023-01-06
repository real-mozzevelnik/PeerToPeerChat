#include "Configs.h"
#include "Interface.h"

char messages[30][512] = {{0}};
// func to send error and exit programm
void send_error(char *error_name)
{
    printf("Error\n");
    printf("%s\n", error_name);
    exit(EXIT_FAILURE);

}

void user_info(char *name, char *ip, int port)
{
    puts("─────────────────────────────────────────────────────────────────");
    printf("│ Your name: %-51s│\n", name);
    printf("│ Your ip address: %-45s│\n", ip);
    printf("│ Your port: %-51d│\n", port);
    puts("─────────────────────────────────────────────────────────────────");
}

void show_messages(void)
{
    puts("─────────────────────────────────────────────────────────────────");
    printf("│ MESSAGES:                                                     │\n");
    for (int i = 0; i < 20; i++)
    {
        printf("│ %-62s│\n", messages[i]);
    }
    puts("─────────────────────────────────────────────────────────────────");

}
