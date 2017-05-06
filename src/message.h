#ifndef MESSAGE_H
#define MESSAGE_H

#include <windows.h>

void success_message(char const*);
void fail_message(char const*);
void success_message_block(char const*);
void fail_message_block(char const*);
char* convert_DWORD_to_Char(DWORD);

#endif