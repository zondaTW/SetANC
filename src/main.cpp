#include <cstdio>
#include <cstdlib>

#include "antivm.h"

int main()
{
    AntiVM antivm;
	antivm.cpuid_exc_31_bit();
	antivm.cpuid_hypervisor_brand();
    printf("What do you want to do? check or set characteristic (0/1): ");
    int choice = 0;
    scanf("%d", &choice);
    if (choice == 0) {
        antivm.check_characteristic();
    }
    else if (choice == 1) {
        printf("What are you want to set? Vmware or Vbox (0/1): ");
        scanf("%d", &choice);
        if (choice == 0 || choice == 1)
            antivm.set_characteristic(choice);
    }
    system("pause");
    return 0;
}

