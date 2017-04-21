#ifndef REG_H
#define REG_H

#include "message.h"

class Reg {
    private:
        Message message;
        int KEY_WOW64_64KEY;
    public:
        Reg();
        //~Reg();
        void isWow64();
        int open_registry_key(HKEY, char const*);
        int read_registry_value(HKEY, char const*, char const*, unsigned char[]);
        int create_registry_key(HKEY, char const*, char const*);
        int create_registry_value(HKEY, char const*, char const*, char const*, char const*);
        int delete_registry_value(HKEY, char const*, char const*);
        int delete_registry_key(HKEY, char const*, char const*);
};

#endif