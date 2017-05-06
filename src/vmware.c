#include <stdio.h>
#include <string.h>
#include <windows.h>

#include "vmware.h"
#include "reg.h"
#include "file.h"
#include "process.h"
#include "message.h"


char const* vmware_registry_value_list[][3] = {
    {"HARDWARE\\DEVICEMAP\\Scsi\\Scsi Port 0\\Scsi Bus 0\\Target Id 0\\Logical Unit Id 0", "Identifier", "VMware"},
    {"HARDWARE\\DEVICEMAP\\Scsi\\Scsi Port 1\\Scsi Bus 0\\Target Id 0\\Logical Unit Id 0", "Identifier", "VMware"},
    {"HARDWARE\\DEVICEMAP\\Scsi\\Scsi Port 2\\Scsi Bus 0\\Target Id 0\\Logical Unit Id 0", "Identifier", "VMware"}
};
char const* vmware_registry_key_list[] = {
    "SOFTWARE\\VMware, Inc.\\VMware Tools"
};
char const* vmware_file_list[] = {
    "C:\\windows\\System32\\Drivers\\Vmmouse.sys",
    "C:\\windows\\System32\\Drivers\\vm3dgl.dll",
    "C:\\windows\\System32\\Drivers\\vmdum.dll",
    "C:\\windows\\System32\\Drivers\\vm3dver.dll",
    "C:\\windows\\System32\\Drivers\\vmtray.dll",
    "C:\\windows\\System32\\Drivers\\VMToolsHook.dll",
    "C:\\windows\\System32\\Drivers\\vmmousever.dll",
    "C:\\windows\\System32\\Drivers\\vmhgfs.dll",
    "C:\\windows\\System32\\Drivers\\vmGuestLib.dll",
    "C:\\windows\\System32\\Drivers\\VmGuestLibJava.dll",
    "C:\\windows\\System32\\Driversvmhgfs.dll"
};
char const* vmware_process_list[] = {
    "Vmtoolsd.exe",
    "Vmwaretrat.exe",
    "Vmwareuser.exe",
    "Vmacthlp.exe"
};


void check_vmware_characteristic() {
    unsigned char byBuffer[1024];
    char temp[TEMP_STRING_SIZE];

    puts("-------registry value-------");
    int rows = sizeof(vmware_registry_value_list) / sizeof(vmware_registry_value_list[0]);
    for (int i = 0; i < rows; i++) { 
        sprintf(temp, "Check HKEY_LOCAL_MACHINE\\%s->%s: %s", 
            vmware_registry_value_list[i][0], 
            vmware_registry_value_list[i][1],
            vmware_registry_value_list[i][2]);

        if (read_registry_value(
                HKEY_LOCAL_MACHINE, 
                vmware_registry_value_list[i][0], 
                vmware_registry_value_list[i][1], 
                byBuffer)
        ) {
            if (strncmp ((char*)vmware_registry_value_list[i][2], (char*)byBuffer, sizeof(vmware_registry_value_list[i][2])) == 0) {
                //puts("WMWARE");
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
    rows = sizeof(vmware_registry_key_list) / sizeof(vmware_registry_key_list[0]);
    for (int i = 0; i < rows; i++) {
        sprintf(temp, "Check HKEY_LOCAL_MACHINE\\%s", 
            (char*)vmware_registry_key_list[i]);

        if (open_registry_key(HKEY_LOCAL_MACHINE, vmware_registry_key_list[i])) {
            //puts("WMWARE");
            success_message_block(temp);
        }
        else {
            fail_message_block(temp);
        }
    }

    puts("-------file-------");
    rows = sizeof(vmware_file_list) / sizeof(vmware_file_list[0]);
    for (int i = 0; i < rows; i++) {
        sprintf(temp, "Check %s", 
            (char*)vmware_file_list[i]);

        if (file_exists(vmware_file_list[i])) {
            //puts("WMWARE");
            success_message_block(temp);
        }
        else {
            fail_message_block(temp);
        }
    }

    puts("-------process-------");
    rows = sizeof(vmware_process_list) / sizeof(vmware_process_list[0]);
    for (int i = 0; i < rows; i++) {
        sprintf(temp, "Check %s", 
            (char*)vmware_process_list[i]);

        if (get_process(vmware_process_list[i])) {
            //puts("WMWARE");
            success_message_block(temp);
        }
        else {
            fail_message_block(temp);
        }
    }
}

void set_vmware_characteristic() {
    char temp[TEMP_STRING_SIZE];

    puts("-------registry value-------");
    int rows = sizeof(vmware_registry_value_list) / sizeof(vmware_registry_value_list[0]);
    for (int i = 0; i < rows; i++) { 
        sprintf(temp, "Set %s\\%s\\%s", 
            vmware_registry_value_list[i][0], 
            vmware_registry_value_list[i][1],
            vmware_registry_value_list[i][2]);

        if (create_registry_value(
                HKEY_LOCAL_MACHINE, 
                "",
                vmware_registry_value_list[i][0], 
                vmware_registry_value_list[i][1],
                vmware_registry_value_list[i][2])
        ) {
            success_message_block(temp);
        }
        else {
            fail_message_block(temp);
        }
    }

    puts("-------registry key-------");
    rows = sizeof(vmware_registry_key_list) / sizeof(vmware_registry_key_list[0]);
    for (int i = 0; i < rows; i++) {
        sprintf(temp, "Set %s", 
            (char*)vmware_registry_key_list[i]);

        if (create_registry_key(
                HKEY_LOCAL_MACHINE, 
                "",
                vmware_registry_key_list[i])
        ) {
            success_message_block(temp);
        }
        else {
            fail_message_block(temp);
        }
    }

    puts("-------file-------");
    rows = sizeof(vmware_file_list) / sizeof(vmware_file_list[0]);
    for (int i = 0; i < rows; i++) {
        sprintf(temp, "Set %s", 
            (char*)vmware_file_list[i]);

        if (create_file(vmware_file_list[i])
        ) {
            success_message_block(temp);
        }
        else {
            fail_message_block(temp);
        }
    }
}

void create_vmware_process() {
    int rows = sizeof(vmware_process_list) / sizeof(vmware_process_list[0]);
    for (int i = 0; i < rows; i++) {
        printf("%s", (char*)vmware_process_list[i]);
        create_process((char*)vmware_process_list[i]);
    }
}

void copy_vmware_process_file(char const* exe_file, char const* path) {
    int rows = sizeof(vmware_process_list) / sizeof(vmware_process_list[0]);
    char temp[TEMP_STRING_SIZE];
    for (int i = 0; i < rows; i++) {
        sprintf(temp, "COPY %s \"%s\\%s\"", exe_file, path, (char*)vmware_process_list[i]);
        puts(temp);
        system(temp);
    }
}