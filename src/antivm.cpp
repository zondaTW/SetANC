#include <cstdio>
#include <cstring>
#include <windows.h>

#include "antivm.h"

AntiVM::AntiVM() {
}

void AntiVM::cpuid_exc_31_bit() {
    printf("cpuid_exec_31_bit: ");

    int ecx;
    __asm__ volatile(
        "cpuid"
        : "=c"(ecx)
		: "a"(0x01)
    );
    int result = ((ecx >> 31) & 0x1);
    if (result == 0) {
        puts("physical machine");
    }
    else if (result == 1) {
        puts("VM machine");
    }
}

void AntiVM::cpuid_hypervisor_brand() {
    printf("cpuid_hypervisor_brand: ");

    unsigned int ebx, ecx, edx;
    char hyper_vendor_id[13];

    __asm__ volatile(
        "cpuid"\
        : "=b"(ebx), 
          "=c"(ecx), 
          "=d"(edx)
		: "a"(0x40000000)
    );
    memcpy(hyper_vendor_id + 0, &ebx, 4);
    memcpy(hyper_vendor_id + 4, &ecx, 4);
    memcpy(hyper_vendor_id + 8, &edx, 4);
    hyper_vendor_id[12] = '\0';

    char const* vm_list[] = {
        "VMwareVMware",
        "Microsoft Hv",
        "KVMKVMKVM\0\0\0",
        "XenVMMXenVMM",
        "prl hyperv ",
        "VBoxVBoxVBox"
    };
    bool flag = TRUE;
    int rows = sizeof(vm_list) / sizeof(vm_list[0]);
    for (int i = 0; i < rows; i++) {
        if (!strcmp(hyper_vendor_id, vm_list[i])) {
            puts(vm_list[i]);
            flag = FALSE;
        }
    }

    if (flag) {
        puts("physical machine");
    }
}

void AntiVM::check_characteristic() {
    puts("-----------------vmware-----------------");
    vmware.check_vmware_characteristic();
    puts("------------------vbox------------------");
    vbox.check_vbox_characteristic();
}

void AntiVM::set_characteristic(int choice) {
    if (choice == 0)
        vmware.set_vmware_characteristic();
    else if (choice == 1)
        vbox.set_vbox_characteristic();
}

void AntiVM::check_registry_key() {
    unsigned char byBuffer[1024];
    reg.create_registry_value(HKEY_CURRENT_USER, "SOFTWARE\\test", "test_subkey", "test_name", "test_value");
    reg.open_registry_key(HKEY_CURRENT_USER, "SOFTWARE\\test\\test_subkey");
    reg.create_registry_key(HKEY_CURRENT_USER, "SOFTWARE\\test", "test_subkey\\ttttttt");
    reg.read_registry_value(HKEY_CURRENT_USER, "SOFTWARE\\test\\test_subkey", "test_name", byBuffer);
    reg.delete_registry_value(HKEY_CURRENT_USER, "SOFTWARE\\test\\test_subkey", "test_name");
    reg.delete_registry_key(HKEY_CURRENT_USER, "SOFTWARE\\test", "test_subkey");
    reg.read_registry_value(HKEY_CURRENT_USER, "SOFTWARE\\test\\test_subkey", "test_name", byBuffer);
}
