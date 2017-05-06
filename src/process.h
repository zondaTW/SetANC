#ifndef PROCESS_H
#define PROCESS_H

#include <windows.h>

int create_process(char const*);
int get_process(char const*);
DWORD GetProcessIdFromName(char const*);

#endif