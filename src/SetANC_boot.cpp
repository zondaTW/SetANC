#include <stdio.h>
#include <stdlib.h>

#include "vmware.h"
#include "vbox.h"

int main()
{
    create_vmware_process();
    create_vbox_process();
    system("pause");
    return 0;
}

