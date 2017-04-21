#ifndef ANTIVM_H
#define ANTIVM_H

#include "reg.h"
#include "message.h"
#include "vbox.h"
#include "vmware.h"

class AntiVM {
    private:
        Reg reg;
        Message message;
        Vbox vbox;
        Vmware vmware;
    public:
        AntiVM();
        //~AntiVM();
        void check_characteristic();
        void set_characteristic(int);
        void cpuid_exc_31_bit();
        void cpuid_hypervisor_brand();
        void check_registry_key();
};

#endif