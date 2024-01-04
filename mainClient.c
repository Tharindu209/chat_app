#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>

#include "chatApp/chat_client.h"
#include "tic-tac-toe/game_client.h"

typedef struct {
    char* ipAddress;
    int port;
} MainClient;

void getIPAddressAndPort(MainClient* user) {
    user->ipAddress = malloc(16 * sizeof(char));
    if (user->ipAddress == NULL) {
        endwin();  // Close ncurses before exiting
        printf("Failed to allocate memory for IP address.\n");
        exit(1);
    }

    printw("\n\n\tEnter IP address: ");
    refresh();
    scanw("%s", user->ipAddress);

    printw("\n\n\tEnter port number: ");
    refresh();
    scanw("%d", &user->port);
}

void printTableHeader() {
    attron(A_BOLD | A_UNDERLINE);
    printw("| Option |      Description      |\n");
    attroff(A_BOLD | A_UNDERLINE);
}

void printTableRow(int option, const char* description) {
    printw("|   %d    | %-21s|\n", option, description);
}

int main() {
    int choice;
    MainClient* user = (MainClient*)malloc(sizeof(MainClient));

    initscr();  
    start_color();  
    raw();      
    keypad(stdscr, TRUE);  
    init_pair(1, COLOR_YELLOW, COLOR_BLACK);  

    printw("-----WELCOME TO CONNECTx-----\n\n");
    printw("Select an option:\n");
    printw("-----------------------------------\n");
    printTableHeader();
    printw("-----------------------------------\n");
    attron(COLOR_PAIR(1));
    printTableRow(1, "Play a game");
    printTableRow(2, "Chat with each other");
    attroff(COLOR_PAIR(1));
    printw("----------------------------\n");
    printw("Enter your choice: ");
    refresh();

    // Get user input
    scanw("%d", &choice);

    switch (choice) {
        case 1:
            clear();  // Clear the screen
            getIPAddressAndPort(user);
            endwin();
            game_client(user->ipAddress, user->port);
            break;
        case 2:
            clear();  // Clear the screen
            getIPAddressAndPort(user);
            endwin();
            chat_client(user->port, user->ipAddress);
            break;
        default:
            printw("Invalid choice\n");
            break;
    }

    // Pause to see the output
    printw("Press any key to exit...");
    refresh();
    getch();

    endwin();  // Close ncurses

    free(user);
    return 0;
}

