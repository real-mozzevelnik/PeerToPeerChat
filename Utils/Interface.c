#include "../Configs.h"
#include "Interface.h"

#include <ncurses.h>

// buffer for messages
static char messages[16][126] = {{0}};

// windows for info messages and input
static WINDOW *user_info_box = NULL;
static WINDOW *messages_box = NULL;
static WINDOW *input_box = NULL;

// create window for user info
static void init_info()
{
    user_info_box = newwin(5, 65, 0, 0);
    box(user_info_box, 0, 0);
    wrefresh(user_info_box);
}

// create window for messages
static void init_messages()
{
    messages_box = newwin(17, 65, 5, 0);
    box(messages_box, 0, 0);
    wrefresh(messages_box);
}

// create window for input
static void init_input()
{
    input_box = newwin(3, 65, 22, 0);
    box(input_box, 0, 0);
    wrefresh(input_box);
}

// initialize the whole interface
void interface_init()
{
    printf("\e[8;25;80;t");
    // init ncurses lib
    initscr();
    // init boxes
    init_info();
    init_messages();
    init_input();

    keypad(input_box, TRUE);
    echo();
    cbreak(); // disable line buffering
    wtimeout(input_box, 1000 / TICK_PER_SECOND);
}

// update user info box
void update_info(char *name, char *ip, int port)
{
    // clear and recreate box
    wclear(user_info_box);
    box(user_info_box, 0, 0);
    // print address
    mvwprintw(user_info_box, 1, 1, "Your address: ");
    mvwprintw(user_info_box, 1, 16, ip);
    char port_string[5] = {0};
    sprintf((char*)&port_string, "%d", port);
    mvwprintw(user_info_box, 1, 16 + strlen(ip), ":");
    mvwprintw(user_info_box, 1, 17 + strlen(ip), port_string);
    // print name
    mvwprintw(user_info_box, 2, 1, "Your name: ");
    mvwprintw(user_info_box, 2, 12, name);

    wrefresh(user_info_box);
}

// recreates message window and print messages
static void update_messages()
{
    wclear(messages_box);
    box(messages_box, 0, 0);
    for (int i = 0; i < 16; i++)
    {
        mvwprintw(messages_box, i, 1, messages[i]);
    }
    wrefresh(messages_box);
}

// add message to message box
// the very first message in the list will disappear
void add_message(char *message)
{
    for (int i = 1; i < 16; i++)
    {
        // clean and move messages
        memset((char*)&messages[i-1], ' ', sizeof(char) * 18);
        strcpy((char*)&messages[i-1], (char*)messages[i]);
    }
    strcpy((char*)&messages[15], message);
    update_messages();
}

// print error with given name
void send_error(char *error_name)
{
    printf("Error\n");
    printf("%s\n", error_name);
    exit(EXIT_FAILURE);

}

// get input from input window to enter messages
int read_input(char *buffer, int *size)
{
    int symbol = 0;
    // err comes when there is no input in 100 ms
    while ((symbol = wgetch(input_box)) != ERR)
    {
        // return if enter
        if (symbol == '\n')
        {
            for (int i = 0; i < *size; i++)
                mvwprintw(input_box, 1, i+1, " ");
            return 1;
        }
        // replace symbol with " "
        else if (symbol == KEY_BACKSPACE)
        {
            if (*size > 0)
            {
                mvwprintw(input_box, 1, *size, " ");
                (*size)--;
                buffer[*size] = 0;
            }
        }
        // add symbol into buffer if number of symbols less than 99
        else if (*size < 99)
        {
            buffer[*size] = (char)symbol;
            (*size)++;
        }
    }
    mvwprintw(input_box, 1, 1, (char*)buffer);
    return 0;
}



