#ifndef Interface_h
#define Interface_h

// print error with given name
void send_error(char *error_name);

// initialize the whole interface
void interface_init();

// update user info box
void update_info(char *name, char *ip, int port);

// add message to message box
// the very first message in the list will disappear
void add_message(char *message);

// get input from input window to enter messages
int read_input(char *buffer, int *size);

// clear the terminal
void close_ui(int sig);

#endif