// server.h

#ifndef GAME_SERVER_H
#define GAME_SERVER_H

void game_server(int initPort);
void *run_game(void *thread_data);
int check_board(char board[][3], int last_move);
void send_player_count(int cli_sockfd);
void send_update(int * cli_sockfd, int move, int player_id);
void draw_board(char board[][3]);
void update_board(char board[][3], int move, int player_id);
int check_move(char board[][3], int move);
int get_player_move(int cli_sockfd);
void get_clients(int lis_sockfd, int * cli_sockfd);
int recv_int(int cli_sockfd);
int setup_listener(int portno);
void write_clients_int(int * cli_sockfd, int msg);
void write_clients_msg(int * cli_sockfd, char * msg);
void write_client_int(int cli_sockfd, int msg);
void write_client_msg(int cli_sockfd, char * msg);
void error(const char *msg);

#endif