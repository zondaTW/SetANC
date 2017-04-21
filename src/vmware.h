#ifndef VMWARE_H
#define VMWARE_H

#include "reg.h"
#include "message.h"

class Vmware {
    private:
        Reg reg;
        Message message;
    public:
        Vmware();
        //~Vmware();
        void check_vmware_characteristic();
        void set_vmware_characteristic();
};

#endif