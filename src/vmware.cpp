#include <cstdio>
#include <cstring>
#include <windows.h>

#include "vmware.h"
#include "reg.h"

char const* vmware_registry_value_list[][3] = {
    {"HARDWARE\\DEVICEMAP\\Scsi\\Scsi Port 0\\Scsi Bus 0\\Target Id 0\\Logical Unit Id 0", "Identifier", "VMware"},
    {"HARDWARE\\DEVICEMAP\\Scsi\\Scsi Port 1\\Scsi Bus 0\\Target Id 0\\Logical Unit Id 0", "Identifier", "VMware"},
    {"HARDWARE\\DEVICEMAP\\Scsi\\Scsi Port 2\\Scsi Bus 0\\Target Id 0\\Logical Unit Id 0", "Identifier", "VMware"}
};
char const* vmware_registry_key_list[] = {
    "SOFTWARE\\VMware, Inc.\\VMware Tools"
};

Vmware::Vmware() {
}

void Vmware::check_vmware_characteristic() {
    unsigned char byBuffer[1024];
    int rows = sizeof(vmware_registry_value_list) / sizeof(vmware_registry_value_list[0]);
    for (int i = 0; i < rows; i++) { 
        if (reg.read_registry_value(
                HKEY_LOCAL_MACHINE, 
                vmware_registry_value_list[i][0], 
                vmware_registry_value_list[i][1], 
                byBuffer)
        ) {
            if (strncmp ((char*)vmware_registry_value_list[i][2], (char*)byBuffer, sizeof(vmware_registry_value_list[i][2])) == 0) {
                puts("WMWARE");
            }
        }
    }

    rows = sizeof(vmware_registry_key_list) / sizeof(vmware_registry_key_list[0]);
    for (int i = 0; i < rows; i++) {
        if (reg.open_registry_key(HKEY_LOCAL_MACHINE, vmware_registry_key_list[i])) {
            puts("WMWARE");
        }
    }
}

void Vmware::set_vmware_characteristic() {
    int rows = sizeof(vmware_registry_value_list) / sizeof(vmware_registry_value_list[0]);
    for (int i = 0; i < rows; i++) { 
        if (reg.create_registry_value(
                HKEY_LOCAL_MACHINE, 
                "",
                vmware_registry_value_list[i][0], 
                vmware_registry_value_list[i][1],
                vmware_registry_value_list[i][2])
        ) {
            message.success_message("setup succcess");
        }
    }

    rows = sizeof(vmware_registry_key_list) / sizeof(vmware_registry_key_list[0]);
    for (int i = 0; i < rows; i++) {
        if (reg.create_registry_key(
                HKEY_LOCAL_MACHINE, 
                "",
                vmware_registry_key_list[i])
        ) {
            message.success_message("setup succcess");
        }
    }
}