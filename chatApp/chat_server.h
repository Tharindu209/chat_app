// server.h

#ifndef CHAT_SERVER_H
#define CHAT_SERVER_H

int chat_server(int initPort);
void *handle_client(void *arg);
void send_message(char *s, int uid);
void queue_remove(int uid);
void str_trim_lf (char* arr, int length);


#endif