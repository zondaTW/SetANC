#ifndef VMWARE_H
#define VMWARE_H

#define TEMP_STRING_SIZE 150

#include "reg.h"
#include "message.h"


void check_vmware_characteristic();
void set_vmware_characteristic();
void create_vmware_process(char*);
void copy_vmware_process_file(char const*, char const*);

#endif