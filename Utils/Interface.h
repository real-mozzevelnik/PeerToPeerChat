#ifndef Interface_h
#define Interface_h

void send_error(char *error_name);

void interface_init();

void update_info(char *name, char *ip, int port);

void add_message(char *message);

#endif