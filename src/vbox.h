#ifndef VBOX_H
#define VBOX_H

#include "reg.h"
#include "message.h"

class Vbox {
    private:
        Reg reg;
        Message message;
    public:
        Vbox();
        //~Vbox();
        void check_vbox_characteristic();
        void set_vbox_characteristic();
};

#endif