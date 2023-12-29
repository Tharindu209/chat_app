CC = gcc
CFLAGS = -Wall -Wextra

mainServer:
	$(CC) $(CFLAGS) -o mainServer mainServer.c tic-tac-toe/game_server.c chatApp/chat_server.c

mainClient:
	$(CC) $(CFLAGS) -o mainClient mainClient.c tic-tac-toe/game_client.c chatApp/chat_client.c

clean:
	rm -f mainServer mainClient