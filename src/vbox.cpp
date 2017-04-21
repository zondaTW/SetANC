#include <cstdio>
#include <cstring>
#include <windows.h>

#include "vbox.h"
#include "reg.h"

char const* vbox_registry_value_list[][3] = {
    {"HARDWARE\\DEVICEMAP\\Scsi\\Scsi Port 0\\Scsi Bus 0\\Target Id 0\\Logical Unit Id 0", "Identifier", "VBOX"},
    {"HARDWARE\\Description\\System", "SystemBiosVersion", "VBOX"},
    {"HARDWARE\\Description\\System", "VideoBiosVersion", "VIRTUALBOX"}
};
char const* vbox_registry_key_list[] = {
    "HARDWARE\\ACPI\\DSDT\\VBOX__",
    "HARDWARE\\ACPI\\FADT\\VBOX__",
    "HARDWARE\\ACPI\\RSDT\\VBOX__",
    "SOFTWARE\\Oracle\\VirtualBox Guest Additions",
    "SYSTEM\\ControlSet001\\Services\\VBoxGuest",
    "SYSTEM\\ControlSet001\\Services\\VBoxMouse",
    "SYSTEM\\ControlSet001\\Services\\VBoxService",
    "SYSTEM\\ControlSet001\\Services\\VBoxSF",
    "SYSTEM\\ControlSet001\\Services\\VBoxVideo"
};

Vbox::Vbox() {
}

void Vbox::check_vbox_characteristic() {
    unsigned char byBuffer[1024];
    int rows = sizeof(vbox_registry_value_list) / sizeof(vbox_registry_value_list[0]);
    for (int i = 0; i < rows; i++) { 
        if (reg.read_registry_value(
                HKEY_LOCAL_MACHINE, 
                vbox_registry_value_list[i][0], 
                vbox_registry_value_list[i][1], 
                byBuffer)
        ) {
            if (strcmp ((char*)vbox_registry_value_list[i][2], (char*)byBuffer) == 0) {
                puts("VBOX");
            }
        }
    }

    rows = sizeof(vbox_registry_key_list) / sizeof(vbox_registry_key_list[0]);
    for (int i = 0; i < rows; i++) {
        if (reg.open_registry_key(HKEY_LOCAL_MACHINE, vbox_registry_key_list[i])) {
            puts("VBOX");
        }
    }
}

void Vbox::set_vbox_characteristic() {
    int rows = sizeof(vbox_registry_value_list) / sizeof(vbox_registry_value_list[0]);
    for (int i = 0; i < rows; i++) { 
        if (reg.create_registry_value(
                HKEY_LOCAL_MACHINE, 
                "",
                vbox_registry_value_list[i][0], 
                vbox_registry_value_list[i][1],
                vbox_registry_value_list[i][2])
        ) {
            message.success_message("setup succcess");
        }
    }

    rows = sizeof(vbox_registry_key_list) / sizeof(vbox_registry_key_list[0]);
    for (int i = 0; i < rows; i++) {
        if (reg.create_registry_key(
                HKEY_LOCAL_MACHINE, 
                "",
                vbox_registry_key_list[i])
        ) {
            message.success_message("setup succcess");
        }
    }
}