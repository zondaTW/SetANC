#include <cstdio>
#include <windows.h>

#include "message.h"

Message::Message() {
    buffer = new char[40];
    _hstdout = GetStdHandle(STD_OUTPUT_HANDLE);
}

void Message::success_message(char const * str) {
    SetConsoleTextAttribute(_hstdout, FOREGROUND_GREEN);
    puts(str);
    SetConsoleTextAttribute(_hstdout, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}

void Message::fail_message(char const * str) {
    SetConsoleTextAttribute(_hstdout, FOREGROUND_RED);
    puts(str);
    SetConsoleTextAttribute(_hstdout, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}

char* Message::convert_DWORD_to_Char(DWORD d_str) {
    snprintf(buffer, 40, "%lu", d_str);
    return buffer;
}