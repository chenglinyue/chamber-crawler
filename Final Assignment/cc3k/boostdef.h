#ifndef BOOSTDEF_H
#define BOOSTDEF_H

#include "item.h"

class BoostDef: public Item {
    public:
        BoostDef (Controller & c, char id);
        virtual void pickUp(Player &player);
        virtual BoostDef* copy ();
};

#endif
