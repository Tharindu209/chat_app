#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include<arpa/inet.h>
#include <netdb.h>

#include "game_client.h"

void error(const char *msg)
{
    perror(msg);
    printf("Either the server shut down or the other player disconnected.\nGame over.\n");
    exit(0);
}

void recv_msg(int sockfd, char * msg)
{
    memset(msg, 0, 4);
    int n = read(sockfd, msg, 3);
    
    if (n < 0 || n != 3)
     error("ERROR reading message from server socket.");

    printf("Received message: %s\n", msg);
   }

int recv_int(int sockfd)
{
    int msg = 0;
    int n = read(sockfd, &msg, sizeof(int));
    
    if (n < 0 || n != sizeof(int)) 
        error("ERROR reading int from server socket");
    return msg;
}

void write_server_int(int sockfd, int msg)
{
    int n = write(sockfd, &msg, sizeof(int));
    if (n < 0)
        error("ERROR writing int to server socket");
    
    printf("Wrote int to server: %d\n", msg);
    
}
int connect_to_server(char * hostname, int portno)
{
    struct sockaddr_in serv_addr;
    struct hostent *server;
 
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	
    if (sockfd < 0) 
        error("ERROR opening socket for server.");
	
    server = gethostbyname(hostname);
	
    if (server == NULL) {
        fprintf(stderr,"ERROR, no such host\n");
        exit(0);
    }
	
	memset(&serv_addr, 0, sizeof(serv_addr));

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(hostname);
    serv_addr.sin_port = htons(portno); 

   if (connect(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) 
        error("ERROR connecting to server");

    printf("Connected to server.\n");
     return sockfd;
}

void draw_board(char board[][3]){
    printf("\t\t %c | %c | %c \n", board[0][0], board[0][1], board[0][2]);
    printf("\t\t-----------\n");
    printf("\t\t %c | %c | %c \n", board[1][0], board[1][1], board[1][2]);
    printf("\t\t-----------\n");
    printf("\t\t %c | %c | %c \n", board[2][0], board[2][1], board[2][2]);
}

void take_turn(int sockfd)
{
    char buffer[10];
    
    while (1) { 
        printf("Enter 0-8 to make a move, or 9 for find number of active players: ");
	    fgets(buffer, 10, stdin);
	    int move = buffer[0] - '0';
        if (move <= 9 && move >= 0){
            printf("\n");
             write_server_int(sockfd, move);   
            break;
        } 
        else
            printf("\nInvalid input. Try again.\n");
    }
}

void get_update(int sockfd, char board[][3])
{
    
    int player_id = recv_int(sockfd);
    int move = recv_int(sockfd);
    board[move/3][move%3] = player_id ? 'X' : 'O';    
}


int game_client(char* initIp, int initPort)
{

    int sockfd = connect_to_server(initIp, initPort);
    int id = recv_int(sockfd);

    char msg[4];
    char board[3][3] = { {' ', ' ', ' '}, 
                         {' ', ' ', ' '}, 
                         {' ', ' ', ' '} };

    printf("-------------------------------\n       Welcome tic-tac-toe      \n-------------------------------\n\n");

    do {
        recv_msg(sockfd, msg);
        if (!strcmp(msg, "HLD"))
            printf("Waiting for a second player...\n");
    } while ( strcmp(msg, "SRT") );

    /* The game has begun. */
    printf("\tGame on!\n");
    printf("Your are %c's\n", id ? 'X' : 'O');

    draw_board(board);

    while(1) {
        recv_msg(sockfd, msg);

        if (!strcmp(msg, "TRN")) { 
	        printf("Your move...\n");
	        take_turn(sockfd);
        }
        else if (!strcmp(msg, "INV")) { 
            printf("That position has already been played. Try again.\n"); 
        }
        else if (!strcmp(msg, "CNT")) { 
            int num_players = recv_int(sockfd);
            printf("There are currently %d active players.\n", num_players); 
        }
        else if (!strcmp(msg, "UPD")) { 
            get_update(sockfd, board);
            draw_board(board);
        }
        else if (!strcmp(msg, "WAT")) { 
            printf("Waiting for other players move...\n");
        }
        else if (!strcmp(msg, "WIN")) { 
            printf("You win!\n");
            break;
        }
        else if (!strcmp(msg, "LSE")) { 
            printf("You lost??.\n");
            break;
        }
        else if (!strcmp(msg, "DRW")) { 
            printf("--Draw--\n");
            break;
        }
        else 
            error("Unknown message.");
    }
    
    printf("Game over.\n");
    close(sockfd);
    return 0;
}