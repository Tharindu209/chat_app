#include <stdio.h>
#include <stdlib.h>

#include "chatApp/chat_client.h"
#include "tic-tac-toe/game_client.h"

typedef struct{
    char* ipAddress;
    int port;
} mainClient;


void getIPAddressAndPort(mainClient* usr) {
    usr->ipAddress = malloc(16 * sizeof(char));
    if (usr->ipAddress == NULL) {
        printf("Failed to allocate memory for IP address.\n");
        exit(1);
    }

    printf("Enter IP address: ");
    scanf("%s", usr->ipAddress);
    
    printf("Enter port number: ");
    scanf("%d", &usr->port);
}

int main() {
    int choice;
    mainClient* user = (mainClient*)malloc(sizeof(mainClient));
    
    printf("Select an option:\n");
    printf("1. Play a game\n");
    printf("2. Chat with each other\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);
    
    switch (choice) {
        case 1:
            getIPAddressAndPort(user);
            game_client(user->ipAddress, user->port);
            break;
        case 2:
            getIPAddressAndPort(user);
            chat_client(user->port, user->ipAddress);
            break;
        default:
            printf("Invalid choice\n");
            break;
    }
    free(user);
    return 0;
}
