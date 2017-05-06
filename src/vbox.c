#include <stdio.h>
#include <string.h>
#include <windows.h>

#include "vbox.h"
#include "reg.h"
#include "file.h"
#include "process.h"
#include "message.h"


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
char const* vbox_file_list[] = {
    "C:\\windows\\System32\\Drivers\\VBoxMouse.sys",
    "C:\\windows\\System32\\Drivers\\VBoxGuest.sys",
    "C:\\windows\\System32\\Drivers\\VBoxSF.sys",
    "C:\\windows\\System32\\Drivers\\VBoxVideo.sys",
    "C:\\windows\\System32\\vboxdisp.dll",
    "C:\\windows\\System32\\vboxhook.dll",
    "C:\\windows\\System32\\vboxmrxnp.dll",
    "C:\\windows\\System32\\vboxogl.dll",
    "C:\\windows\\System32\\vboxoglarrayspu.dll",
    "C:\\windows\\System32\\vboxoglcrutil.dll",
    "C:\\windows\\System32\\vboxoglerrorspu.dll",
    "C:\\windows\\System32\\vboxoglfeedbackspu.dll",
    "C:\\windows\\System32\\vboxoglpackspu.dll",
    "C:\\windows\\System32\\vboxoglpassthroughspu.dll",
    "C:\\windows\\System32\\vboxservice.exe",
    "C:\\windows\\System32\\vboxtray.exe",
    "C:\\windows\\System32\\VBoxControl.exe"
};
char const* vbox_process_list[] = {
    "vboxservice.exe",
    "vboxtray.exe"
};


void check_vbox_characteristic() {
    unsigned char byBuffer[1024];
    char temp[TEMP_STRING_SIZE];

    puts("-------registry value-------");
    int rows = sizeof(vbox_registry_value_list) / sizeof(vbox_registry_value_list[0]);
    for (int i = 0; i < rows; i++) { 
        sprintf(temp, "Check HKEY_LOCAL_MACHINE\\%s->%s: %s",
            vbox_registry_value_list[i][0], 
            vbox_registry_value_list[i][1],
            vbox_registry_value_list[i][2]);

        if (read_registry_value(
                HKEY_LOCAL_MACHINE, 
                vbox_registry_value_list[i][0], 
                vbox_registry_value_list[i][1], 
                byBuffer)
        ) {
            if (strstr ((char*)byBuffer, (char*)vbox_registry_value_list[i][2]) != NULL) {
                //puts("VBOX");
                success_message_block(temp);
            }
            else {
                fail_message_block(temp);
            }
        }
        else {
            fail_message_block(temp);
        }
    }

    puts("-------registry key-------");
    rows = sizeof(vbox_registry_key_list) / sizeof(vbox_registry_key_list[0]);
    for (int i = 0; i < rows; i++) {
        sprintf(temp, "Check HKEY_LOCAL_MACHINE\\%s", 
            vbox_registry_key_list[i]);

        if (open_registry_key(HKEY_LOCAL_MACHINE, vbox_registry_key_list[i])) {
            //puts("VBOX");
            success_message_block(temp);
        }
        else {
            fail_message_block(temp);
        }
    }

    puts("-------file-------");
    rows = sizeof(vbox_file_list) / sizeof(vbox_file_list[0]);
    for (int i = 0; i < rows; i++) {
        sprintf(temp, "Check %s", 
            vbox_file_list[i]);

        if (file_exists(vbox_file_list[i])
        ) {
            success_message_block(temp);
        }
        else {
            fail_message_block(temp);
        }
    }

    puts("-------process-------");
    rows = sizeof(vbox_process_list) / sizeof(vbox_process_list[0]);
    for (int i = 0; i < rows; i++) {
        sprintf(temp, "Check %s", 
            vbox_process_list[i]);

        if (get_process(vbox_process_list[i])) {
            //puts("VBOX");
            success_message_block(temp);
        }
        else {
            fail_message_block(temp);
        }
    }
}

void set_vbox_characteristic() {
    char temp[TEMP_STRING_SIZE];
    
    puts("-------registry value-------");
    int rows = sizeof(vbox_registry_value_list) / sizeof(vbox_registry_value_list[0]);
    for (int i = 0; i < rows; i++) { 
        sprintf(temp, "Set %s\\%s\\%s", 
            vbox_registry_value_list[i][0], 
            vbox_registry_value_list[i][1],
            vbox_registry_value_list[i][2]);

        if (create_registry_value(
                HKEY_LOCAL_MACHINE, 
                "",
                vbox_registry_value_list[i][0], 
                vbox_registry_value_list[i][1],
                vbox_registry_value_list[i][2])
        ) {
            success_message_block(temp);
        }
        else {
            fail_message_block(temp);
        }
    }

    puts("-------registry key-------");
    rows = sizeof(vbox_registry_key_list) / sizeof(vbox_registry_key_list[0]);
    for (int i = 0; i < rows; i++) {
        sprintf(temp, "Set %s", 
            vbox_registry_key_list[i]);

        if (create_registry_key(
                HKEY_LOCAL_MACHINE, 
                "",
                vbox_registry_key_list[i])
        ) {
            success_message_block(temp);
        }
        else {
            fail_message_block(temp);
        }
    }

    puts("-------file-------");
    rows = sizeof(vbox_file_list) / sizeof(vbox_file_list[0]);
    for (int i = 0; i < rows; i++) {
        sprintf(temp, "Set %s", 
            vbox_file_list[i]);

        if (create_file(vbox_file_list[i])
        ) {
            success_message_block(temp);
        }
        else {
            fail_message_block(temp);
        }
    }
}

void create_vbox_process() {
    int rows = sizeof(vbox_process_list) / sizeof(vbox_process_list[0]);
    for (int i = 0; i < rows; i++) {
        create_process((char*)vbox_process_list[i]);
    }
}

void copy_vbox_process_file(char const* exe_file, char const* path) {
    int rows = sizeof(vbox_process_list) / sizeof(vbox_process_list[0]);
    char temp[TEMP_STRING_SIZE];
    for (int i = 0; i < rows; i++) {
        sprintf(temp, "COPY %s \"%s\\%s\"", exe_file, path, (char*)vbox_process_list[i]);
        puts(temp);
        system(temp);
    }
}