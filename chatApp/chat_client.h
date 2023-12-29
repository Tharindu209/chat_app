// client.h

#ifndef CHAT_CLIENT_H
#define CHAT_CLIENT_H

int chat_client(int initPort, char* initIp);
void recv_msg_handler();
void send_msg_handler();
void catch_ctrl_c_and_exit();
void str_trim_lf(char* arr, int length);
void str_overwrite_stdout();

#endif