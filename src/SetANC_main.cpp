#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#include "antivm.h"
#include "process.h"
#include "file.h"
#include "reg.h"

#define TEMP_STRING_SIZE 150

extern char const* vmware_process_list;
extern char const* vbox_process_list;

int main()
{
	cpuid_exc_31_bit();
	cpuid_hypervisor_brand();
    printf("What do you want to do? check or set characteristic (0/1): ");
    int choice = 0;
    scanf("%d", &choice);
    if (choice == 0) {
        check_characteristic();
    }
    else if (choice == 1) {
        printf("What are you want to set? Vmware or Vbox or both (0/1/2): ");
        scanf("%d", &choice);
        if (choice >=0 && choice <=2)
            set_characteristic(choice);
        

        puts("------------------boot------------------");
        char temp[TEMP_STRING_SIZE];
        char const* exe_forever_file = "exe_forever.exe";
        char const* dir_path = "C:\\Program Files\\SetANC";
        puts("-------create dir-------");
        sprintf(temp, "mkdir \"%s\"", dir_path);
        system(temp);
        puts("-------copy boot file-------");
        sprintf(temp, "COPY %s \"%s\\%s\"", "SetANC_boot.exe", dir_path, "SetANC_boot.exe");
        system(temp);
        puts("-------set boot-------");
        sprintf(temp, "\"%s\\%s\"", dir_path, "SetANC_boot.exe");
        if (create_registry_value(
            HKEY_LOCAL_MACHINE, 
            "",
            "Software\\Microsoft\\Windows\\CurrentVersion\\Run",
            "SetANC",
            temp))
        {
            success_message_block(temp);
        }
        else {
            fail_message_block(temp);
        }
        puts("-------copy vmexe file-------");
        copy_vmware_process_file(exe_forever_file, dir_path);
        puts("-------copy vbox file-------");
        copy_vbox_process_file(exe_forever_file, dir_path);

        sprintf(temp, "\"%s\\%s\"", dir_path, "SetANC_boot.exe");
        system(temp);
    }
    system("pause");
    return 0;
}

