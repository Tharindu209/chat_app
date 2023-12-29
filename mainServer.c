#include <stdio.h>
#include <stdlib.h>

#include "tic-tac-toe/game_server.h"
#include "chatApp/chat_server.h"

int main(void) {
    int port;
    int choice;

    printf("------WELCOME------\n");
    printf("Select an option:\n");
    printf("1. Play a game\n");
    printf("2. Chat with each other\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);
    
    switch (choice) {
        case 1:
            printf("Enter the Tic-Tac-Toe server port: ");
            scanf("%d", &port);
            game_server(port);
            break;
        case 2:
            printf("Enter the Chat server port: ");
            scanf("%d", &port);
            chat_server(port);
            break;
        default:
            printf("Invalid choice\n");
            break;
    }

    return 0;
}
