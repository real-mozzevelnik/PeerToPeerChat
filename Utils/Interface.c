#include "../Configs.h"
#include "Interface.h"

static char messages[MAX_MESSAGES][BUFFER_SIZE] = {{0}};
// save user info
char name[MAX_NAME_LENGTH] = {0};
char ip[MAX_IPv4_LENGTH] = {0};
int port;

// func to send error and exit programm
void send_error(char *error_name)
{
    printf("Error\n");
    printf("%s\n", error_name);
    exit(EXIT_FAILURE);

}

void init_user_info(char *name, char *ip, int port)
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
    for (int i = 0; i < MAX_MESSAGES; i++)
    {
        printf("│ %-62s│\n", messages[i]);
    }
    puts("─────────────────────────────────────────────────────────────────");

}

void init_ui(char *name, char *ip, int port)
{
    system("clear");
    init_user_info(name, ip, port);
    show_messages();
}

void add_message(char *message)
{
    clear_messages();
    for (int i = 1; i < MAX_MESSAGES; i++)
    {   
        strcpy((char*)&messages[i-1], (char*)messages[i]);
    }
    strcpy((char*)&messages[MAX_MESSAGES-1], message);
    printf("\033[100A"); // move up a lot
    printf("\033[2B"); //move down
    show_messages();

}

void save_user_info(char *s_name, char *s_ip, int s_port)
{
    strcpy(name, s_name);
    strcpy(ip, s_ip);
    port = s_port;
}

void clear_messages(void)
{
    printf("\033[200A"); // move up a lot
    printf("\033[2B"); //move down
    for (int i = 0; i < MAX_MESSAGES + 2; i++)
    {
        printf("\033[64C"); // Move right X column;
        for (int i = 0; i < 66; i++) printf("\b \b"); // delete the str
        printf("\033[1B"); // Move down X lines;
    }
    printf("\033[1B"); // Move down X lines;
}



