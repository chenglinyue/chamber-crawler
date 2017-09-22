#ifndef WOUNDDEF_H
#define WOUNDDEF_H

#include "item.h"

class WoundDef: public Item {
    public:
        WoundDef (Controller & c, char id);
        virtual void pickUp(Player &player);
        virtual WoundDef* copy ();
};

#endif
