// client.h

#ifndef GAME_CLIENT_H
#define GAME_CLIENT_H

int game_client(char* initIp, int initPort);
void error(const char *msg);
void recv_msg(int sockfd, char * msg);
int recv_int(int sockfd);
void write_server_int(int sockfd, int msg);
int connect_to_server(char * hostname, int portno);
void draw_board(char board[][3]);
void take_turn(int sockfd);
void get_update(int sockfd, char board[][3]);

#endif