#include <stdio.h>
#include <windows.h>

#include "message.h"

HANDLE _hstdout = GetStdHandle(STD_OUTPUT_HANDLE);

void success_message(char const * str) {
    SetConsoleTextAttribute(_hstdout, FOREGROUND_GREEN);
    puts(str);
    SetConsoleTextAttribute(_hstdout, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}

void fail_message(char const * str) {
    SetConsoleTextAttribute(_hstdout, FOREGROUND_RED);
    puts(str);
    SetConsoleTextAttribute(_hstdout, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}

void success_message_block(char const * str) {
    printf("[");
    SetConsoleTextAttribute(_hstdout, FOREGROUND_GREEN);
    printf("ok");
    SetConsoleTextAttribute(_hstdout, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);  
    printf("]");
    puts(str);
}

void fail_message_block(char const * str) {
    printf("[");
    SetConsoleTextAttribute(_hstdout, FOREGROUND_RED);
    printf("failed");
    SetConsoleTextAttribute(_hstdout, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);  
    printf("]");
    puts(str);
}

char* convert_DWORD_to_Char(DWORD d_str) {
    char* buffer = new char[40];
    snprintf(buffer, 40, "%lu", d_str);
    return buffer;
}