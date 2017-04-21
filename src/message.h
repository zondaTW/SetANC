#ifndef MESSAGE_H
#define MESSAGE_H

#include <windows.h>


class Message {
    private:
        char* buffer;
        HANDLE _hstdout;
    public:
        Message();
        //~Message();
        void success_message(char const*);
        void fail_message(char const*);
        char* convert_DWORD_to_Char(DWORD);
};

#endif