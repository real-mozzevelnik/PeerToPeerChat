#ifndef Interface_h
#define Interface_h

void save_user_info(char *s_name, char *s_ip, int s_port);

void add_message(char *message);

void init_ui(char *name, char *ip, int port);

void send_error(char *error_name);

void init_user_info(char *name, char *ip, int port);

void show_messages(void);

void clear_messages(void);


#endif