#ifndef VBOX_H
#define VBOX_H

#define TEMP_STRING_SIZE 150

#include "reg.h"
#include "message.h"


void check_vbox_characteristic();
void set_vbox_characteristic();
void create_vbox_process(char*);
void copy_vbox_process_file(char const*, char const*);
#endif