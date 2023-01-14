#ifndef Packet_h
#define Packet_h

#define PACKET_CONNECT_REQUEST '0' // packet to request for connection
#define PACKET_CONNECT_ACCEPT '1' // packet to accept connection
#define PACKET_PING '2' // ping packet
#define PACKET_TIMEOUT '3' // packet to disconect the client
#define PACKET_REQUEST_USERS '4' // packets to get all users
#define PACKET_LIST_USERS '5'
#define PACKET_SEND_MESSAGE '6' //message packet

// returns packet id from given message buffer
int get_packet_id(char *buffer);

// create the packet to connect 
// creates char array with packet id and sender name
// returns len of array
int create_connect_request_packet(char *buffer, char *name);

// create one byte packet that includes type of the packet
// returns 1 as the size of packet
int create_simple_packet(char type, char *buffer);

// create packet to accept connection
int create_connect_accept_packet(char *buffer, char *name);

// creates list of all available users to send it to requester
int create_list_of_users_packet(char *buffer);

#endif