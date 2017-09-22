#ifndef WOUNDATK_H
#define WOUNDATK_H

#include "item.h"

class WoundAtk: public Item {
    public:
        WoundAtk (Controller & c, char id);
        virtual void pickUp(Player &player);
        virtual WoundAtk* copy ();
};

#endif
